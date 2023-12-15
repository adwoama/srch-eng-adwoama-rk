/*
 * Rebecca Kuhlman
 * 4/6/2021
 * CS 2341
 * The User Interface class that interacts with the user and contains methods to display to the user
 */

#ifndef SEARCH_ENGINE_USERINTERFACE_H
#define SEARCH_ENGINE_USERINTERFACE_H
#include <string>
#include "Runner.h"
#include <iostream>

class UserInterface {
private:
    string folder;
    vector<pair<string, int>> freqs;
public:
    UserInterface(string&);
    void receiveQueries();
    void getFreqWords(DSAVLTree<string, string, int>&);
    void getFreqWords(vector<pair<string, int>>&, DSTreeNode<string,string,int>*, int&);
    void sortFreqs(vector<pair<string, int>>&);
    void sortHelper(pair<string, int>*, pair<string, int>*);
    void setUpIndex(Runner& process, string& folder);
};


#endif //SEARCH_ENGINE_USERINTERFACE_H
