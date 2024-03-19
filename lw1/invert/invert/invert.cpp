// invert.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <iomanip>
#include <sstream>

const int HEIGHT_OF_MATRIX = 3;

using Array2D = std::array<std::array<float, HEIGHT_OF_MATRIX>, HEIGHT_OF_MATRIX>;

bool ConvertLineToMatrix(const std::string& subject, Array2D& matrix, const int row)
{
    std::istringstream stream(subject);
    int i = 0;
    float number;
    while (stream >> number)
    {
        if (i > 2)
        {
            return false;
        }
        matrix[row][i] = number;
        i++;
    }
    if (stream.bad() || i <= 2)
    {
        return false;
    }
    return true;
}

bool ReadMatrixFromStream(std::istream& input, Array2D& matrix)
{
    std::string line;
    int i = 0;

    while (std::getline(input, line))
    {
        if (line == "")
        {
            return false;
        }
        if (i > 2)
        {
            return false;
        }
        if (!ConvertLineToMatrix(line, matrix, i))
        {
            return false;
        }
        i++;
    }
    if (input.bad() || i <= 2)
    {
        return false;
    }
    return true;
}

float FindDeterminantOfMatrix(Array2D& matrix)
{
    return matrix[0][0] * matrix[1][1] * matrix[2][2] +
        matrix[0][1] * matrix[1][2] * matrix[2][0] +
        matrix[1][0] * matrix[2][1] * matrix[0][2] -
        matrix[0][2] * matrix[1][1] * matrix[2][0] -
        matrix[0][1] * matrix[1][0] * matrix[2][2] -
        matrix[2][1] * matrix[1][2] * matrix[0][0];
}

void TransposeMatrix(Array2D& matrix)
{
    for (int i = 0; i < HEIGHT_OF_MATRIX; i++)
    {
        for (int j = 0; j < HEIGHT_OF_MATRIX; j++)
        {
            if (i != j && i < j)
            {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
}

float FindAddition(Array2D matrix, int i, int j)
{
    float addition[4];
    int counter = 0;
    for (int k = 0; k < HEIGHT_OF_MATRIX; k++)
    {
        if (k == i)
        {
            continue;
        }
        for (int p = 0; p < HEIGHT_OF_MATRIX; p++)
        {
            if (p != j)
            {
                addition[counter++] = matrix[k][p];
            }
        }
    }

    return addition[0] * addition[3] - addition[1] * addition[2];
}

Array2D FindMatrixOfAdditions(Array2D matrix)
{
    Array2D matrixAdd;
    for (int i = 0; i < HEIGHT_OF_MATRIX; i++)
    {
        for (int j = 0; j < HEIGHT_OF_MATRIX; j++)
        {
            matrixAdd[i][j] = FindAddition(matrix, i, j);
            if ((i + j) % 2 != 0)
            {
                matrixAdd[i][j] *= -1;
            }
        }
    }
    return matrixAdd;
}

bool InvertMatrix(Array2D& matrix)
{
    float det = round(FindDeterminantOfMatrix(matrix) * 1000) / 1000;
    if (det == 0)
    {
        return false;
    }

    matrix = FindMatrixOfAdditions(matrix);
    TransposeMatrix(matrix);

    for (int i = 0; i < HEIGHT_OF_MATRIX; i++)
    {
        for (int j = 0; j < HEIGHT_OF_MATRIX; j++)
        {
            matrix[i][j] = round((matrix[i][j] / det) * 1000) / 1000;
        }
    }
    return true;
}

void FixNegativeZerosInMatrix(Array2D& matrix)
{
    for (int i = 0; i < HEIGHT_OF_MATRIX; i++)
    {
        for (int j = 0; j < HEIGHT_OF_MATRIX; j++)
        {
            matrix[i][j] = (matrix[i][j] == -0) ? 0 : matrix[i][j];
        }
    }
}

void PrintMatrix(const Array2D matrix)
{
    for (int i = 0; i < HEIGHT_OF_MATRIX; i++)
    {
        for (int j = 0; j < HEIGHT_OF_MATRIX; j++)
        {
            std::cout << matrix[i][j];
            if (j != 2)
            {
                std::cout << " ";
            }
        }
        if (i != 2)
        {
            std::cout << "\n";
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: invert.exe <matrix file1>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1], std::ios::in);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open this file for reading: " << argv[1] << "\n";
        return 1;
    }

    Array2D matrix;
    if (!ReadMatrixFromStream(inputFile, matrix))
    {
        std::cout << "Failed to read matrix from input file\n";
        std::cout << "In input file must be 3x3 matrix\n";
        return 1;
    }

    if (!InvertMatrix(matrix))
    {
        std::cout << "Cannot invert this matrix: the determinant is zero\n";
        return 0;
    }

    FixNegativeZerosInMatrix(matrix);

    PrintMatrix(matrix);

    return 0;
}