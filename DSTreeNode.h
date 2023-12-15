//
// Created by robot on 4/10/2021.
//

#ifndef DSAVLMAP_DSTREENODE_H
#define DSAVLMAP_DSTREENODE_H

#include <list>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

template<class K, class V, class R>
class DSTreeNode {
private:
    K key;
    vector<V> values;
    vector<R> rankings;
    DSTreeNode<K,V, R>* left = nullptr;
    DSTreeNode<K,V, R>* right = nullptr;
    int height;
public:
    DSTreeNode();
    DSTreeNode(K d,V val, R ranking, DSTreeNode<K,V, R>* l = nullptr, DSTreeNode<K,V,R>* r = nullptr);
    DSTreeNode(K d, vector<V> val, vector<R> ranking, DSTreeNode<K,V, R>* l = nullptr, DSTreeNode<K,V,R>* r = nullptr);
    DSTreeNode(const DSTreeNode & toCopy);
    ~DSTreeNode();
    //operators
    DSTreeNode<K,V,R>& operator = (const DSTreeNode<K,V,R>& val);
    //accessors
    K& getKey(){return key;}
    vector<V> getValues(){
        return values;
    }
    vector<R> getRankings(){return rankings;}
    inline int& getHeight(){return height;}
    inline DSTreeNode*& getLeft(){return left;}
    inline DSTreeNode*& getRight(){return right;}
    //mutators
    inline void setKey(const K& newKey){key = newKey;}
    void addValue(const V& val, const R& rank);
    inline void setHeight(const int& h){height = h;}
    inline void setLeft(DSTreeNode<K,V,R>* node){left = node;}
    inline void setRight(DSTreeNode<K,V,R>* node){right = node;}
};

#endif //DSAVLMAP_DSTREENODE_H
/**
 * Creates a TreeNode object default
 */
template<class K, class V, class R>
DSTreeNode<K,V,R>::DSTreeNode(){
    height = -1;
    left = nullptr;
    right = nullptr;
}//default constructor

/**
 *  Creates a TreeNode object with the given attributes
 * @param d Key
 * @param val Value
 * @param ranked Rank
 * @param l left ptr
 * @param r right ptr
 */
template<class K, class V, class R>
DSTreeNode<K,V,R>::DSTreeNode(K d,V val, R ranked, DSTreeNode<K,V,R>* l, DSTreeNode<K,V,R>* r){
    key = d;
    values.push_back(val);
    rankings.push_back(ranked);
    left = l;
    right = r;
    height = 0;
}// 3 val constructor

/**
 *  Creates a TreeNode object with the given attributes
 * @param d Key
 * @param val set of Values
 * @param ranked set of Ranks
 * @param l left ptr
 * @param r right ptr
 */
template<class K, class V, class R>
DSTreeNode<K,V,R>::DSTreeNode(K d, vector<V> val, vector<R> ranking,  DSTreeNode<K,V,R>* l, DSTreeNode<K,V,R>* r){
    key = d;
    values = val;
    rankings = ranking;
    left = l;
    right = r;
    height = 0;
}

/**
 * Creates a TreeNode object with the given object
 * @param toCopy TreeNode to copy
 */
template<class K, class V, class R>
DSTreeNode<K,V,R>::DSTreeNode(const DSTreeNode<K,V,R> & toCopy){
    key = toCopy.key;
    values= toCopy.values;
    rankings = toCopy.rankings;
    left = toCopy.left;
    right = toCopy.right;
    height = toCopy.height;
}//copy constructor

//Destructors
template<class K, class V, class R>
DSTreeNode<K,V,R>::~DSTreeNode(){
    right = nullptr;
    left = nullptr;
    /*if(right != nullptr)
        delete right;
    if(left != nullptr)
        delete left;*/
}//destructor

/**
 * Creates a TreeNode object with the given object
 * @param toCopy TreeNode to copy
 * @return made object
 */
template<class K, class V, class R>
DSTreeNode<K,V,R> &DSTreeNode<K,V,R>::operator=(const DSTreeNode<K,V,R> &val) {
    key = val.key;
    values = val.values;
    rankings = val.rankings;
    left = val.left;
    right = val.right;
    height = val.height;

    return *this;
}//operator=

/**
    Adds value and rank to the node's sets
 * @param val val to add
 * @param rank rank to add
 */
template<class K, class V, class R>
void DSTreeNode<K,V,R>::addValue(const V& val, const R& rank){
    for(int i = 0; i < values.size(); i++){
        if(values.at(i) == val) {
            rankings.at(i) += rank;//add to that words rank for this doc ID
            return;
        }
    }
    values.push_back(val);//if value not already in list, add to list
    rankings.push_back(rank);
}

