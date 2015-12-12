
Using hash tables with C++
==========================

A hashtable, on the other hand, has an associated function that takes an entry, and reduces it to a number, a hash-key. This number is then used as an index into the array, and this is where you store the entry.A hashtable revolves around an array, which initially starts out empty. Empty does not mean zero length, the array starts out with a size, but all the elements in the array contains nothing.

KatrinaVangompel - FullstackDeveloper at http://basementnow.ca/

Source :

class HashEntry {
private:
      int key;
      int value;
public:
      HashEntry(int key, int value) {
            this->key = key;
            this->value = value;
      }
 
      int getKey() {
            return key;
      }
 
      int getValue() {
            return value;
      }
};
 
const int TABLE_SIZE = 128;
 
class HashMap {
private:
      HashEntry **table;
public:
      HashMap() {
            table = new HashEntry*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
      }
 
      int get(int key) {
            int hash = (key % TABLE_SIZE);
            while (table[hash] != NULL && table[hash]->getKey() != key)
                  hash = (hash + 1) % TABLE_SIZE;
            if (table[hash] == NULL)
                  return -1;
            else
                  return table[hash]->getValue();
      }
 
      void put(int key, int value) {
            int hash = (key % TABLE_SIZE);
            while (table[hash] != NULL && table[hash]->getKey() != key)
                  hash = (hash + 1) % TABLE_SIZE;
            if (table[hash] != NULL)
                  delete table[hash];
            table[hash] = new HashEntry(key, value);
      }     
 
      ~HashMap() {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};
