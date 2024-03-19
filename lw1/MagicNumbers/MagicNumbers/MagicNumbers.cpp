// MagicNumbers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cstdint>

const std::string NON_MAGIC = "Non-magic\n";
const std::string ERROR = "ERROR\n";
const char CH_0 = '0';
const int DEPTH = 10;

bool IsNonNegativeNumber(const std::string& subject)
{
    if (subject.empty())
    {
        return false;
    }

    for (int i = 0; i < subject.length(); i++)
    {
        if (!isdigit(subject[i]))
        {
            return false;
        }
    }
    return true;
}

bool ConvertToUint64(const std::string& subject, std::uint64_t& number)
{
    for (char ch : subject)
    {
        if (number > (UINT64_MAX - (ch - CH_0)) / DEPTH)
        {
            return false;
        }
        number = DEPTH * number + (ch - CH_0);
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: MagicNumbers.exe\n";
        return 1;
    }

    std::string line;
    if (!getline(std::cin, line) || !IsNonNegativeNumber(line))
    {
        std::cout << ERROR;
        return 0;
    }

    std::uint64_t number = 0;
    if (!ConvertToUint64(line, number))
    {
        std::cout << ERROR;
        return 0;
    }

    std::cout << NON_MAGIC;

    if (std::cin.bad())
    {
        std::cout << "Failed to read data from input stream\n";
        return 1;
    }

    if (!std::cout.flush())
    {
        std::cout << "Failed to write data in output stream\n";
        return 1;
    }

    return 0;
}