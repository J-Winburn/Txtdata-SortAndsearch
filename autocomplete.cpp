/* File: autocomplete.cpp
 * Course: CS216-00x
 * Project: Project 2
 * Purpose: the implementation of member functions for the class named Autocomplete.
 *
 */
#include <iostream>
#include "autocomplete.h"

// default constructor
Autocomplete::Autocomplete()
{
    // You can leave it blank
    // since the private data member terms has been initialized through default constructor of SortingList class 
}


// inserts the newterm to the sequence
// note that a SortingList<Term> object, named terms
//          represents the sequence
void Autocomplete::insert(Term newterm)
{
    terms.insert(newterm);
}


// sort all the terms by query in the lexicographical order  
void Autocomplete::sort()
{
    terms.std_sort(); //use sort function 
}

// binary search helper function
// as private function
// since it serves binary_search member function only
int Autocomplete::binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index)
{
    if(right_index < left_index)
    {
        int KEY_NOT_FOUND = -1;
        return KEY_NOT_FOUND;
    }
    else
    {
        Term keyterm(key, 0);
        int r = key.length();
        int middle = (left_index + right_index) / 2;
        if(Term::compareByPrefix(keyterm,terms[middle],r) > 0)
        {
            return binary_searchHelper(terms, key, left_index, middle - 1);

        }
        else if(Term::compareByPrefix(keyterm,terms[middle],r)  < 0)
        {
            return binary_searchHelper(terms, key, middle + 1, right_index);
        }
        else
        {
            return middle;
        }
    }
}

// return the index number of the term whose query 
// prefix-matches the given prefix, using binary search algorithm
// Note that binary search can only be applied to sorted sequence
// Note that you may want a binary search helper function
int Autocomplete::binary_search(string prefix)
{
    if (terms.size() ==0){
        return -1;} // if the list is empty we return -1

    return(binary_searchHelper(terms, prefix, 0, terms.size()-1));  // call to the helper function 
}

// first: the index of the first query whose prefix matches
//          the search key, or -1 if no such key
// last: the index of the last query whose prefix matches 
//         the search key, or -1 if no such key
// key: the given prefix to match
// hints: you can call binary_search() first to find one matched index number,
//        say hit, then look up and down from hit, to find first and last respectively
void Autocomplete::search(string key, int& firstIndex, int& lastIndex)
{
    int match = binary_search(key);
    if (match == -1){ // no mathes found 
    firstIndex = -1;
    lastIndex = -1;
    return;
    }
    
    firstIndex = match;
    while(firstIndex > 0 && Term::compareByPrefix(Term(key,0), terms[firstIndex -1],key.length()) == 0){
        firstIndex--;} // comapre all previous indexes for a match by calling the compare by prefix function, if the result is 0 then its a match

    lastIndex = match;
    while(lastIndex < terms.size()-1 &&Term::compareByPrefix(terms[lastIndex +1],Term(key,0), key.length()) == 0){
    lastIndex++;} //same as firstIndex but we move forward instead of backwards until we dont match or we hit end of the list

}

// returns all terms that start with the given prefix, in descending order of weight
SortingList<Term> Autocomplete::allMatches(string prefix)
{
    SortingList<Term> matchedTerms;
    int firstIndex, lastIndex;

    search(prefix, firstIndex, lastIndex);

    if(firstIndex == -1 && lastIndex == -1){
        return matchedTerms; // no match found
    }
    for (int i = firstIndex; i <= lastIndex; i++){
        matchedTerms.insert(terms[i]);
    }
    matchedTerms.selection_sort(Term::compareByWeight);
    return matchedTerms;
}
void Autocomplete::print()
{
    for(int i = 0; i < terms.size(); i++){
        cout << terms[i] << endl;}
    cout << endl;
}

