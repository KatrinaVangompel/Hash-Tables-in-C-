#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stock.h"

class hashTable
{
public:

	//Constructors and destructor.
	hashTable();
	hashTable(char * fileName);
	hashTable(const hashTable& aTable);
	~hashTable();

	//mutator functions
	void add(const stock& aStock);
	bool remove(char * tickerSymbol);
	bool modify(char * tickerSymbol, float newNetAssetVal, char * newDate, float newDateReturn);
	void writeOut(char *fileName);

	//accessor functions
	void display();
	bool retrieve(char * tickerSymbol, stock& aStock);

private:
	struct node
	{
		stock item;
		node * next;
		int chainSize; //int to hold a node's position in a chain of nodes with the same hash value

		node(const stock& aStock)
		{
			item = aStock;
			next = NULL;
			int chainSize = 0;
		}

	};
	node **table;
	node *first;

	int size;
	void initializeTable();
	int calculateIndex(char * tickerSymbol)const;
};
#endif