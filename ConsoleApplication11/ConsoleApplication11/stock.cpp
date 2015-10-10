#include "stock.h"
#include <iostream>
#include <iomanip>
using namespace std;

/*
Default constructor.
*/
stock::stock() :name(NULL), ticker(NULL), netAssetValues(0), date(NULL), dateReturn(0)
{

}

/*
Copy Constructor.
*/

stock::stock(const stock& aStock) :name(NULL), ticker(NULL), date(NULL)
{
	setName(aStock.name);
	setTicker(aStock.ticker);
	setNetAssetValues(aStock.netAssetValues);
	setDate(aStock.date);
	setDateReturn(aStock.dateReturn);
}

/*
Operator overloader for assignment operator. Makes it so that one stock object can be assigned to another.
*/

const stock& stock::operator=(const stock& aStock)
{
	if (this == &aStock)
		return *this;
	else
	{
		setName(aStock.name);
		setTicker(aStock.ticker);
		setNetAssetValues(aStock.netAssetValues);
		setDateReturn(aStock.dateReturn);
		setDate(aStock.date);
		return *this;
	}
}

/*
Destructor.
*/
stock::~stock()
{
	if (name)
		delete[] name;
	if (ticker)
		delete[] ticker;
	if (date)
		delete[] date;
}

/*
Load sent in char array with instance object's name variable. 
*/
void stock::getName(char * name)const
{
	strcpy(name, this->name);
}

void stock::getDate(char * date)const
{
	strcpy(date, this->date);
}


void stock::getTicker(char * ticker)const
{
	strcpy(ticker, this->ticker);
}

float stock::getnetAssetValues(void) const
{
	return netAssetValues;
}

float stock::getdateReturn(void) const
{
	return dateReturn;
}

/*
Load instance object's name variable with sent in char array. 
*/
void stock::setName(const char * name)
{
	if (this->name)
		delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void stock::setDate(const char * date)
{
	if (this->date)
		delete[] this->date;

	this->date = new char[strlen(date) + 1];
	strcpy(this->date, date);
}


void stock::setTicker(const char * ticker)
{
	if (this->ticker)
		delete[] this->ticker;
	this->ticker = new char[strlen(ticker) + 1];
	strcpy(this->ticker, ticker);
}

void stock::setNetAssetValues(float netAssetValues)
{
	this->netAssetValues = netAssetValues;
}

void stock::setDateReturn(float dateReturn)
{
	this->dateReturn = dateReturn;
}

/*
Operator overloader for stock objects. When cout is used on a stock object, the stock's items will be displayed.
*/
ostream& operator<< (ostream& out, const stock& aStock)
{
	out << "Name: " << aStock.name << endl << "Ticker: " << aStock.ticker << endl << "Net asset values: " << aStock.netAssetValues << endl << "Date to return: " << aStock.dateReturn << "%" << endl << "Date: " << aStock.date << "\n\nRecord Finished\n===========\n\n";
	return out;
}

