/*
 * Course: CS216-001
 * Jared Winburn Project 2 
 * Auto Complete Program
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

using namespace std;

int main(int argc, char** argv) {
    const int ARGUMENTS = 2;
    
    // check the command line argument, an input file name is needed
    if (argc != ARGUMENTS+1)
    {
        cout<< "Warning: need exatcly 2 command line arguments."<<endl;
        cout << "Usage: " << argv[0] << " <filename> "<< "number" << endl;
        return 1;
    }    
    
    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Warning: Cannot open the file named " << argv[1] << endl;
        return 2;
    }
    int k = atoi(argv[2]);
    if (k <= 0){
        cout << "Warning: the number of matching terms needs to be a positive number!"<<endl;
        return 1;
    } // validating the number of matching terms the user wants
    
    // read in the terms from the input file
    // line by line and store into Autocomplete object
    Autocomplete autocomplete;
    long weight;
    string query;
    
    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {    
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }    
    } 

    // read the time clock 
    // before calling sort() function and after it
    // to measure the time spent for sorting operation
    // clock_t tstart, tstop;
    // tstart = clock();
    autocomplete.sort();
    // tstop = clock();
    // double  elapsed = (double)(tstop-tstart)/CLOCKS_PER_SEC; 
    // cout << "Time for sorting all terms: "<<  elapsed << " seconds." << endl;
    
    string input;
    string prefix;
    cout<< "Enjoy CS216 Auto-complete Me search engine !"<<endl;
    cout<< "It is written by Jared Winburn in CS216 Section 001"<<endl;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, input);
    prefix = input;
    while (prefix != "exit")
    {

        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);
        
        if (matchedTerms.size() == 0)
        {    
            cout << "No matched query!" << endl;
        }
        else // Updated for Project 2, only sort and print the specified ammount given by the user
        {
         matchedTerms.selection_sort(Term::compareByWeight);
        
          for (int i = 0; i < min(k, matchedTerms.size());i++){
              cout <<matchedTerms[i] <<endl;
          }
        }

         cout<< "Enjoy CS216 Auto-complete Me search engine !"<<endl;
         cout<< "It is written by Jared Winburn in CS216 Section 001"<<endl;
         cout << "Please input the search query (type \"exit\" to quit): " << endl;
         getline(cin, input);
         prefix = input;
    }
    cout<< "Thank you for using Auto-complete feature provided by CS216!"<<endl;
    return 0;
}

