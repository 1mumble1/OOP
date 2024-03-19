// crypt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>
#include <fstream>
#include <cstdint>

const char CH_0 = '0';
const int DEPTH = 10;
const std::string CRYPT = "crypt";
const std::string DECRYPT = "decrypt";

struct Args
{
    std::string mode;// enum
    std::string inputFileName;
    std::string outputFileName;
    std::string key;// число
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        return std::nullopt;
    }
    Args args;
    args.mode = argv[1];
    args.inputFileName = argv[2];
    args.outputFileName = argv[3];
    args.key = argv[4];
    return args;
}

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

bool ConvertToUint8(const std::string& subject, std::uint8_t& number)
{
    for (char ch : subject)
    {
        if (number > (UINT8_MAX - (ch - CH_0)) / DEPTH)
        {
            return false;
        }
        number = DEPTH * number + (ch - CH_0);
    }

    return true;
}

char ShuffleBits(char ch)
{
    ch = (ch & 0b11100000) >> 5 | (ch & 0b00011111) << 3;
    ch = (ch & 0b00011000) >> 1 | (ch & 0b00000100) << 3 | (ch & 0b00100000) >> 1 | (ch & 0b11000011);
    return ch;
}

char UnshuffleBits(char ch)
{
    ch = (ch & 0b00100000) >> 3 | (ch & 0b00001100) << 1 | (ch & 0b00010000) << 1 | (ch & 0b11000011);
    ch = (ch & 0b00000111) << 5 | (ch & 0b11111000) >> 3;
    return ch;
}


//std::function использовать
void Crypt(std::istream& input, std::ostream& output, const int& key)
{
    char ch;
    while (input.get(ch))
    {
        output.put(ShuffleBits(ch ^ key));
    }
}

void Decrypt(std::istream& input, std::ostream& output, const int& key)
{
    char ch;
    while (input.get(ch))
    {
        output.put(UnshuffleBits(ch) ^ key);
    }
}

// не работает с .exe,  добавить соответствующий тест

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: crypt.exe crypt/decrypt <input file> <output file> <key>\n";
        return 1;
    }

    // в функцию вынести открытие файлов
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

    std::uint8_t key = 0;
    if (!IsNonNegativeNumber(args->key) || !ConvertToUint8(args->key, key))
    {
        std::cout << "Incorrect value of key: it must be in interval [0, 255]\n";
        return 1;
    }

    if (args->mode != CRYPT && args->mode != DECRYPT)
    {
        std::cout << "Incorrect mode of program: it must be 'crypt' or 'decrypt' only\n";
        return 1;
    }

    if (args->mode == CRYPT)
    {
        Crypt(inputFile, outputFile, key);
    }
    else
    {
        Decrypt(inputFile, outputFile, key);
    }
    
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
