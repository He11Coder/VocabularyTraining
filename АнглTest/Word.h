#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <Windows.h>
#include <conio.h>

class Word
{
public:
	bool m_mandatory_meaning;

	std::string m_eng;

	std::string m_rus1;

	std::string m_rus2;

	Word(bool mandatory_meaning, std::string eng, std::string rus1, std::string rus2 = "0");

private:
	const std::string getRus();

	const std::string getEng();
};