//
// Created by Maggie Asare on 4/13/2021.

//
#include "include/rapidjson/document.h"
#include <dirent.h>
#include <string>
#include <iostream>
#include <sstream>
#include <locale.h>
#include <fstream>
#include "Runner.h"
#include <set>
#include <list>
#include <algorithm>
#include <vector>
#include "porter2_stemmer.h"
#include <stdexcept>

using namespace std;
using namespace rapidjson;

#define DEBUG false
#define DEBUG2 false

/**
 * Creates a running object by intializing needed varibles and
 * reading in stopWords.txt
 */
Runner::Runner(){
    fstream inputStop;
    string stopFile = "stopWords.txt";
    inputStop.open(stopFile);
    if(!inputStop.is_open())
        throw invalid_argument("File not found for stop words!");
    int index = 0;
    string newStop;
    while (!inputStop.eof()){ //&& (newStop != " " && newStop != "")){
        inputStop >> newStop;
        stopWords[index] = newStop;
        index++;
    }
   /* sort(stopWords, stopWords + 641);
    ofstream output;
    output.open("newStops.txt");
    for(int i = 0; i < 641; i++){
        output << stopWords[i] << endl;
    }*/
    numDocuments = 0;
    avgWordCount = 0;
}

/**
 * Creates keywords and authors by reading in the documents
 * @param folder path to documents to read in
 */
void Runner::MakeDocList(string & folder){
    filePath = folder;
    int numWords = 0;

    if(DEBUG2) cout << "Building Directory from: " << folder.c_str() << endl;
    //METHOD 1
    struct dirent *entry;
    DIR *dir = opendir(folder.c_str());
    if (dir == NULL) {
        if(DEBUG2)  cout << "NULL directory" << endl;
        return;
    }
    while ((entry = readdir(dir)) != NULL) {//loops through each directory
        if(DEBUG2)   cout << " Entry: " ;
        string file = entry->d_name;//file name put into string
        int length = file.length();
        if(DEBUG2)   cout << file << " ";
        if(DEBUG2)    cout << entry->d_name << endl;
        if(length>6){

            if(DEBUG2)  cout << file.substr((length-4));
            string type = file.substr((length-4));//last 4 digits of file name(ex "json")
            if(type.compare("json") == 0){
                if(DEBUG2)  cout << " is a json";
                // READ data from json file
                numDocuments++;//increase count of documents for TF IDF score
                rapidjson::Document doc;
                ifstream  streamy((folder+"/"+file).c_str());
                //put the whole file's data into a string:
                string wholeFile;
                string temp;
                while(getline(streamy,temp)){wholeFile+=temp;}
                streamy.close();

                doc.Parse(wholeFile.c_str());
               // if(doc.IsObject()) cout << "Is an object!" << endl << endl;//check that parsing worked

                doc["paper_id"].IsObject();
                string paper_id = doc["paper_id"].GetString();//read paper_id
                if(DEBUG2)   cout << "Paper id: " << paper_id << endl;
             //Read Authors
                doc["metadata"]["authors"].IsObject();
                doc["metadata"]["authors"].IsArray();
                for(auto &v : doc["metadata"]["authors"].GetArray()){
                    temp = v["last"].GetString();//hold authors last name in temp
                    authors.insert(temp, paper_id);//TODO HASH TABLE fix insert authors into
                    if(DEBUG) cout << authors.contains(temp) << endl;
                }
             //Read Abstract
                doc["abstract"].IsObject();
                doc["abstract"].IsArray();
                for(auto &v : doc["abstract"].GetArray()){
                    if(DEBUG) cout << v["text"].GetString() << endl;
                    istringstream inSS(v["text"].GetString());
                    inSS >> temp;
                    if(removeStops(temp)){
                        numWords++;
                        stemming(temp);
                        if(DEBUG2)cout << temp << endl;
                        keywords.insert(temp, paper_id, 10);
                    }
                    while(!inSS.eof()) {//parses file word by word via string stream
                        inSS >> temp;
                        if(removeStops(temp)){
                            numWords++;
                            stemming(temp);
                            if(DEBUG2)cout << temp << endl;
                            keywords.insert(temp, paper_id, 10);
                        }
                    }
                }//for every sentence of abstract
             //Read Body Text
                doc["body_text"].IsObject();
              //  if(doc["body_text"].IsArray()) cout << "body is an array" << endl << endl;

                for(auto &v : doc["body_text"].GetArray()) {
                    if(DEBUG2) cout << v["text"].GetString() << endl;//print json body text
                    istringstream inSS(v["text"].GetString());
                    inSS >> temp;
                    if(removeStops(temp)){
                        numWords++;
                        stemming(temp);
                        if(DEBUG2)cout << temp << endl;
                        keywords.insert(temp, paper_id, 1);
                    }
                    while(!inSS.eof()) {//parses file word by word via string stream
                        inSS >> temp;
                        if(removeStops(temp)){
                            numWords++;
                            stemming(temp);
                            if(DEBUG2)cout << temp << endl;
                            keywords.insert(temp, paper_id, 1);
                        }
                    }
                }

            }//if file is type .json
        }//if file name is long enough
    }
    closedir(dir);
    avgWordCount = numWords*(1.0)/numDocuments;
}

/**
 * Search made for the speed check
 * @param word Word to find
 */
vector<string> Runner::Search(string & word){
    DSTreeNode<string,string, int>* node = keywords.find(word);
    if(node == nullptr)
        throw std::out_of_range("Enter valid word");
    return node->getValues();
}

/**
 * Output made for the speed check
 * @param word Word found
 * @param docIds Doc IDs that word appeared in
 */
void Runner::Output(string& word, vector<string>& docIds){
    cout << word << endl;
    for(auto& item : docIds){
        cout << item << endl;
    }
}

/**
 * Given a query, gets the information from keywords and authors to call output with
 * @param str Query that was read in
 */
void Runner::getInput(string& str) {
    vector<string> andWords;
    vector<string> orWords;
    string notWord;
    string author;
    bool ifAnd = false;
    int find = 0;
    int length = str.length();
    string check;
    for (int index = 0; index < length; index++) {
        find = str.find(' ', index);
        if (find == -1) {
            find = length;
        }
        check = str.substr(index, find - index);
        if (check == "AND") {
            ifAnd = true;
        } else if (check == "OR") {
            ifAnd = false;
        } else if (check == "NOT") {
            int find2 = str.find(' ', find + 1);
            if (find2 == -1) {
                find2 = length;
            }
            notWord = str.substr(find + 1, find2 - find - 1);
            stemming(notWord);
        } else if (check == "AUTHOR") {
            int find2 = str.find(' ', find + 1);
            if (find2 == -1) {
                find2 = length;
            }
            author = str.substr(find + 1, find2 - find - 1);
            break;
        } else if (ifAnd) {
            if (removeStops(check)) {
                stemming(check);
                andWords.push_back(check);
            }
        } else {
            if (removeStops(check)) {
                stemming(check);
                orWords.push_back(check);
            }
        }
        index = find;
    }


    //TODO: Search AVL tree and Hash Table
    vector<string> printIds;//final list of IDs to send to output
    set<string> searchFrom;
    if (author.length() > 0) {
        if (authors.contains(author))
            searchFrom = authors.get(author);
        else
            cout << "Author doesn't exist" << endl;

    }

    if (ifAnd && !andWords.empty()) {// IF AND OPERATOR
        vector<string> andIDs;
        if (!keywords.contains(andWords.at(0))) {
            cout << "Invalid input" << endl;
            return;
        }
        andIDs = keywords.find(andWords.at(0))->getValues();
        for (int i = 1; i < andWords.size(); i++) {
            vector<string> temp;
            if (!keywords.contains(andWords.at(i))) {
                cout << "Invalid input" << endl;
                return;
            }
            vector<string> compare = keywords.find(andWords.at(i))->getValues();
            for (string ids : andIDs) {
                bool contains = false;
                for (string compIds : compare) {
                    if (compIds == ids) {
                        if (searchFrom.empty()) {
                            contains = true;//check if id appears in both lists
                        } else {
                            if (searchFrom.count(ids) == 1)
                                contains = true;
                        }
                    }
                }
                if (contains) {
                    temp.push_back(ids);
                };//only keep ids that appear in all lists
            }//for each string in andIDs, check if it is in the next list, if not remove it
            andIDs = temp;
        }//for every list of ids that correspond to an AND word

        //once all AND ids are found, add them to printIds
        printIds = andIDs;

        /*
         * relevancy score = (# of times that word appears in that document)*
         * log((#of documents total)/(# of documents that contain that word))
         *
         * # of times the word appears in that document: is the ranking number from the vector in the AVL Node
         * # of documents total is member value: numDocuments
         * # of documents that contain that word: is length of value list in node
         */
        list<pair<int, string>> scoreForId;//organize scores based on ids
        for (int i = 0; i < printIds.size(); i++) {
            int currentScore = 0;
            for (string word : andWords) {
                vector<string> temp = keywords.find(word)->getValues();
                for (int j = 0; j < temp.size(); j++) {
                    if (temp.at(j) == printIds.at(i))//add TF IDF
                        currentScore += (keywords.find(word)->getRankings().at(j)) * log(numDocuments / temp.size());
                }//check ids for that word to see if the score needs to be added to
            }//check ids for all words
            pair<int, string> addPair = make_pair(currentScore, printIds.at(i));
            scoreForId.push_back(addPair);
        }
        scoreForId.sort();
        printIds.clear();
        for (auto &item :scoreForId) {
            printIds.push_back(get<1>(item));//push strings from pairs back into idlist in order
        }
    }//add only ids that appear in all AND words lists
    else {//IF OR OPERATOR
        for (int i = 0; i < orWords.size(); i++) {
            if (!keywords.contains(orWords.at(i))) {
                cout << "Invalid input" << endl;
                return;
            }
            vector<string> compare = keywords.find(orWords.at(i))->getValues();
            for (string compIds : compare) {
                bool contains = false;
                for (string ids : printIds) {//check if printIDs has this document _ id already
                    if (ids == compIds)
                        contains = true;
                }
                if (!contains) {
                    if (searchFrom.empty()) {
                        printIds.push_back(compIds);//check if id appears in both lists
                    } else {
                        if (searchFrom.count(compIds) == 1)
                            printIds.push_back(compIds);
                    }
                }
            }
        }

        list<pair<int, string>> scoreForId;//organize scores based on ids
        for (int i = 0; i < printIds.size(); i++) {
            int currentScore = 0;
            for (string word : orWords) {
                vector<string> temp = keywords.find(word)->getValues();
                for (int j = 0; j < temp.size(); j++) {
                    if (temp.at(j) == printIds.at(i))//add TF IDF
                        currentScore += (keywords.find(word)->getRankings().at(j)) * log(numDocuments / temp.size());
                }//check ids for that word to see if the score needs to be added to
            }//check ids for all words
            pair<int, string> addPair = make_pair(currentScore, printIds.at(i));
            scoreForId.push_back(addPair);
        }
        scoreForId.sort();
        printIds.clear();
        for (auto &item :scoreForId) {
            printIds.push_back(get<1>(item));//push strings from pairs back into idlist in order
        }
    }//add all ids that appear in OR words lists
    if (notWord.length() > 0) {
        if (!keywords.contains(notWord)) { //DEBUG &&
            cout << notWord << " not in list" << endl;
            return;
        }
        vector<string> notIDs = keywords.find(notWord)->getValues();
        //form a list of notIDS
    // for each list of ids corresponding to not words, iterate through them and add to temp list
    //once list of notIDs formed, remove any ids from printIDs that appear in notIds
        vector<string> temp;
        for (string id : printIds) {
            bool contains = false;
            for (string compID : notIDs) {
                if (id == compID)
                    contains = true;
            }
            if (!contains)//only keep printIds that are not in the NOT ids list
                temp.push_back(id);
        }
        printIds = temp;
    }//remove ids that appear in NOT words lists
    if(printIds.size() < 1){
        cout << "No results found" << endl;
        return;
    }


    // andWords and orWords are searched for in doc list

    //set<string> printIds = keywords.find(*it->c_str());

    output(printIds);


}

/**
 * Checks to see if given word is a stop word
 * @param word Word to check if it is a stop word
 * @return true if word wasn't a stop word, false if it was
 */
bool Runner::removeStops(string& word){
    if(word.length() < 2)
        return false;
    string lowered = ((char) tolower(word[0])) + (word.substr(1, word.length() - 1));
    if(binarySearch(lowered, 636) != -1)
        return false;
    return true;
}

/**
 * Does a binary search of the stopWords.txt file
 * @param find String to find
 * @param length Length of stopwords
 * @return index of stop word, -1 if not found
 */
int Runner::binarySearch(string& find, int length)
{
    int lower = 0;
    int upper = length - 1;
    while (lower <= upper) {
        int mid = lower + (upper - lower) / 2;
        if (find == (stopWords[mid]))
            return mid;
        if (find > (stopWords[mid]))
            lower = mid + 1;
        else
            upper = mid - 1;
    }
    return -1;
}

/**
 * Calls Port2Stemmer for stemming
 * @param str word to stem
 */
void Runner::stemming(string& str){
    punctCheck(str);
    Porter2Stemmer::stem(str);
    transform(str.begin(), str.end(), str.begin(), ::tolower);

}

/**
 *
 * @param docIds
 */
void Runner::output(vector<string>& docIds){
   //prints title and author for first 15 documents query output
    for( int i = 0; i < docIds.size() && i < 15; i ++){
        string file = docIds.at(i);
        cout << endl << file << endl;
        rapidjson::Document doc;
        ifstream  streamy((filePath+"/"+file+".json").c_str());
        //put the whole file's data into a string:
        string wholeFile;
        string temp;
        while(getline(streamy,temp)){wholeFile+=temp;}
        streamy.close();
        doc.Parse(wholeFile.c_str());
        //PRINT TITLE
        cout << endl << "[" << i << "] ";//rank
        cout << doc["metadata"]["title"].GetString() << endl;
        //PRINT AUTHORS
        int count = 0;
        for(auto &v : doc["metadata"]["authors"].GetArray()){
            if(count < 3)
            cout<< v["first"].GetString() << " " << v["last"].GetString() <<  v["suffix"].GetString() << ", ";

           count++;
        }//print first 3 authors
        cout << endl;
    }//for first 15 files
    int menu = 0;
    do{
        cout << endl << "Enter the number for the document you want to open, or a negative number to quit..." << endl;
        cin >> menu;
        while(!cin.good()){
            cout << "Pls follow instructions and enter a NUMBER"<< endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> menu;
        }
        if(menu >= 0 && menu < docIds.size()){
            string file = docIds.at(menu);
            cout << file << endl;
            rapidjson::Document doc;
            ifstream  streamy((filePath+"/"+file+".json").c_str());
            //put the whole file's data into a string:
            string wholeFile;
            string temp;
            while(getline(streamy,temp)){wholeFile+=temp;}
            streamy.close();
            doc.Parse(wholeFile.c_str());
            int wordsPrinted = 0;
            for(auto &v : doc["body_text"].GetArray()) {
                cout << v["text"].GetString() << endl;//print json body text
                istringstream inSS(v["text"].GetString());
                inSS >> temp;
                wordsPrinted++;
                while(!inSS.eof()) {//parses file word by word via string stream
                    inSS >> temp;
                    wordsPrinted++;
                }
                if(wordsPrinted > 300)
                    break;//stop printing if past 300 words
            }//for each line of body_text
        }//if valid document option, parse document
        else if(menu < docIds.size()){
            cout << "That document ID is too large :( please follow instructions ..." << endl;
        }//if user input is larger than document list
    }while(menu >= 0);
    /*
    auto iter = docIds.begin();
    while(iter != docIds.end()){
        cout << (*iter) << endl;
        iter++;
    }
    */
}//output

//Returns keywords
DSAVLTree<string, string, int>& Runner::getKeyWords(){
    return keywords;
}

//Returns authors
DSHashTable<string,string>& Runner::getAuthors(){
    return authors;
}

/**
 * Clears keywords and authors of elements
 */
void Runner::clearIndex(){
    keywords.clear();
    authors.clear();
}

void Runner::punctCheck(string& str){
    char first = str[0];
    char last;
    int length = str.length();
    bool firstChanged = false;
    if(length > 1)
        last = str[length - 1];
    for(int index = 0; index < 6; index++){
        char check = punction[index];
        if(!firstChanged && check == first){
            if(length == 1){
                str = "";
                break;
            }
            str = str.substr(1, length - 1);
            firstChanged = true;
        }
        else if(length > 1 && check == last){
            if(firstChanged && str.length() == 1){
                str = "";
            }
            str = str.substr(0, str.length() - 1);
        }
    }
}


void Runner::makeKeywordFile(string& fileName){
    ofstream output;
    output.open(fileName);
    output << filePath << endl;
    output << numDocuments << endl;
    output << avgWordCount << endl;
    output << keywords.getSize() << endl;
    makeKeywordFile(output, keywords.getRoot());
    cout << "Finished with word Index... starting author index..." << endl;
    makeAuthorFile(output);
    output.close();
}

void Runner::makeKeywordFile(ofstream& output, DSTreeNode<string,string,int>* node){
    if(node != nullptr){
        vector<string> values = node->getValues();
        vector<int> ranking = node->getRankings();
        output << node->getKey() << endl << values.size() << endl;
        for(int index = 0; index < values.size(); index++){
            output << values.at(index) << endl << ranking.at(index) << endl;
        }
        makeKeywordFile(output, node->getRight());
        makeKeywordFile(output, node->getLeft());
    }
}

void Runner::makeAuthorFile(ofstream& output){
    set<string> keys = authors.getKeys();
    output << keys.size() << endl;
    for(string check : keys){
        output << check << endl;
        set<string> values = authors.get(check);
        output << values.size() << endl;
        for(string val : values){
            output << val << endl;
        }
    }
}

void Runner::parseFile(string& fileName){
    fstream input;
    input.open(fileName);
    input >> filePath;
    input >> numDocuments;
    input >> avgWordCount;
    int treeSize;
    input >> treeSize;
    string key;
    int valSize;
    string value;
    int rank;
    for(int index = 0; index < treeSize; index++){
        input >> key;
        input >> valSize;
        for(int i = 0; i < valSize; i++){
            input >> value;
            input >> rank;
            keywords.insert(key, value, rank);
        }
    }
    cout << "done with word index... working on authors..." << endl;
    int authorSize;
    input >> authorSize;
    for(int index = 0; index < authorSize; index++){
        input >> key;
        input >> valSize;
        for(int i = 0; i < valSize; i++){
            input >> value;
            authors.insert(key, value);
        }
    }
    input.close();
}