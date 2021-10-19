#pragma once
#include "Word.h"

class Application
{
private:
	std::vector<Word> m_word_bank;

public:
	void run();

private:
	void createSet(std::string filename);

	void printSet();

	void fromRusTrain();

	void fromEngTrain();
};