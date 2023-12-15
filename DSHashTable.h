/*
 * Rebecca Kuhlman
 * 4/6/2021
 * CS 2341
 * DSHashTable class that defines variables and functions to create
 * a hash table as an array of vectors of Entries
 */
#ifndef AVL_DSHASHTABLE_H
#define AVL_DSHASHTABLE_H

#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <algorithm>

#define DEBUG false

template<class T, class B>
class DSHashTable {
private:
    //Entry object with a key and set<value> pair
    struct Entry{
        T key;
        set<B> value;
        Entry(T t, set<B> b):key(t), value(b){}
    };
    int capacity;
    int size;
    vector<Entry>* table = nullptr;
    set<T> keys;

public:
    DSHashTable();
    DSHashTable(const DSHashTable<T, B>&);
    ~DSHashTable();
    void clear();
    void rehash();
    void insert(const T& key, const set<B>& value);
    void insert(const T& key, const B& value);
    set<B>& get(const T&);
    bool contains(const T&);
    int getSize();
    inline set<T> getKeys(){return keys;}
    DSHashTable<T, B>& operator= (const DSHashTable<T, B>&);
};


#endif //AVL_DSHASHTABLE_H

/**
 * Creates a hash table object
 */
template<class T, class B>
DSHashTable<T, B>::DSHashTable(){
    size = 0;
    capacity = 100;
    table = new vector<Entry>[capacity];
}

/**
 * Copies given table to new hash table object
 * @param newTable table to copy
 */
template<class T, class B>
DSHashTable<T, B>::DSHashTable(const DSHashTable<T, B>& newTable){
    table = newTable.table;
    capacity = newTable.capacity;
    size = newTable.size;
    keys = newTable.keys;
}

/**
 * Copies given table to new hash table object
 * @param newTable table to copy
 * @return the object created
 */
template<class T, class B>
DSHashTable<T, B>& DSHashTable<T, B>::operator= (const DSHashTable<T, B>& newTable){
    clear();
    table = newTable.table;
    capacity = newTable.capacity;
    size = newTable.size;
    keys = newTable.keys;
    return *this;
}

//Destructor
template<class T, class B>
DSHashTable<T, B>::~DSHashTable(){
    if(table != nullptr){
        delete[] table;
        size = 0;
        capacity = 100;
        table = nullptr;
    }
}

//Clears object of all elements and resets it
template<class T, class B>
void DSHashTable<T, B>::clear(){
    if(table != nullptr){
        delete[] table;
        size = 0;
        capacity = 100;
        table = nullptr;
    }
    table = new vector<Entry>[capacity];
}

/**
 * Increases the capacity of the table and rehashs each element currently in the table
 */
template<class T, class B>
void DSHashTable<T, B>::rehash(){
    int newCapacity = capacity * 2;
    auto* newTable = new vector<Entry>[newCapacity];
    for(int index = 0; index < capacity; index++){
        vector<Entry> entries = table[index];
        if(!entries.empty()){
        for(int j = 0; j < entries.size(); j++){
            Entry checkEntry = entries.at(j);
            auto hash_value = std::hash<T>{}(checkEntry.key);
            int loc = hash_value % newCapacity;
            if(DEBUG) std::cout << checkEntry.key << ": " << hash_value << std::endl;
            newTable[loc].push_back(checkEntry);
            }
        }
    }
    table = newTable;
    capacity = newCapacity;
}


/**
 * Inserts a new element into the table
 * @param key New key to add to the table
 * @param newValue New value to add to the table
 */
template<class T, class B>
void DSHashTable<T, B>::insert(const T& key, const set<B>& newValue){
    if((size + 1) / capacity >= 1)
        rehash();
    Entry newEntry(key, newValue);
    auto hash_value = std::hash<T>{}(key);
    int loc = hash_value % capacity;
    if(DEBUG) std::cout << key << ": " << hash_value << std::endl;
    table[loc].push_back(newEntry);
    size++;
    keys.insert(key);
}

/**
 * Inserts a new element into the table
 * @param key New key to add to the table
 * @param newValue New value to add to the table
 */
template<class T, class B>
void DSHashTable<T, B>::insert(const T& key, const B& newValue){
    if((size + 1) / capacity >= 1)
        rehash();
    auto hash_value = std::hash<T>{}(key);
    int loc = hash_value % capacity;
    if(DEBUG) std::cout << key << ": " << hash_value << std::endl;
    bool added = false;
    for(auto &check : table[loc]){
        if(check.key == key){
            check.value.insert(newValue);
            added = true;
        }
    }
    if(!added){
        set<B> newSet;
        newSet.insert(newValue);
        Entry newEntry(key, newSet);
        table[loc].push_back(newEntry);
    }
    size++;
    keys.insert(key);
}

/**
 * Gets a value from a given key
 * @param key key to find value with
 */
template<class T, class B>
set<B>& DSHashTable<T, B>::get(const T& key){
    int loc = std::hash<T>{}(key) % capacity;
    for(auto &check : table[loc]){
        if(check.key == key)
            return check.value;
    }
    throw std::out_of_range("Key doesn't exist");
}

/**
 * Sees if table contains key
 * @param key key to find
 * @return true if found, false otherwise
 */
template<class T, class B>
bool DSHashTable<T, B>::contains(const T& key){
    int loc = std::hash<T>{}(key) % capacity;
    for(auto &check : table[loc]){
        if(check.key == key)
            return true;
    }
    return false;
}

//returns size
template<class T, class B>
int DSHashTable<T, B>::getSize(){
    return size;
}

