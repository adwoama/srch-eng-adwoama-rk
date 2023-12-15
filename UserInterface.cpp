/*
 * Rebecca Kuhlman
 * 4/6/2021
 * CS 2341
 * The User Interface class that interacts with the user and contains methods to display to the user
 */

#include <fstream>
#include "UserInterface.h"

using namespace std;

/**
 * Creates a user interface object
 * @param folder given file path to get documents from
 */
UserInterface::UserInterface(string& folder){
    this->folder = folder;
}

/**
 * Prompts the user and receives input, and based on input calls the methods necessary
 */
void UserInterface::receiveQueries(){
    cout << "Hello and Welcome to the Seaside Csphalopod Search, for all your COVID-19 searching"
            << " needs~ " << endl;
    string userInput;
    bool go = true;
    Runner process;
    DSAVLTree<string, string, int> keys;
    while(go){
        cout << "Enter the following number for the corresponding command"
             << endl << "1 - Enter a Query" << endl << "2 - Parse and Populate Index" << endl <<
             "3 - Clear Index" << endl << "4 - Print Search Statistics " << endl
             << "5 - Save Index " << endl << "0 - Quit" << endl;
        cin >> userInput;
        if(keys.getRoot() == nullptr)
            keys = process.getKeyWords();
        if(userInput == "1"){
            if(keys.getRoot() == nullptr){
                setUpIndex(process, folder);
            }
            char query[50];
            string newQ;
            int yn = 2;
            while(yn == 2){
                cout << "Enter a Query: " << endl;
                cin >> newQ;
                cin.getline(query, 50);
                cout << "Was that query entered correctly? (1 for yes, 2 for no)" << endl;
                cin >> yn;
            }
            newQ += query;
            process.getInput(newQ);
        }
        else if(userInput == "2"){
            if(keys.getRoot() == nullptr){
               setUpIndex(process, folder);
            }
            else
                cout << "Index already populated" << endl;
        }
        else if(userInput == "3"){
            cout << "clearing index..." << endl;
            process.clearIndex();
            freqs.clear();
            keys.clear();
            cout << "Index cleared" << endl;
        }
        else if(userInput == "4"){
            if(keys.getRoot() == nullptr){
                setUpIndex(process, folder);
                keys = process.getKeyWords();
            }
            cout << "Total number of individual articles indexed: " << process.getNumDocuments() << endl;
            cout << "Average number of words indexed per article (after removal of stop words): " << process.getAvgWordCount() << endl;
            cout << "Total number of unique words indexed (after stop word removal): " << keys.getSize() << endl;
            cout << "Total number of unique Authors: " << process.getAuthors().getSize() << endl;
            cout << "Top 50 most frequent words (after removal of stop words): " << endl;
            getFreqWords(keys);
            int daysSince = 0;
            cout << "Days since last seg fault: " << daysSince;
            if(daysSince > 1)
                cout << " ^-^" << endl;
            else if(daysSince == 1)
                cout << " :o" << endl;
            else
                cout << " :<" << endl << endl;
        }
        else if(userInput == "5"){
            cout << "Saving Index..." << endl;
            string fileName = "index.txt";
            process.makeKeywordFile(fileName);
            cout << "Index saved as " << fileName << endl;
        }
        else if(userInput == "0")
            go = false;
    }
}

/**
 * Executes Top 50 most frequent words
 * @param keys AVL Tree to find words in
 */
void UserInterface::getFreqWords(DSAVLTree<string, string, int>& keys){
    if(freqs.empty()){
        DSTreeNode<string,string,int>* root = keys.getRoot();
        int min = -1;
        getFreqWords(freqs, root, min);
        sortFreqs(freqs);
    }
    int countDown = 50;
    for(pair<string, int> print : freqs){
        cout << countDown << ": " << print.first << endl;
        countDown--;
    }
    cout << endl;
}

/**
 * Helper method that fills out the top 50 vector
 * @param freqs vector to fill out
 * @param node place in the AVL that is currently being checked
 * @param minIndex Index of the current minimum value in the vector
 */
void UserInterface::getFreqWords(vector<pair<string, int>>& freqs, DSTreeNode<string,string,int>* node, int& minIndex){
    if(node == nullptr)
        return;
    vector<int> checks = node->getRankings();
    int sum = 0;
    for(int num : checks)
        sum += num;
    if(minIndex == -1){
        freqs.push_back(make_pair(node->getKey(), sum));
        minIndex = 0;
    }
    else{
        pair<string, int> minPair = freqs.at(minIndex);
        if(freqs.size() < 50){
            freqs.push_back(make_pair(node->getKey(), sum));
            if(minPair.second > sum)
                minIndex = freqs.size() - 1;
        }
        else if(sum > minPair.second){
            int newMin = sum;
            int newMinIndex = -1;
            for(int index = 0; index < freqs.size(); index++){
                pair<string, int> check = freqs.at(index);
                if(index == minIndex){
                    freqs.at(index) = make_pair(node->getKey(), sum);
                    if(newMinIndex == -1)
                        newMinIndex = index;
                }
                else if(check.second < newMin){
                    newMin = check.second;
                    newMinIndex = index;
                }
            }
            minIndex = newMinIndex;
        }
    }
    getFreqWords(freqs, node->getRight(), minIndex);
    getFreqWords(freqs, node->getLeft(), minIndex);
}

    /**
     * Sorts vector in ascending order (Selection Sort)
     */
    void UserInterface::sortFreqs(vector<pair<string, int>>& freqs){
        int smallest;
        for(int index = 0; index < freqs.size() - 1; index++){
            smallest = index;
            for(int i = index + 1; i < freqs.size(); i++){
                if(freqs[i].second < freqs[smallest].second)
                    smallest = i;
            }
            sortHelper(&freqs[smallest], &freqs[index]);
        }
    }

    /**
     * Helper method to sortFreqs that swaps elements
     * @param str1ptr - 1st element to be swapped
     * @param str2ptr - 2nd element to be swapped
     */
    void UserInterface::sortHelper(pair<string, int> *str1ptr, pair<string, int> *str2ptr){
        pair<string, int> temp = *str1ptr;
        *str1ptr = *str2ptr;
        *str2ptr = temp;
    }

    void UserInterface::setUpIndex(Runner& process, string& folder){
        int yn = 2;
        cout << "Use preexisting index?  (1 for yes, 2 for no)";
        cin >> yn;
        if(yn == 1){
            string filePath;
            yn = 2;
            while(yn == 2){
                cout << "Please enter file path of desired index file" << endl;
                cin >> filePath;
                cout << "Was that query entered correctly? (1 for yes, 2 for no)" << endl;
                cin >> yn;
            }
            cout << "setting up index..." << endl;
            process.parseFile(filePath);
            cout << "Index populated" << endl;
        }
        else{
            cout << "Use different file path? (1 for yes, 2 for no)" << endl;
            cin >> yn;
            if(yn == 1){
                string filePath;
                yn = 2;
                while(yn == 2){
                    cout << "Please enter file path of desired index file" << endl;
                    cin >> filePath;
                    cout << "Was that query entered correctly? (1 for yes, 2 for no)" << endl;
                    cin >> yn;
                }
                cout << "setting up index..." << endl;
                process.MakeDocList(filePath);
                cout << "Index populated" << endl;
            }
            else{
                cout << "Using command line default..." << endl;
                cout << "setting up index..." << endl;
                process.MakeDocList(folder);
                cout << "Index populated" << endl;
            }
        }
    }
