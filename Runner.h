//
// Created by robot on 4/13/2021.
//

#ifndef SEARCH_ENGINE_RUNNER_H
#define SEARCH_ENGINE_RUNNER_H

#include "DSAVLTree.h"
#include "DSHashTable.h"

#include <string>
#include <set>
#include <vector>

class Runner {
private:
    DSAVLTree<string, string, int> keywords;
    DSHashTable<string,string> authors;
    string stopWords[641];
    char punction[6] = {'.', ',', '(', ')', '!', '?'};
    string filePath;
    int numDocuments;
    double avgWordCount;
public:
    Runner();
    void MakeDocList(string & folder);
    vector<string> Search(string& word);
    void Output(string& word, vector<string>& docIds);
    void output(vector<string>& docIds);
    void getInput(string&);
    bool removeStops(string&);
    void stemming(string&);
    int binarySearch(string&, int);
    DSAVLTree<string, string, int>& getKeyWords();
    DSHashTable<string,string>& getAuthors();
    inline double getAvgWordCount(){return avgWordCount;}
    inline int getNumDocuments(){return numDocuments;}
    void clearIndex();
    void punctCheck(string&);
    void makeKeywordFile(ofstream& output, DSTreeNode<string,string,int>* node);
    void makeKeywordFile(string& fileName);
    void makeAuthorFile(ofstream& output);
    void parseKeywordFile(string& fileName);
    void parseFile(string& fileName);
};


#endif //SEARCH_ENGINE_RUNNER_H
