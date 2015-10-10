#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


/*
Default constructor.
*/
hashTable::hashTable() : size(0)
{
	table = new node*[101];
	int i;
	for (i = 0; i < 101; i++)
		table[i] = NULL;
}

/*
Constructor with filename.
*/
hashTable::hashTable(char * fileName) : size(0)
{
	ifstream in;
	stock currstock;
	char name[100];
	char ticker[6];
	char date[100];
	float netAssetValues;
	float dateReturn;

	initializeTable();
	in.open(fileName);
	if (in.good() != true)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}

	in.get(name, 100, ';');
	while (in.eof() != true)
	{
		in.ignore(100, ';');
		in.get(ticker, 6, ';');
		in.ignore(100, ';');
		in >> netAssetValues;
		in.ignore(100, ';');
		in.get(date, 100, ';');
		in.ignore(100, ';');
		in >> dateReturn;
		in.ignore(100, '\n');
		currstock.setName(name);
		currstock.setTicker(ticker);
		currstock.setDate(date);
		currstock.setNetAssetValues(netAssetValues);
		currstock.setDateReturn(dateReturn);

		add(currstock);

		in.get(name, 100, ';');
	}
	in.close();
}

/*
Deep copy constructor.
*/
hashTable::hashTable(const hashTable& aTable) :size(aTable.size)
{
	table = new node*[101];
	int i;
	for (i = 0; i < 101; i++)
	{
		if (aTable.table[i] == NULL)
			table[i] = NULL;
		else
		{
			table[i] = new node(aTable.table[i]->item);
			node * srcNode = aTable.table[i]->next;
			node * destNode = table[i];
			while (srcNode)
			{
				destNode->next = new node(srcNode->item);
				destNode = destNode->next;
				srcNode = srcNode->next;
			}
			destNode->next = NULL;
		}
	}
}

/*
Destructor.
*/
hashTable::~hashTable()
{
	int i;
	for (i = 0; i<101; i++)
	{
		node * head = table[i];
		node * curr;
		while (head)
		{
			curr = head->next;
			head->next = NULL;
			delete head;
			head = curr;
		}
	}
	delete[] table;
}

/*
Initializes each head of the linked list.
*/
void hashTable::initializeTable()
{
	table = new node*[101];
	int i;
	for (i = 0; i < 101; i++)
		table[i] = NULL;
}

/*
Adds a new element to the hash table. If the element is already taken, an list starting from that element is linked alphebetically with the node pointer *next. 
*/
void hashTable::add(const stock& aStock)
{
	char tickerSymbol[100];
	char otherTicker[100];
	aStock.getTicker(tickerSymbol); //populate local char array with the key
	int index = calculateIndex(tickerSymbol);
	int idx;
	int alphebetize = 10000;
	int countOther = 0;
	int countNew = 0;
	node *curr, *root;
	node *newNode = new node(aStock);
	if (table[index] == NULL)
	{
		table[index] = newNode;
	}
	else if (table[index] != NULL)
	{
		curr = table[index];
		while (curr != NULL) //until the end of the chain is reached...
		{
			root = table[index];
			alphebetize = 260000;
			curr->item.getTicker(otherTicker);
			for (idx = 0; idx < 5; idx++){ //code to calculate which is alphabetically sooner
				countOther += otherTicker[idx] * alphebetize;
				countNew += tickerSymbol[idx] * alphebetize;
				alphebetize = alphebetize / 26;
			}
			if (countNew <= countOther)
			{ //if the new ticker produced a smaller number than the old ticker (making it alphabetically earlier) or equal to it...
				node *prev = NULL;
				if (root != curr)
				{
					while (root->next != curr)
						root = root->next;
					prev = root;
				}
				newNode->next = curr;
				if (prev == NULL)
					table[index] = newNode;
				else
					prev->next = newNode;
				break;
			}
			curr = curr->next;
			newNode->chainSize++; //increment the chain position
		}
		if (curr == NULL)
		{
			node * prev = NULL;
			root = table[index];
			while (root->next != NULL)
			{
				root = root->next;
			}
			prev = root;
			prev->next = newNode;
		}
	}
	size++;
}

/*
Function to modify the private members of a given node in the hash table. Returns true if modification is successful.
*/
bool hashTable::modify(char * tickerSymbol, float newNetAssetVal, char * newDate, float newDateReturn)
{
	int index;
	node *curr;
	index = calculateIndex(tickerSymbol);
	curr = table[index];
	curr->item.setNetAssetValues(newNetAssetVal);
	curr->item.setDate(newDate);
	curr->item.setDateReturn(newDateReturn);

	return true;
}

/*
displays all stocks/hedges
*/
void hashTable::display()
{
	int i;
	node * curr;
	for (i = 0; i < 101; i++)
	{
		for (curr = table[i]; curr; curr = curr->next)

			cout << curr->item << endl;
	}
}

/*
The hash function.
In: char array to be used as hash key
Out: A hash key less than 101
*/
int hashTable::calculateIndex(char * tickerSymbol)const
{
	int total = 0;
	int len = strlen(tickerSymbol);
	int index;
	for (index = 0; index<len; index++)
	{
		total += tickerSymbol[index];
	}
	return total % 101;
}

/*
Removes a stock from the hash table.
*/
bool hashTable::remove(char * tickerSymbol)
{
	int index = calculateIndex(tickerSymbol);
	node * curr = table[index];
	node * prev = NULL;
	char id[100];
	while (curr)
	{
		curr->item.getTicker(id);
		if (strcmp(tickerSymbol, id) == 0)
		{
			if (!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;

			curr->next = NULL;
			delete curr;
			size--;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;
}

/*
Returns information on any the stock item that matches the key.
*/
bool hashTable::retrieve(char *tickerSymbol, stock & aStock)
{
	int index = calculateIndex(tickerSymbol);
	node * curr = table[index];
	char id[100];
	while (curr)
	{
		curr->item.getTicker(id);
		if (strcmp(tickerSymbol, id) == 0)
		{
			aStock = curr->item;

			cout << endl << "Here is the information on " << tickerSymbol << ": " << endl;
			cout << curr->item << endl << endl;
			return true;
		}
		else
			curr = curr->next;
	}
	return false;
}

/*
Writes all stock objects in the table in main memory to an external file.
*/
void hashTable::writeOut(char *fileName)
{
	ofstream out;

	out.open(fileName);
	if (!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	int i;
	char name[100];
	char ticker[100];
	char date[100];
	node * curr;
	for (i = 0; i<101; i++)
	{
		for (curr = table[i]; curr; curr = curr->next)
		{
			curr->item.getTicker(ticker);
			curr->item.getName(name);
			curr->item.getDate(date);
			out << name << ';' << ticker << ';' << curr->item.getnetAssetValues() << ';' << date << ';' << curr->item.getdateReturn() << '\n';
		}
	}
	out.close();
}



