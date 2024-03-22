// Vocabulary.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Vocabulary.h"
#include <optional>
#include <fstream>
#include <Windows.h>

const std::string INVALID_ARGS = "Invalid arguments count.\nUsage: Vocabulary.exe <file of vocabulary>.\n";
const std::string READING_ERROR = "Failed to read data from vocabulary.\nFormat is: <word>:<translate>.\n";
const std::string EXIT = "...";

std::optional<std::string> ParseArgs(int argc, char *argv[])
{
    if (argc != 2)
    {
        return std::nullopt;
    }
    std::string args = argv[1];
    return args;
}

int main(int argc, char *argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << INVALID_ARGS;
        return 1;
    }

    std::map<std::string, std::string> vocabulary;
    size_t startSizeOfVocabulary;

    if (!IdentifyVocabulary(args.value(), vocabulary, startSizeOfVocabulary))
    {
        std::cout << READING_ERROR;
        return 1;
    }

    std::string word;
    while (std::getline(std::cin, word)) // в отдельную функцию 
    {
        if (word.empty())
        {
            continue;
        }

        if (word == EXIT)
        {
            return TryToSaveChanges(args.value(), vocabulary, startSizeOfVocabulary);
        }

        if (!FindWordInVocabulary(word, vocabulary))
        {
            TryToSaveNewTranslation(word, vocabulary);
            continue;
        }


        std::cout << vocabulary[LowerCaseString(word)] << std::endl;
    }

    return 0;
}