/*
 * Name: Stephen Sams
 * Date Submitted: 03/02/2021
 * Lab Section: 002
 * Assignment Name: Lab 5 - Spell Checker Using Hash Table
 */

#include "stringset.h"
#include <functional> //needed for hash object
#include <string>

using namespace std;

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const {
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const {
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const {
    return size;
}

//Function is designed to insert a passed string into the list if it dosen't already exist in the list
void Stringset::insert(string word) {
    hash<string> hash_var;
    
    if(!find(word)) { //checks to see if the word already exists in the list
        if(num_elems == size) { //if the num_elems already equals the size of the list, then the list is rehashed and the size is doubled
            vector<list<string>> size_double(size * 2);
            
            list<string>::const_iterator j;
            int i = 0;
            
            for(i = 0; i < size; i++) {
                for(j = table[i].begin(); j != table[i].end(); j++) {
                    size_t rehashVariable = hash_var(*j) % (size * 2);
                    size_double[rehashVariable].push_front(*j);
                }
            }
            size *= 2;
            table = size_double;
        }
        size_t indexVariable = hash_var(word) % size; //the index of "word" is calculated
        table[indexVariable].push_front(word); //pushes "word" to the front of the list at the index represented by "indexVariable"
        num_elems++;
    }
}

//Function is designed to check to see if there is a word in the list that matches a passed in string and if so returns true 
// and false otherwise
bool Stringset::find(string word) const {
    hash<string> hash_var;
    bool wordFound = false; //indicates whether a matching word was found 
    size_t indexVariable = hash_var(word) % size; //the index of "word" is calculated
    list<string>::const_iterator i;
    
    for(i = table[indexVariable].begin(); i != table[indexVariable].end(); i++) { //iterates through the list and if a word in the list matches
                                                                                 //the passed in string then the value of "true" is assigned to           //"wordFound"
        if(*i == word) {
            wordFound = true;
        }
    }
   
   return wordFound;
}

//Function is designed remove a word from the list if it matches a passed in string
void Stringset::remove(string word) {
    hash<string> hash_var;
    
    if(find(word)) {
        size_t indexVariable = hash_var(word) % size; //the index of "word" is calculated
        table[indexVariable].remove(word); //deletes the word at the index represented by "indexVariable"
        num_elems--;
    }
}