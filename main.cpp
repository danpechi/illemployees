/* Madeleine Schwartz
 * July 8th, 2018
 * main.cpp
 *
 * driver for getGender.h public methods
 * 
 */

#include "getGender.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
        cerr << "In program\n";

        GetGender program;
        string filename = "new-baby-names.csv";

        if (argc == 2) {
                program.setDictionaries(filename);               
                program.run('a', argv[1]);
        }
        else if (argc == 3) {
                program.setDictionaries(filename);
        }
        else {
                cerr << "Usage: ./getGender [filename]\n"
                     << "       ./getGender -i [filename]\n";
                return 1;
        }        

        return 0;
}
