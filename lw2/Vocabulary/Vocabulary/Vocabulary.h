#pragma once
#include <map>
#include <string>
#include <fstream>
#include <iostream>

bool IdentifyVocabulary(const std::string& inputFileName, std::map<std::string, std::string>& vocabulary, size_t& startSize);
std::string LowerCaseString(const std::string& subject);
bool FindWordInVocabulary(const std::string& word, const std::map<std::string, std::string>& vocabulary);
bool IsVocabularyChanged(const std::map<std::string, std::string>& vocabulary, size_t startSize);
bool SaveChanges(const std::string& outputFileName, const std::map<std::string, std::string>& vocabulary);
void TryToSaveNewTranslation(const std::string& word, std::map<std::string, std::string>& vocabulary, std::istream& input, std::ostream& output);
int TryToSaveChanges(const std::string& outputFileName, const std::map<std::string, std::string>& vocabulary, size_t startSize, 
	std::istream& input, std::ostream& output);