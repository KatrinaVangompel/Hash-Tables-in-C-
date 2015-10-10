/*
NAME: Colleen Minor
CLASS: CS 260- Data Structures
ASSIGNMENT: Lab 3
*/

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "stock.h"
#include "hashtable.h"
#include <iostream>
using namespace std;

void displayMenu();
char readInCommand();
void processCommand(char command, hashTable &theTable);
void getStock(stock &newStock);
void readString(const char prompt[], char inputString[], int maxChar);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	char fileName[] = "data.dat";
	char command;
	hashTable theTable(fileName);
	displayMenu();


	command = readInCommand();

	while (command != 'q')
	{
		processCommand(command, theTable);
		displayMenu();
		command = readInCommand();
	}

	cout << "\nThat's all!" << endl << endl;
	return 0;
}

void displayMenu()
{
	cout << "Welcome back to stock watcher! Options: "
		"\n\tl: List all stocks/funds." << endl
		<< "\tm: Modify a stock." << endl
		<< "\ta: Add a new stock." << endl
		<< "\ts: Search for information on a stock or fund." << endl
		<< "\tr: Remove a stock from the list." << endl
		<< "\tw: Write your updated information to the file." << endl
		<< "\tq: Quit." << endl;
	return;
}

char readInCommand()
{
	char   command;

	cout << endl << "Please enter the command (l, a, m, s, r, w or q): ";
	cin >> command;
	cin.ignore(100, '\n');
	return tolower(command);
}

void processCommand(char command, hashTable &theTable)
{
	stock newStock;
	char ticker[101];
	char fileName[] = "data.dat";


	switch (command)
	{
	case 'a':
		cout << "\nYou chose add a stock or fund. \n" << endl;
		getStock(newStock);
		theTable.add(newStock);
		break;

	case 'm':
		cout << "\nYou chose to modify a stock. \n" << endl;
		getStock(newStock);
		theTable.add(newStock);
		break;

	case 'l':
		theTable.display();
		break;

	case 's':
		readString("Enter the ticker of the stock that you would like to retreive information on: ", ticker, 101);
		if (theTable.retrieve(ticker, newStock) != true)
		{
			cout << endl << "Stock or fund not found." << endl;
		}
		break;

	case 'r':
		readString("Enter the ticker of the stock/fund that you wish to remove: ", ticker, 101);
		theTable.remove(ticker);
		break;

	case 'w':
		theTable.writeOut(fileName);


	default: cout << endl << "Command not recognized. You will now be returend to the main menu." << endl;
		break;
	}
}

/*
Loads newStock with data from the user input.
*/
void getStock(stock& newStock)
{
	char name[101];
	char ticker[6];
	char date[101];
	float dateReturn, assetValues;

	cout << endl;
	readString("Please enter the stock/fund's ticker: ", ticker, 6);
	readString("Please enter the stock/fund's new name: ", name, 101);

	cout << "Please enter the new return rate since the start of the year: ";
	cin >> dateReturn;
	cin.ignore(101, '\n');
	cout << "Please enter the new total asset values: ";
	cin >> assetValues;
	cin.ignore(101, '\n');
	readString("Please enter the date of this information: ", date, 101);

	newStock.setName(name);
	newStock.setTicker(ticker);
	newStock.setDate(date);
	newStock.setNetAssetValues(assetValues);
	newStock.setDateReturn(dateReturn);

	cout << "\nData received. You will now be returned to the main menu. \n" << endl;
}

/*
readString prompts the user for data and reads into the inputString array that's sent in.
Precondition: prompt is a string to be outputted to the console window, inputString is a char array to be filled,
and maxChar is an int representing the maximum number of characters to be read.
Postcondition: inputString contains user-input.
*/
void readString(const char prompt[], char inputString[], int maxChar)
{
	char *outputString;
	cout << prompt;
	cin.get(inputString, maxChar, '\n');
	outputString = new char[strlen(inputString) + 1];
	strcpy(outputString, inputString);
	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << endl << prompt;
		cin.get(outputString, maxChar, '\n');
	}
	cin.ignore(100, '\n');
}
