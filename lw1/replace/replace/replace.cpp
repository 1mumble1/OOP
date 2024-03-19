// replace.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <optional>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::string searchString;
    std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];
    return args;
}

std::string ReplaceString( std::string& subject,
    const std::string& searchString, const std::string& replacementString)
{
    if (searchString.empty())
    {
        return subject;
    }

    size_t pos = 0;
    // Результат будет записан в новую строку result, оставляя строку subject неизменной
    std::string result;
    while (pos < subject.length())
    {
        // Находим позицию искомой строки, начиная с pos
        size_t foundPos = subject.find(searchString, pos);
        // Если не нашли - добавляем остаток исходной строки и возвращаем результат
        if (foundPos == std::string::npos)
        {
            return result.append(subject, pos, subject.length());
        }

        // Если нашли - в результирующую строку записываем текст из диапазона [pos,foundPos) и заменяющую строку
        result.append(subject, pos, foundPos - pos);
        result.append(replacementString);
        pos = foundPos + searchString.length();
    }
    return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output, 
    const std::string& searchString, const std::string& replacementString)
{
    std::string line;

    while (std::getline(input, line))
    {
        output << ReplaceString(line, searchString, replacementString) << "\n";
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: replace.exe <input file> <output file> <search string> <replace string>";
        return 1;
    }

    std::ifstream inputFile(args->inputFileName, std::ios::in);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open this file for reading: " << args->inputFileName << "\n";
        return 1;
    }

    std::ofstream outputFile(args->outputFileName, std::ios::out);
    if (!outputFile.is_open())
    {
        std::cout << "Failed to open this file for writing: " << args->outputFileName << "\n";
        return 1;
    }

    std::string search = args->searchString;
    std::string replace = args->replaceString;

    CopyStreamWithReplacement(inputFile, outputFile, search, replace);

    if (inputFile.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return 1;
    }

    if (!outputFile.flush())
    {
        std::cout << "Failed to write data in output file\n";
        return 1;
    }

    return 0;
}