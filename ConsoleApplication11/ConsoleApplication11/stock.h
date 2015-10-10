#ifndef stock_H
#define stock_H
#include <iostream>
using namespace std;
class stock
{
public:

	//constructors and destructor
	stock();
	stock(const stock& aStock);
	~stock();

	//accessor functions
	void getName(char * name) const;
	void getTicker(char * ticker) const;
	float getnetAssetValues(void) const;
	void getDate(char *date) const;
	float getdateReturn(void) const;

	//mutator functions
	void setName(const char * name);
	void setTicker(const char * ticker);
	void setNetAssetValues(float netAssetValues);
	void setDate(const char *date);
	void setDateReturn(float dateReturn);

	//operator overloaders
	friend ostream& operator<< (ostream& out, const stock& aStock);
	const stock& operator=(const stock& aStock);	//overload assignment operator

private:
	char * name;
	char * ticker;
	char * date;
	float netAssetValues;
	float dateReturn;
};

#endif