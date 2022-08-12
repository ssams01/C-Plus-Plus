/*
 * Name: Stephen Sams
 * Date Submitted: 03/02/2021
 * Lab Section: 002
 * Assignment Name: Lab 5 - Spell Checker Using a Hash Table
 */

#pragma once

#include <string>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

//Stringset class, do not modify definitions for existing members
class Stringset
{
    private:
        vector<list<string>> table;
        int num_elems;
        int size;
    public:
        Stringset();
        vector<list<string>> getTable() const;
        int getNumElems() const;
        int getSize() const;
        void insert(string word);
        bool find(string word) const;
        void remove(string word);
};