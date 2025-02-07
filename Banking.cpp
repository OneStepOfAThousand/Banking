#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <thread>
#include "DateCompareValue.h"
#include "CSVEditor.h"


#include <filesystem>
namespace fs = std::filesystem;

#include "Banking.h"
#include "Buttons.h"
#include"User.h"

static const std::string configFileName = (std::string)"config.csv";

//void Write() {
//	std::cout << "Write" << std::endl;
//}

void ReadCSVTransactions(std::vector<Transaction>& transactions, const std::string& filePath) {
	std::ifstream fileReader(filePath);
	CSVEditor csvEditor = CSVEditor();
	std::vector<std::string> cells = csvEditor.ReadFile(filePath);
	Transaction tempTransaction = Transaction();
	int count = 0;
	int offset = 13;
	while (true)
	{
		if (offset + count * 12 >= cells.size())
		{
			break;
		}

		transactions.emplace_back(std::stoul(cells[offset + count * 12 + 1])
			, std::stoull(cells[offset + count * 12 + 2]), cells[offset + count * 12 + 3]
			, cells[offset + count * 12 + 4], DateCompareValue(cells[offset + count * 12 + 5])
			, DateCompareValue(cells[offset + count * 12 + 6]), DateCompareValue(cells[offset + count * 12 + 7])
			, cells[offset + count * 12 + 8], cells[offset + count * 12 + 9]
			, std::stof(cells[offset + count * 12 + 10]), std::stof(cells[offset + count * 12 + 11]));
		count++;
	}
}

void StoreCSVTransactions(std::vector<Transaction>& transactions, std::vector<Account>& accounts) {
	Account tempAccount = Account();
	bool accountExists = false;
	bool alreadyAdded = false;

	for (auto& t : transactions)
	{
		accountExists = false;
		alreadyAdded = false;
		for (auto& a : accounts)
		{
			if (a.clearingNumber == t.clearingNum && a.accountNumber == t.accountNum)
			{
				accountExists = true;
				switch (a.AddTransaction(t))
				{
				case 1:
					alreadyAdded = true;
					break;
				default:
					break;
				}

				if (alreadyAdded)
					break;
				else
				{
					a.AddTransaction(t);
					accountExists = true;
				}
			}
		}
		if (!accountExists)
		{
			tempAccount.accountNumber = t.accountNum;
			tempAccount.clearingNumber = t.clearingNum;
			tempAccount.name = t.productType;
			tempAccount.AddTransaction(t);
			accounts.push_back(tempAccount);
			tempAccount = Account();
		}
	}
}

void LoadAll(std::vector<Transaction>& transactionsVector, std::vector<Account>& accountsVector, const std::string& path) {
	std::string tempString = "";
	bool configExists = false;
	std::cout << "Checking for Config.";
	for (const auto& entry : fs::directory_iterator(path)) //Checks wether the config file exists or not, the config file holds information on which .csv files have already been loaded
	{
		tempString = entry.path().generic_string();
		std::cout << entry.path() << std::endl;
		if (tempString.length() > 9 && tempString.substr(tempString.length() - 10, 10) == configFileName) {
			configExists = true;
			break;
		}
	}

	if (configExists)//Check if new transaction files have been added, if so, add them
	{
		std::cout << "Config found.";
		std::vector<std::string> sortedCSVFiles = std::vector<std::string>();
		std::ifstream ifs;
		ifs.open(configFileName);
		bool start = false;
		while (ifs >> tempString)//Check for sorted transactionfiles
		{
			if (start) {
				if (tempString == "Stop")
					break;
				sortedCSVFiles.push_back(tempString);
				continue;
			}

			if (tempString == "Files")
				start = true;
		}

		//Load and sort transactions from unsorted transaction files
		//Todo: add the now sorted files to config
		bool skip = false;
		for (const auto& entry : fs::directory_iterator(path)) //For all files in directory
		{
			std::cout << entry.path() << std::endl;
			tempString = entry.path().generic_string();
			if (tempString.substr(tempString.length() - 4, 4) == ".csv" && tempString.find(configFileName) == tempString.npos) {//Check if csv
				skip = false;
				for (auto& filepath : sortedCSVFiles)
				{
					if (tempString == filepath)
					{
						skip = true;
						break;
					}
				}
				if (skip)
				{
					continue;
				}
				ReadCSVTransactions(transactionsVector, tempString);
				StoreCSVTransactions(transactionsVector, accountsVector);
				transactionsVector = std::vector<Transaction>();
			}
		}
	}
	else //Create Config file and store the file paths for the transaction files
	{
		std::cout << "Config not found.";
		std::ofstream ofs;
		ofs.open(configFileName);
		ofs << "Files ";
		for (const auto& entry : fs::directory_iterator(path))
		{
			std::cout << entry.path() << std::endl;
			tempString = entry.path().generic_string();
			if (tempString.substr(tempString.length() - 4, 4) == ".csv") {
				ReadCSVTransactions(transactionsVector, tempString);
				StoreCSVTransactions(transactionsVector, accountsVector);
				transactionsVector = std::vector<Transaction>();
				ofs << tempString + " ";
			}
		}
		ofs << "Stop ";
		ofs.close();
	}
}

int main()
{
	std::cout << "Hello Banking!" << std::endl;

	std::vector<Transaction> transactions = std::vector<Transaction>();
	std::vector<Account> accounts = std::vector<Account>();

	std::string directoryPath = fs::current_path().generic_string();//Path of the application
	std::string tempString;

	//Checks for the format directory
	bool directoryExists = false;
	std::string formatDirectoryPath = directoryPath + "/format";
	for (const auto& entry : fs::directory_iterator(directoryPath))
	{
		int pathLength = entry.path().generic_string().length();
		if (entry.is_directory() && pathLength > 6 && entry.path().generic_string().substr(pathLength - 6, 7) == (std::string)"format")
		{
			directoryExists = true;
			std::cout << "Format directory already exists." << std::endl;
			std::cout << directoryExists << ":" << entry.path().generic_string().substr(pathLength - 6, 7) << std::endl;
			break;
		}
	}
	if (!directoryExists)
	{
		std::cout << "Creating format directory." << std::endl;
		fs::create_directory(formatDirectoryPath);
	}
	else
	{
		//LoadfromFormatFiles if format files exist
	}

	LoadAll(transactions, accounts, directoryPath);

	std::cout << "Goodbye Banking!\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	//Displays and sorts the maps and sorted vectors
	for (auto& a : accounts) {
		std::cout << "Account: " << a.name << " Account number: " << a.accountNumber << " LastTransaction: " << a.lastTransactionDate.ToString() << " Balance: " << a.currentBalance << std::endl;

		a.SortTransactions();
		a.MapTransactions();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	CSVEditor editor = CSVEditor();
	editor.ReadFile("C:/Users/edwin/source/repos/Banking/Transaktioner_2024-09-12_17-42-35.csv");

	DateCompareValue date = DateCompareValue(2024, 4, 1);
	DateCompareValue date2 = DateCompareValue(2024, 12, 31);
	int tempInt = 0;
	std::cout << "Start" << std::endl;
	std::cout << "Year Month Day" << std::endl;
	std::cin >> tempString;
	tempInt = std::stoi(tempString);
	tempString = "";
	date.SetYearTo(tempInt);
	std::cin >> tempString;
	tempInt = std::stoi(tempString);
	tempString = "";
	date.SetMonthTo(tempInt);
	std::cin >> tempString;
	tempInt = std::stoi(tempString);
	tempString = "";
	date.SetDayTo(tempInt);

	tempInt = 0;
	std::cout << std::endl << "End" << std::endl;
	std::cout << "Year Month Day" << std::endl;
	std::cin >> tempString;
	tempInt = std::stoi(tempString);
	tempString = "";
	date2.SetYearTo(tempInt);
	std::cin >> tempString;
	tempInt = std::stoi(tempString);
	tempString = "";
	date2.SetMonthTo(tempInt);
	std::cin >> tempString;
	tempInt = std::stoi(tempString);
	tempString = "";
	date2.SetDayTo(tempInt);
	std::cout << std::endl;

	DateCompareValue date1 = date;
	std::cout << date1.ToString() << " to " << date2.ToString() << std::endl;
	float balance = 0;
	//Loop through accounts
	for (auto& a : accounts)
	{
		std::map<std::string, unsigned int> occurences = std::map<std::string, unsigned int>(); //Occurences of the refrence in the transactions (store, swish, etc.)
		std::map<std::string, float> occurencesSpending = std::map<std::string, float>(); //Amount spent in total from all the occurences
		while (date1 < date2)
		{
			//std::cout << date1.ToString() << " to " << date2.ToString() << std::endl;

			//Loop through transactions of the account during date1
			for (auto& t : a.mapedTransactions[date1.value])
			{
				//If this is the first found occurence of this refrence, add the refrence to the occurence map
				if (occurences.find(t.refrence) == occurences.end())
				{
					occurences.emplace(t.refrence, 1);
					occurencesSpending.emplace(t.refrence, t.amount);
				}
				else //Else add one to the already existing occurence counter
				{
					occurences[t.refrence] += 1;
					occurencesSpending[t.refrence] += t.amount;
				}
				//t.PrintToConsole();
				balance += t.amount;
			}
			//Progress the date by one.
			date1.ChangeDayTo(date1.Day() + 1);
		}
		std::cout << std::endl << std::endl;
		std::cout << "Account: " << a.name << " : " << balance << std::endl;
		for (auto& o : occurences)
		{
			std::cout << o.first << " : " << o.second << " : " << occurencesSpending[o.first] << std::endl;
		}
		balance = 0;
		date1 = date;
	}

	//Add system for config files, writing and reading


	//SFML
	//sf::Font fond;
	//if (!fond.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
	//	std::cout << "Sadge" << std::endl;
	//}

	///*Button button(sf::Vector2f(50, 30), sf::Vector2f(50, 50), sf::Color::Cyan, sf::Color::Black, sf::Color::Yellow, sf::Color::Yellow, sf::Color::Cyan, sf::Color::Black, "Jeff", fond, 25, Write);*/

	//sf::RenderWindow window(sf::VideoMode(900, 600), "Jeff");
	//sf::Event sfevent;

	//while (window.isOpen())
	//{
	//	window.clear(sf::Color::White);
	//	button.Draw(window);

	//	//hdl vents
	//	while (window.pollEvent(sfevent))
	//	{
	//		switch (sfevent.type)
	//		{
	//		case sf::Event::Closed:
	//			window.close();
	//			break;
	//		default:
	//			break;
	//		}

	//	}
	//	button.Update(window);
	//	window.display();
	//}
}

//unsigned long DateCompareValue(const std::tm & date)
//{
//	unsigned long value = (unsigned long long)date.tm_mday | ((unsigned long long)date.tm_mon << 5) | ((unsigned long long)date.tm_year << 9);
//	return value;
//}
//unsigned long DateCompareValue(unsigned int year, unsigned int month, unsigned int day)
//{
//	unsigned long value = (unsigned long long)day | ((unsigned long long)month<< 5) | ((unsigned long long)year<< 9);
//	return value;
//}
//unsigned int DateCompareValueYear(unsigned long dateCompareValue)
//{
//	unsigned int value = dateCompareValue >> 9;
//	return value;
//}
//unsigned int DateCompareValueMonth(unsigned long dateCompareValue)
//{
//	unsigned int value = (dateCompareValue >> 5)&0b1111;
//	return value;
//}
//unsigned int DateCompareValueDay(unsigned long dateCompareValue)
//{
//	unsigned int value = dateCompareValue & 0b11111;
//	return value;
//	return 0;
//}


