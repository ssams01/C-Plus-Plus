/*
 * Name: Stephen Sams
 * Date Submitted: 03/02/2021
 * Lab Section: 002
 * Assignment Name: Lab 5 - Spell Checker Using a Hast Table
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 #include <string>
 
 using namespace std;
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
 int main()
 {
     Stringset wordlist;
     testStringset(wordlist);
     return 0;
 }
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 //Function is designed to get words from a file and then insert them into our hash table
 void loadStringset(Stringset& words, string filename) {
     string newWord = " "; //meant to store the value of the string that gets read in from the file
     ifstream inputFile(filename); //meant to access the file that has the words needed to be read in
     
     while(getline(inputFile, newWord)) { //while the input file still has words to read in, a word is extracted and place in "newWord", then 
                                         //calls the insert() function passing in "newWorld" to be added to the hash table
         words.insert(newWord);
     }
     
     inputFile.close(); //closes the input file 
 }
 
 //Function is designed loop through all possible words that are 1 letter off of the word passed in and if its in the hast table, it
 //gets added to a list of possible corrections
 vector<string> spellcheck(const Stringset& words, string word) {
     vector<string> alternateWords; //meant to hold the list of possible corrective words
     string comparisonWord = word; //used in the comparison of the passed in word and the "possible corrections"
     const int WORDS_IN_AlPHABET = 26; //used to store the number of letters in the alphabet
     int i = 0;
     int j = 0;
     
     for(i = 0; i < (word.length()); i++) {
         for(j = 0; j < WORDS_IN_AlPHABET; j++) {
             if(comparisonWord[i] == 'z') { //checks to see if the character indicated by index "i" in the string is the letter z then it
                                            //changes it to letter a...
                 comparisonWord[i] = 'a';
             }
             else { //...if not just advance the character indicated by index "i" to the next letter in the alphabet
                 comparisonWord[i] = comparisonWord[i] + 1;
             }
             
             if(words.find(comparisonWord) && word != comparisonWord) { //checks to see if the alternate to the passed in word is in the hash
                                                                        //table and also if the passed in word doesn't equal the alternate word
                                                                        //,and if so adds it the list of possible corrections
                 alternateWords.push_back(comparisonWord);
             }
         }
     }
     
     return alternateWords; //returns the list of possible corrections
 }