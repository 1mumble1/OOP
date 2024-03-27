#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Vocabulary/Vocabulary.h"
#include <fstream>

#include <Windows.h>

const std::string START_VALUES = "cat:кошка\ndog:собака";

bool CompareFiles(const std::string fileName1, const std::string fileName2)
{
	std::ifstream file1(fileName1);
	std::ifstream file2(fileName2);

	char ch1, ch2;
	while (!file1.eof() && !file2.eof())
	{
		file1.get(ch1);
		file2.get(ch2);
		if (ch1 != ch2)
		{
			return false;
		}
	}

	if (!file1.eof() || !file2.eof())
	{
		return false;
	}

	return true;
}

SCENARIO("Opening file with non-valid string returns false-result and empty map")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	REQUIRE(!IdentifyVocabulary("nonValid.txt", vocabulary, startSize));
	REQUIRE(vocabulary.empty());
}

SCENARIO("Opening missing file returns empty map")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	REQUIRE(IdentifyVocabulary("missing.txt", vocabulary, startSize));
	REQUIRE(vocabulary.empty());
}

SCENARIO("Opening normal file returns map with several values")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;

	std::ofstream inputVocabulary("input.txt");
	inputVocabulary << START_VALUES;
	inputVocabulary.close();

	REQUIRE(IdentifyVocabulary("input.txt", vocabulary, startSize));
	REQUIRE(!vocabulary.empty());
}

SCENARIO("If word not in the vocabulary, it gives false")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;

	std::ofstream inputVocabulary("input.txt");
	inputVocabulary << START_VALUES;
	inputVocabulary.close();

	IdentifyVocabulary("input.txt", vocabulary, startSize);

	REQUIRE(!FindWordInVocabulary("paper", vocabulary));
}

SCENARIO("If word in the vocabulary, it gives true")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;

	std::ofstream inputVocabulary("input.txt");
	inputVocabulary << START_VALUES;
	inputVocabulary.close();

	IdentifyVocabulary("input.txt", vocabulary, startSize);

	REQUIRE(FindWordInVocabulary("cat", vocabulary));
}

SCENARIO("If save new word in vocabulary, you can translate it")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;

	std::ofstream inputVocabulary("input.txt");
	inputVocabulary << START_VALUES;
	inputVocabulary.close();

	IdentifyVocabulary("input.txt", vocabulary, startSize);

	std::string word = "road", translate = "дорога";
	std::istringstream input(translate);
	std::ofstream output("output.txt");
	TryToSaveNewTranslation(word, vocabulary, input, output);
	REQUIRE(vocabulary[word] == translate);

	output.close();
	REQUIRE(CompareFiles("output.txt", "outputGoodSaveTranslation.txt"));
}

SCENARIO("If ignore new word in vocabulary, you cannot translate it")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;

	std::ofstream inputVocabulary("input.txt");
	inputVocabulary << START_VALUES;
	inputVocabulary.close();

	IdentifyVocabulary("input.txt", vocabulary, startSize);

	std::string word = "road", translate = "";
	std::istringstream input(translate);
	std::ofstream output("output.txt");
	TryToSaveNewTranslation(word, vocabulary, input, output);
	REQUIRE(!vocabulary.contains(word));

	output.close();
	REQUIRE(CompareFiles("output.txt", "outputBadSaveTranslation.txt"));
}

SCENARIO("If save new word in vocabulary, the size changed too")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;

	std::ofstream inputVocabulary("input.txt");
	inputVocabulary << START_VALUES;
	inputVocabulary.close();

	IdentifyVocabulary("input.txt", vocabulary, startSize);

	std::string word = "road", translate = "дорога";
	std::istringstream input(translate);
	std::ofstream output("output.txt");
	TryToSaveNewTranslation(word, vocabulary, input, output);
	REQUIRE(IsVocabularyChanged(vocabulary, startSize));
}

SCENARIO("If save changes, file will be like the model")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;

	std::ofstream inputVocabulary("input.txt");
	inputVocabulary << START_VALUES;
	inputVocabulary.close();

	IdentifyVocabulary("input.txt", vocabulary, startSize);

	std::string word = "road", translate = "дорога";
	std::istringstream input(translate);
	std::ofstream output("output.txt");
	TryToSaveNewTranslation(word, vocabulary, input, output);
	SaveChanges("input.txt", vocabulary);
	REQUIRE(CompareFiles("input.txt", "newInput.txt"));
}