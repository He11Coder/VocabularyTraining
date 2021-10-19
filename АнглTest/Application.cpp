#include "Application.h"

void Application::run()
{
	bool flag = true;
	int k;
	while (flag)
	{
		std::cout << std::endl << "1 - create a set of words" << std::endl;
		std::cout << "2 - start translation training from Russian to English" << std::endl;
		std::cout << "3 - start translation training from English to Russian" << std::endl;
		std::cout << "4 - close the application" << std::endl;
		std::cin >> k;
		std::cin.get();

		switch (k)
		{
		case 1:
		{
			std::string filename;
			std::cout << std::endl << "Please, enter the name of Vocabulary file located in the project directory (without extension):" << std::endl;
			getline(std::cin, filename);
			filename += ".txt";
			createSet(filename);
			std::cout << std::endl << "Word bank has been successfully created!\nYou can start training." << std::endl;
			break;
		}
		case 2:
			if (m_word_bank.empty())
				std::cout << std::endl << "You haven't created a set of words. Choose the first point of menu and try again!" << std::endl;
			else
			{
				fromRusTrain();
				std::cout << "\nTraining complete!\n";
			}
			break;
		case 3:
			if (m_word_bank.empty())
				std::cout << std::endl << "You haven't created a set of words. Choose the first point of menu and try again!" << std::endl;
			else
			{
				fromEngTrain();
				std::cout << "\nTraining complete!\n";
			}
			break;
		case 4:
			flag = false;
			break;
		default:
			std::cout << "\nYou've chosen a non-existent point of menu. Try again!\n";
			break;
		}
	}
	std::cout << "\nApplication closed!\n";
}

void Application::createSet(std::string filename)
{
	std::ifstream dictionary(filename);
	std::vector<Word> Bank;
	std::string word_pair;

	if (!dictionary)
	{
		std::cout << "Some file error has occurred!";
	}
	else
	{
		while (dictionary)
		{
			getline(dictionary, word_pair);
			if (word_pair == "")
				continue;
			word_pair.erase(word_pair.begin());

			auto iter = word_pair.begin();
			std::string eng;
			std::string rus1;

			while (*iter != '/')
			{
				eng.push_back(*iter);
				++iter;
			}

			eng.pop_back();

			iter += 2;
			while ((iter != word_pair.end()) && (*iter != '|') && (*iter != '&'))
			{
				rus1.push_back(*iter);
				++iter;
			}

			bool flag;
			std::string rus2;
			if (iter != word_pair.end())
			{
				rus1.pop_back();

				if (*iter == '|')
					flag = false;
				else
					flag = true;

				iter += 2;
				while (iter != word_pair.end())
				{
					rus2.push_back(*iter);
					++iter;
				}

				Bank.emplace_back(flag, eng, rus1, rus2);
			}
			else
				Bank.emplace_back(false, eng, rus1);
		}
		m_word_bank = std::move(Bank);
		m_word_bank.pop_back();
	}
}

void Application::printSet()
{
	for (auto iter = m_word_bank.cbegin(); iter != m_word_bank.cend(); ++iter)
	{
		if (iter->m_rus2 == "0")
			std::cout << iter->m_eng << " - " << iter->m_rus1 << std::endl;
		else
			std::cout << iter->m_eng << " - " << iter->m_rus1 << ", " << iter->m_rus2 << std::endl;
	}
}

void Application::fromRusTrain()
{
	std::cout << "\nYou've chosen Russian->English training mode!\nYou should write English equivalent of each Russian word and press Enter.\n\n";
	std::cout << "Don't forget to use \"to\" before the verb =))\n\n";
	std::cout << "If you want to stop training enter /stop instead of translation\n";
	std::cout << "_________________________________________________________________________" << std::endl;
	std::random_device rd;
	std::mt19937 r(rd());
	std::shuffle(m_word_bank.begin(), m_word_bank.end(), r);

	std::string ans;
	for (auto iter = m_word_bank.begin(); iter != m_word_bank.end(); ++iter)
	{
		if (iter->m_rus2 != "0")
			std::cout << iter->m_rus1 << ", " << iter->m_rus2 << " - ";
		else
			std::cout << iter->m_rus1 << " - ";

		getline(std::cin, ans);
		if (ans == "/stop")
			break;

		if (ans != iter->m_eng)
			std::cout << "Incorrectly! The right translation is \"" << iter->m_eng << "\"\n";

		std::cout << std::endl;
	}
}

void Application::fromEngTrain()
{
	std::cout << "\nYou've chosen English->Russian training mode!\nYou should write Russian equivalent of each English word and press Enter.\n\n";
	std::cout << "If a word or an expression has another meaning, you should enter both meanings separating by comma and space (for example \"light - светлый, легкий\")\n";
	std::cout << "Otherwise (if you forgot the second meaning) missing answer will be displayed to you.\n\n";
	std::cout << "If you want to stop training enter /stop instead of translation\n";
	std::cout << "_____________________________________________________________________________________" << std::endl;
	std::random_device rd;
	std::mt19937 r(rd());
	std::shuffle(m_word_bank.begin(), m_word_bank.end(), r);

	std::string ans;
	for (auto iter = m_word_bank.begin(); iter != m_word_bank.end(); ++iter)
	{
		std::cout << iter->m_eng << " - ";

		getline(std::cin, ans);
		if (ans == "/stop")
			break;

		if ((iter->m_mandatory_meaning == true) && (ans == iter->m_rus1))
			std::cout << "This word has another meaning - " << "\"" << iter->m_rus2 << "\"\n";
		else if ((iter->m_mandatory_meaning == true) && (ans == iter->m_rus2))
			std::cout << "This word has another meaning - " << "\"" << iter->m_rus1 << "\"\n";
		else if ((iter->m_mandatory_meaning == true) && (ans != iter->m_rus1 + ", " + iter->m_rus2) && (ans != iter->m_rus2 + ", " + iter->m_rus1))
		{
			if (iter->m_rus2 != "0")
				std::cout << "Incorrectly! The right translation is \"" << iter->m_rus1 << ", " << iter->m_rus2 << "\"\n";
			else
				std::cout << "Incorrectly! The right translation is \"" << iter->m_rus1 << "\"\n";
		}

		if ((iter->m_mandatory_meaning == false) && (ans != iter->m_rus1) && (ans != iter->m_rus2) && (ans != iter->m_rus1 + ", " + iter->m_rus2) && (ans != iter->m_rus2 + ", " + iter->m_rus1))
		{
			if (iter->m_rus2 != "0")
				std::cout << "Incorrectly! The right translation is \"" << iter->m_rus1 << ", " << iter->m_rus2 << "\"\n";
			else
				std::cout << "Incorrectly! The right translation is \"" << iter->m_rus1 << "\"\n";
		}
			
		std::cout << std::endl;
	}
}