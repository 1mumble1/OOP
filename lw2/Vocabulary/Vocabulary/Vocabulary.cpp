#include "Vocabulary.h"
#include <iosfwd>
#include <iterator>
#include <algorithm>

const char SEPARATOR = ':';
const std::string YES_SMALL = "y";
const std::string YES_BIG = "Y";

bool IdentifyVocabulary(const std::string& inputFileName, std::map<std::string, std::string>& vocabulary, size_t& startSize)
{
	std::ifstream input(inputFileName);
	if (!input.good())
	{
		return true;
	}
	// обработка файла заблокированного для запсии или чтения

	std::string line;
	while (std::getline(input, line))
	{
		size_t separator = line.find(SEPARATOR);
		if (separator == std::string::npos)
		{
			return false;
		}
		std::string word = line.substr(0, separator);
		std::string translate = line.substr(separator + 1);
		vocabulary[word] = translate;
	}

	if (input.bad())
	{
		return false;
	}

	input.close();
	startSize = vocabulary.size();
	return true;
}

std::string LowerCaseString(const std::string& subject)
{
	std::string subjectLowerCase = subject;
	std::transform(subject.begin(), subject.end(), subjectLowerCase.begin(),
		[](unsigned char ch) { return std::tolower(ch); });

	return subjectLowerCase;
}

bool FindWordInVocabulary(const std::string& word, const std::map<std::string, std::string>& vocabulary)
{
	return vocabulary.contains(LowerCaseString(word));
}

bool IsVocabularyChanged(const std::map<std::string, std::string>& vocabulary, size_t startSize)
{
	return (startSize != vocabulary.size());
}

bool SaveChanges(const std::string& outputFileName, const std::map<std::string, std::string>& vocabulary)
{
	std::ofstream output(outputFileName);
	if (!output.is_open())
	{
		return false;
	}

	for (auto& pair : vocabulary)
	{
		if (!(output << pair.first << SEPARATOR << pair.second << std::endl))
		{
			return false;
		}
	}

	if (!output.flush())
	{
		return false;
	}

	output.close();
	return true;
}

void TryToSaveNewTranslation(const std::string& word, std::map<std::string, std::string>& vocabulary)
{
	std::cout << "Неизвестное слово \'" << word << "\'. Введите перевод или пустую строку для отказа." << std::endl;

	std::string translate;
	std::getline(std::cin, translate);

	if (!translate.empty())
	{
		vocabulary.insert({ LowerCaseString(word), translate});
		std::cout << "Слово \'" << word << "\' сохранено в словаре как \'" << translate << "\'." << std::endl;
	}
	else
	{
		std::cout << "Слово \'" << word << "\' проигнорировано." << std::endl;
	}
}

int TryToSaveChanges(const std::string& outputFileName, const std::map<std::string, std::string>& vocabulary, size_t startSize)
{
	if (!IsVocabularyChanged(vocabulary, startSize))
	{
		return 0;
	}

	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;

	std::string line;
	std::getline(std::cin, line);

	if (line != YES_BIG && line != YES_SMALL)
	{
		std::cout << "Изменения не сохранены. До свидания." << std::endl;
		return 0;
	}

	if (!SaveChanges(outputFileName, vocabulary))
	{
		std::cout << "Failed to write data in vocabulary." << std::endl;
		return 1;
	}

	std::cout << "Изменения сохранены. До свидания." << std::endl;
	return 0;
}