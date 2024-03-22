#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Vocabulary/Vocabulary.h"
#include <fstream>

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
	REQUIRE(!IdentifyVocabulary("nonValid.txt", vocabulary, startSize) && vocabulary.empty());
}

SCENARIO("Opening missing file returns empty map")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	REQUIRE(IdentifyVocabulary("missing.txt", vocabulary, startSize) && vocabulary.empty());
}

SCENARIO("Opening normal file returns map with several values")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	REQUIRE(IdentifyVocabulary("input.txt", vocabulary, startSize) && !vocabulary.empty());
}

SCENARIO("If word not in the vocabulary, it gives false")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	IdentifyVocabulary("input.txt", vocabulary, startSize);

	REQUIRE(!FindWordInVocabulary("paper", vocabulary));
}

SCENARIO("If word in the vocabulary, it gives true")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	IdentifyVocabulary("input.txt", vocabulary, startSize);

	REQUIRE(FindWordInVocabulary("cat", vocabulary));
}

SCENARIO("If save new word in vocabulary, you can translate it")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	IdentifyVocabulary("input.txt", vocabulary, startSize);

	std::string word = "road", translate = "дорога";
	TryToSaveNewTranslation(word, vocabulary);
	REQUIRE(vocabulary[word] == translate);
}

SCENARIO("If save new word in vocabulary, the size changed too")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	IdentifyVocabulary("input.txt", vocabulary, startSize);

	std::string word = "road";
	TryToSaveNewTranslation(word, vocabulary);
	REQUIRE(!IsVocabularyChanged(vocabulary, startSize));
}

SCENARIO("If save changes and then identify vocabulary again, file will be like the model")
{
	std::map<std::string, std::string> vocabulary;
	size_t startSize;
	IdentifyVocabulary("input.txt", vocabulary, startSize);

	std::string word = "road", translate = "дорога";
	TryToSaveNewTranslation(word, vocabulary);
	SaveChanges("input.txt", vocabulary);
	REQUIRE(CompareFiles("input.txt", "newInput.txt"));
}