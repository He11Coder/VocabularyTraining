#include "Word.h"

Word::Word(bool mandatory_meaning, std::string eng, std::string rus1, std::string rus2) : m_mandatory_meaning(mandatory_meaning), m_eng(eng), m_rus1(rus1), m_rus2(rus2)
{
}

const std::string Word::getRus()
{
	if (m_rus2 == "0")
		return m_rus1;
	else
		return m_rus1 + ", " + m_rus2;
}

const std::string Word::getEng() 
{
	return m_eng;
}