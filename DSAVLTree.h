//
// Created by Maggie Asare on 4/10/2021.
//

#ifndef DSAVLMAP_DSAVLTREE_H
#define DSAVLMAP_DSAVLTREE_H

#include "DSTreeNode.h"

using namespace std;

template<class K, class V, class R>
class DSAVLTree {
private:
    DSTreeNode<K,V,R> *root = nullptr;
    int size;
public:
    DSAVLTree(): root(nullptr), size(0){}
    DSAVLTree(const DSAVLTree<K,V,R>& rhs){*this = rhs; size = 0;}
    DSAVLTree<K, V, R>& operator= (DSAVLTree<K, V, R>&);
    ~DSAVLTree();
    //accessors
    DSTreeNode<K,V,R>* find(K key);
    inline DSTreeNode<K,V,R>* getRoot(){return root;}
    inline bool contains(K val){return contains(root, val);}
    bool contains(DSTreeNode<K,V,R>* c, K val);
    DSTreeNode<K,V,R>* find(DSTreeNode<K,V,R>* c, K val);
    int height(DSTreeNode<K,V,R>*&);
    int getSize();

    //mutators
    inline void insert(const K& key, const V& val, const R& rank){insert(key, val, rank, root); size++;}
    void insert(const K& key, const V& val, const R& rank, DSTreeNode<K,V, R>*& t);
    void insert(const K&, const vector<V>&, const vector<R>&, DSTreeNode<K,V, R>*&);
    void balance(DSTreeNode<K,V,R>*& t);
    void rotateWithLeftChild(DSTreeNode<K,V,R>*& k2);
    void doubleWithLeftChild(DSTreeNode<K,V,R>*& k3);
    void rotateWithRightChild(DSTreeNode<K,V,R>*& k2);
    void doubleWithRightChild(DSTreeNode<K,V,R>*& k3);
    inline void clear(){clear(root); size = 0; root = nullptr;}
    void clear(DSTreeNode<K,V,R>* n);
    void copyHelper(DSTreeNode<K, V, R>*&);

};

#endif //DSAVLMAP_DSAVLTREE_H

//Destuctor
template<class K, class V, class R>
DSAVLTree<K, V, R>::~DSAVLTree() {
    //empty tree using post order traversal
    clear(root);
}//destructor

/**
 * Creates a new object with the given object
 * @param newTree object to make this object out of
 * @return made object
 */
template<class K, class V, class R>
DSAVLTree<K, V, R>& DSAVLTree<K, V, R>::operator= (DSAVLTree<K, V, R>& newTree){
    clear();
    if(newTree.root != nullptr){
        copyHelper(newTree.root);
        size = newTree.size;
    }
    return *this;
}

/**
 * Recursively copies for oper = function via inserting
 * @param node current node being copied
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::copyHelper(DSTreeNode<K, V, R>*& node){
    if(node != nullptr){
        insert(node->getKey(), node->getValues(), node->getRankings(), root);
        copyHelper(node->getLeft());
        copyHelper(node->getRight());
    }
}

/**
 * Inserts a new node using given information, tranversing tree via t
 * @param key for new object
 * @param vals for new object
 * @param ranks for new object
 * @param t current node that are checking
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::insert(const K& key, const vector<V>& vals, const vector<R>& ranks, DSTreeNode<K,V, R>*& t) {
    if(t==nullptr) {
        t = new DSTreeNode<K, V, R>(key, vals, ranks);
        if(root == nullptr)
            root = t;
        else
            balance(t);
    }
    else if(t->getKey() < key) {
        insert(key, vals, ranks, t->getRight());
        balance(t);
    }
    else if(key < t->getKey()) {
        insert(key, vals, ranks, t->getLeft());
        balance(t);
    }
}

/**
 * Inserts a new node using given information, tranversing tree via t
 * @param key for new object
 * @param vals for new object
 * @param ranks for new object
 * @param t current node that are checking
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::insert(const K& key, const V& val, const R& rank, DSTreeNode<K,V, R>*& t) {
    if(t==nullptr) {
        t = new DSTreeNode<K, V, R>(key, val, rank, nullptr, nullptr);
        if(root == nullptr)
            root = t;
        else
            balance(t);
    }
    else if(t->getKey() < key) {
        insert(key, val, rank, t->getRight());
        balance(t);
    }
    else if(key < t->getKey()) {
        insert(key, val, rank, t->getLeft());
        balance(t);
    }
    else //if(key == t->getKey())//
        t->addValue(val,rank);//add this doc id and add to its rank for this word

}//insert

/**
 * Balances AVL tree by checking cases and calling rotations as needed
 * @param t current node in tree
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::balance(DSTreeNode<K, V, R>*& t) {
        if(height(t->getLeft()) - height(t->getRight()) > 1) {//Case 1 or 2
            if (height(t->getLeft()->getLeft()) >= height(t->getLeft()->getRight()))//Case 1
                rotateWithLeftChild(t);
            else//Case 2
                doubleWithLeftChild(t);
        }
        else if (height(t->getRight()) - height(t->getLeft()) > 1) {//Case 3 or 4
            if (height(t->getRight()->getLeft()) >= height(t->getRight()->getRight()))
                doubleWithRightChild(t);//Case 3?
            else//Case 4?
                rotateWithRightChild(t);
        }
        t->setHeight(max(height(t->getLeft()), height(t->getRight())) + 1);
}//balance(DSTreeNode<K, V> *&t)

/**
 * rotates the left child
 * @param k2 node to rotate with
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::rotateWithLeftChild(DSTreeNode<K, V, R>*& k2) {
    DSTreeNode<K,V, R>* k1 = k2->getLeft();
    k2->setLeft((k1->getRight()));
    k1->setRight(k2);
    k2->setHeight(max(height(k2->getLeft()), height(k2->getRight())) + 1);
    k1->setHeight(max(height(k1->getLeft()), k2->getHeight()) + 1);
    k2 = k1;
}//rotateWithLeftChild

/**
 * rotates the right then the left child to balance
 * @param k3 node to rotate with
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::doubleWithLeftChild(DSTreeNode<K, V, R>*& k3) {
//TODO check with panopto
    rotateWithRightChild(k3->getLeft());
    rotateWithLeftChild(k3);
}//doubleWithLeftChild

/**
 * rotates the right child
 * @param k2 node to rotate with
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::rotateWithRightChild(DSTreeNode<K, V, R>*& k2) {
    DSTreeNode<K,V, R>* k1 = k2->getRight();
    k2->setRight((k1->getLeft()));
    k1->setLeft(k2);
    k2->setHeight(max(height(k2->getRight()), height(k2->getLeft())) + 1);
    k1->setHeight(max(height(k1->getRight()), k2->getHeight()) + 1);
    k2 = k1;
}//rotateWithRightChild

/**
 * rotates the left then the right child to balance
 * @param k3 node to rotate with
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::doubleWithRightChild(DSTreeNode<K, V, R>*& k3) {
    rotateWithLeftChild(k3->getRight());
    rotateWithRightChild(k3);
}//doubleWithRightChild

/**
 * Checks to see if given value is in the list
 * @param c iter node
 * @param val key to check
 * @return true/false if key was contained
 */
template<class K, class V, class R>
bool DSAVLTree<K, V, R>::contains(DSTreeNode<K, V, R> *c, K val) {
    if(c == nullptr)
        return false;
    else if(c->getKey() == val)
        return true;
    else if(val < c->getKey())
        return contains(c->getLeft(), val);
    else //if(c->getKey() < val)
        return contains(c->getRight(), val);
}//contains

/**
 * Finds given value in the list
 * @param val key to check
 * @return value of given key
 */
template<class K, class V, class R>
DSTreeNode<K, V, R>* DSAVLTree<K, V, R>::find(K key) {
    return find(root,key);
}

/**
 * Finds given value in the list
 * @param c iter node
 * @param val key to check
 * @return value of given key
 */
//find
template<class K, class V, class R>
DSTreeNode<K,V, R>* DSAVLTree<K, V, R>::find(DSTreeNode<K, V, R> *c, K val) {
    if(c == nullptr)
        return nullptr;
    else if(c->getKey() == val)
        return c;
    else if(val < c->getKey())
        return find(c->getLeft(), val);
    else //if(c->getKey() < val)
        return find(c->getRight(), val);
}

/**
 * Finds given value in the list
 * @param c iter node
 * @param val key to check
 * @return value of given key
 */
template<class K, class V, class R>
void DSAVLTree<K, V, R>::clear(DSTreeNode<K,V,R>* n) {
    if(n != nullptr){
        clear(n->getLeft());
        clear(n->getRight());
        delete n;
    }
}

//TODO: review height function
template<class K, class V, class R>
int DSAVLTree<K, V, R>::height(DSTreeNode<K, V, R>*& node){
    if(node == nullptr)
        return -1;
    return node->getHeight();
}

//destructor
template<class K, class V, class R>
int DSAVLTree<K, V, R>::getSize(){
    return size;
}


