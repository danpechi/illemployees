/* Madeleine Schwartz
 * July 8th, 2018
 * gender.h
 *
 * interface for getGender.c
 * contracts for methods that assign gender off given male/female names
 */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class GetGender
{
        public:
                GetGender();
                ~GetGender();

                void setDictionaries(string path);
                void run(char u, string path);


        private:
                unordered_set<string> *mnames;
                unordered_set<string> *fnames;
                char usage;

                void parseNames(string input, 
                                string &malen, string &femalen);

                void analyzeGenders(ifstream &infile);
                string assignGender(string name);
                string capWord(string word);
};
