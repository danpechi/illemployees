/* Madeleine Schwartz
 * July 8th, 2018
 * getGender.cpp
 *
 * implementation of getGender.h
 * methods to assign gender based off given lists of male/female names
 */

#include "getGender.h"

/*
 * GetGender: constructs GetGender class by building unordered sets for
 * male and female names
 */
GetGender::GetGender()
{
        mnames = new unordered_set<string>;
        fnames = new unordered_set<string>;
}

/*
 * ~GetGender: destructor for GetGender class, frees data on the heap 
 */
GetGender::~GetGender()
{
        delete mnames;
        delete fnames;
}

/*
 * setDictionaries: takes in a string of a file pathway, storing its
 * contents in the gender/name dictionaries, retunr nothing
 */
void GetGender::setDictionaries(string filename)
{
        ifstream infile;
        string input, malen, femalen;
        infile.open(filename);
        
        if (infile.is_open() == false) {
                cerr << "Error opening file\n";
                return;
        }

        infile >> input;
        
        /* input distinct male and female names to respective maps */
        for (infile >> input; infile.eof() == false; infile >> input) {
                malen = "";
                femalen = "";
                parseNames(input, malen, femalen);

                if (fnames->find(malen) != mnames->end()) {
                        fnames->erase(malen);
                }
                else {
                        mnames->insert(malen);
                }
                
                if (mnames->find(femalen) != mnames->end()) {
                        mnames->erase(femalen);
                }
                else {
                        fnames->insert(femalen);
                }
        }
        
        infile.close();
}

/*
 * parseNames: takes the string input, string of the male name by
 * reference, and string of the female name by reference. Parses
 * the input, putting the male and female names in the referenced
 * parameters, returns nothing
 */
void GetGender::parseNames(string input, string &malen, string &femalen)
{
        int length = input.length();
        int i;
        
        for (i = 0; i < length && input[i] != ','; i++) {
                malen = malen + input[i];
        }

        for (i = i + 1; i < length; i++) {
                femalen = femalen + input[i];
        }
}

/*
 * run: given a character of the usage and string of the pathway,
 * runs the getGender program, printing the results to stdout
 * returns nothing
 */
void GetGender::run(char u, string path)
{
        ifstream infile;
        infile.open(path);
        if (infile.is_open() == false) {
                cerr << "Error opening " << path << endl;
                return;
        }        

        usage = u;
        analyzeGenders(infile);       

        infile.close();
}

/*
 * analyzeGenders: given an open ifstream, reads the file, assigning
 * gender to each name and printing the results to stdout, returns
 * nothing
 */ 
void GetGender::analyzeGenders(ifstream &infile)
{
        char input;
        int field = 0;
        string word = "";
        int line = 0;
        string gender = "GENDER";
        for (infile.get(input); infile.eof() == false; infile.get(input)) {
                if (input == ',') {
                        if (field == 1 && line > 0) {
                                gender = assignGender(word);
                        }
                        field++;
                        cout << word << ",";
                        word = "";
                        
                }
                else if (input == '\n') {
                        cout << word << "," << gender << endl;
                        field = 0;
                        word = "";
                        line++;
                }
                else {
                        word = word + input;
                }
        }
}

/*
 * assignGender: given a string name, assigns gender as according to the
 * gender/name dictionaries, returning the assigned gender as a string
 */
string GetGender::assignGender(string name)
{
        string gender = "";
        name = capWord(name);        
        if (fnames->find(name) != fnames->end())
                gender = "FEMALE";
        else if (mnames->find(name) != mnames->end())
                gender = "MALE";
        else {
                if (usage == 'i')
                        cin >> gender;
                else 
                        gender = "UNKOWN";
        }
        
        return gender;
}

string GetGender::capWord(string word)
{
        int length = word.length();

        for (int i = 0; i < length; i++) {
                if (i == 0)
                        word[i] = toupper(word[i]);       
                else
                        word[i] = tolower(word[i]);
        }
        return word;
}
