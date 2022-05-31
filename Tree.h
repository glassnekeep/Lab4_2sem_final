//
// Created by - on 29.05.2022.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include <iostream>
#include <functional>
#include <string>

using namespace std;

template<class T>
class Tree{
protected:
    class Node {
    public:
        explicit Node(T value) : value(value), height(1){}
        Node(const Node& node){
            if(&node == nullptr)
                throw std::range_error("Node cant be created from null");
            value = node.value;
            height = node.height;
            if(node.left) left = new Node(*node.left);
            if(node.right) right = new Node(*node.right);
        }
        explicit Node(Node* node){
            if(node){
                value = node->value;
                height = node->height;
                if(node->left) left = new Node(node->left);
                if(node->right) right = new Node(node->right);
            }
        }
        Node():Node(nullptr){};

        T value;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
    };
private:
    void DestroyNode(Node* node) {
        if (node) {
            if(node->left) DestroyNode(node->left);
            if(node->right) DestroyNode(node->right);
            delete node;
        }
    }

    int height(Node *N) {
        if (N == NULL) { return 0; }
        return N -> height;
    }

    int max(int a, int b) {
        return (a > b)? a : b;
    }

    Node *RightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
        // Perform rotation
        x->right = y;
        y->left = T2;
        // Update heights
        y->height = max(height(y -> left),height(y -> right)) + 1;
        x->height = max(height(x -> left),height(x -> right)) + 1;
        // Return new root
        return x;
    }
    Node *LeftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
        // Perform rotation
        y -> left = x;
        x -> right = T2;
        // Update heights
        x -> height = max(height(x -> left),height(x -> right)) + 1;
        y -> height = max(height(y -> left),height(y -> right)) + 1;
        // Return new root
        return y;
    }
    int GetBalance(Node *N) {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* FindMin(Node* node) {
        while (node -> left != nullptr) { node = node -> left; }
        return node;
    }
protected:
    Node* root;
    template<class T1>
    void Mapping(T1(*mapper)(T), Node* node, Tree<T>* tree){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        // auto temp = mapper(node->value);
        tree->Append(mapper(node->value));
        // node->value = temp;
        if (node->left) Mapping(mapper, node->left, tree);
        if (node->right) Mapping(mapper, node->right, tree);
    }

    void WherePath(bool(*predicate)(T), Node* node, Tree<T> *tree){
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        if(predicate(node->value)) tree->Append(node->value);
        if(node->left) WherePath(predicate, node->left, tree);
        if(node->right) WherePath(predicate, node->right, tree);
    }

    /*T ReducePath(T(*reducer)(T, T), T const& c, Node* node){
        if(node){
            T res = reducer(node->value, c);
            res = ReducePath(reducer, res, node->left);
            res = ReducePath(reducer, res, node->right);
            return res;
        }
        return c;
    }*/
public:
    Tree(){
        root = nullptr;
    }

    explicit Tree(T rootKey){
        root = new Node(rootKey);
    }

    Tree(std::initializer_list<T> items):Tree(){
        for(T item : items){
            Append(item);
        }
    }

    explicit Tree(const Node &root){
        this->root = new Node(root);
    }
    explicit Tree(Node *root){
        this->root = new Node(root);
    }

    Tree(const Tree &tree): Tree(){
        if(tree.root != nullptr) root = new Node(*tree.root);
    }

    explicit Tree(Tree<T>* tree): Tree(){
        if(tree != nullptr && tree->root != nullptr) root = new Node(tree->root);
    }

    ~Tree(){
        DestroyNode(root);
    }

    Node* getRoot() {
        return root;
    }

    void setRoot(Node* node) {
        root = node;
    }

    void Append(T value){
        if(&value == nullptr){
            throw std::range_error("You cant append NULL");
        }
        root = Insert(root, value);
    }

    void AppendBalanced(T value) {
        if (&value == nullptr) {
            throw std::range_error("You cannot append NULL");
        }
        root = BalancedInsert(root, value);
    }

    Node* Insert(Node* node, T value) {
        if (node == NULL)
            return(new Node(value));
        if (value < node->value)
            node->left = Insert(node->left, value);
        else if (value > node->value)
            node->right = Insert(node->right, value);
        else
            return node;
        node->height = 1 + max(height(node->left),
                               height(node->right));
        return node;
    }

    Node* BalancedInsert(Node* node, T value) {
        if (node == NULL)
            return(new Node(value));
        if (value < node->value)
            node->left = Insert(node->left, value);
        else if (value > node->value)
            node->right = Insert(node->right, value);
        else // Equal keys are not allowed in BST
            return node;
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = GetBalance(node);
        if (balance > 1 && value < node->left->value) { return RightRotate(node); }
        if (balance < -1 && value > node->right->value) { return LeftRotate(node); }
        if (balance > 1 && value > node->left->value) {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }
        if (balance < -1 && value < node->right->value) {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }
        return node;
    }

    Node* Remove(T value){
        if (&value == nullptr || !root){
            throw std::range_error("You cant remove NULL");
        }
        return Delete(&root, value);
    }
    Node* Delete(Node **node, T value) {
        if(*node == nullptr) return *node;
        else if(value < (*node)->value) (*node)->left = Delete(&(*node)->left, value);
        else if (value > (*node)->value) (*node)->right = Delete(&(*node)->right, value);
        else {
            if((*node)->left == nullptr && (*node)->right == nullptr) {
                delete *node;
                *node = nullptr;
            }
            else if((*node)->left == NULL) {
                struct Node *temp = *node;
                *node = (*node)->right;
                delete temp;
            }
            else if((*node)->right == NULL) {
                struct Node *temp = *node;
                *node = (*node)->left;
                delete temp;
            }
            else {
                Node *temp = FindMin((*node)->right);
                (*node)->value = temp->value;
                (*node)->right = Delete(&(*node)->right, temp->value);
            }
        }
        return *node;
    }

    bool Search(T value){
        if(&value == nullptr || !root) {
            throw std::range_error("You cant search NULL");
        }
        Node** current = &root;
        while (*current){
            Node& node = **current;
            if(value < node.value){
                current = &node.left;
            }
            else{
                if(value > node.value){
                    current = &node.right;
                }
                else{
                    return (*current)->value == value;
                }
            }
        }
        return false;
    }

    T* GetValue(T value){
        if (&value == nullptr || !root) {
            throw std::range_error("You cant search NULL");
        }
        Node* current = root;
        while (current){
            Node& node = *current;
            if(value < node.value){
                current = node.left;
            }
            else{
                if(value > node.value){
                    current = node.right;
                }
                else{
                    if(node.value == value)
                        return &(node.value);
                }
            }
        }
        return nullptr;
    }

    Node* SearchNode(T value){
        Node** current = &root;
        while (*current){
            Node& node = **current;
            if(value < node.value){
                current = &node.left;
            }
            else{
                if(value > node.value){
                    current = &node.right;
                }
                else{
                    return (*current);
                }
            }
        }
        return nullptr;
    }

    Tree<T> SubTree(T value){
        Node** current = &root;
        while (*current){
            Node& node = **current;
            if(value < node.value){
                current = &node.left;
            }
            else {
                if(value > node.value){
                    current = &node.right;
                }
                else{
                    return Tree(**current);
                }
            }
        }
        return Tree();
    }

    bool SearchSubTree(const Tree& tree){
        if(&tree == nullptr || tree.root == nullptr) return false;
        Node** current = &root;
        T value = tree.root->value;
        while (*current){
            Node& node = **current;
            if(value < node.value){
                current = &node.left;
            }
            else{
                if(value > node.value){
                    current = &node.right;
                }
                else{
                    bool a1 = false;
                    if((*current)->right != nullptr && tree.root->right != nullptr)
                        a1 = tree.root->right->value == (*current)->right->value;
                    else if((*current)->right == nullptr && tree.root->right == nullptr)
                        a1 = true;

                    bool a2 = false;
                    if((*current)->left != nullptr && tree.root->left != nullptr)
                        a2 = tree.root->left->value == (*current)->left->value;
                    else if((*current)->left == nullptr && tree.root->left == nullptr)
                        a2 = true;

                    bool result = value == (*current)->value && a1 && a2;

                    return result;
                }
            }
        }
        return false;
    }

    template<class T1>
    Tree<T1>* Map(T1(*mapper)(T)) {
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        auto* newTree = new Tree<T1>();
        Mapping(mapper, this->root, newTree);
        return newTree;
    }
    Tree<T>* Where(bool(*predicate)(T)) {
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        auto* newTree = new Tree<T>();
        WherePath(predicate, this->root, newTree);
        return newTree;
    }
    /*T Reduce(T(*reducer)(T, T), T const &c) {
        if (reducer == nullptr)
            throw std::invalid_argument("reducer is NULL");
        T res = ReducePath(reducer, c, root);
        return res;
    }*/
    Tree<T> &operator=(const Tree<T> &tree){
        if(&tree != this && tree.root != nullptr) {
            DestroyNode(root);
            root = new Node(tree.root);
        }
        return *this;
    }

    void PreOrder(Node *node, int ctr) {
        if(node != nullptr) {
            std::string brackets[] = {"{", "}", "(", ")", "[", "]"};
            std::cout << brackets[ctr] << node->value << " ";
            PreOrder(node->left, (ctr + 2) % 6);
            PreOrder(node->right, (ctr + 4) % 6);
            std::cout << brackets[ctr + 1];
        }
    }
    void Output(){
        PreOrder(root, 0);
        std::cout << "\n";
    }
    void printOutput() {
        print(root, 0);
        std::cout << "\n" << std::endl;
    }
    void print(Node* node, int level) {
        if (node != nullptr) {
            print(node -> left, level + 1);
            for (int i = 0; i < level; i++) std::cout << "   ";
            std::cout << node -> value <<  std::endl;
            print (node -> right, level + 1);
        }
    }

    void PKL(Node *tree) {
        if (tree != nullptr) {
            PKL (tree -> right);
            std::cout << tree -> value << "\t";
            PKL (tree -> left);
        }
    }

    void PLK(Node *tree) {
        if (tree != nullptr) {
            PLK (tree -> right);
            PLK (tree -> left);
            cout << tree -> value << "\t";
        }
    }

    void KLP(Node *tree) {
        if (tree != nullptr) {
            cout << tree -> value << "\t";
            KLP (tree -> left);
            KLP (tree -> right);
        }
    }

    void KPL(Node *tree) {
        if (tree != nullptr) {
            cout << tree -> value << "\t";
            KPL (tree -> right);
            KPL (tree -> left);
        }
    }

    void LPK(Node *tree) {
        if (tree != nullptr) {
            LPK (tree -> left);
            LPK (tree -> right);
            cout << tree -> value << "\t";
        }
    }

    void LKP(Node *tree) {
        if (tree != nullptr) {
            LKP (tree -> left);
            cout << tree->value << "\t";
            LKP (tree -> right);
        }
    }

    string* IntoString(Node* tree, string* result) {
        if (tree == nullptr) {
            return nullptr;
        }
        *result = *result + to_string(tree -> value);
        if (tree -> left != nullptr) {
            *result += "(";
            IntoString(tree -> left, result);
            *result += ")";
        } else {
            *result += "()";
        }
        if (tree -> right != nullptr) {
            *result += "(";
            IntoString(tree -> right, result);
            *result += ")";
        } else {
            *result += "()";
        }
        return result;
    }

    Node* fromString(const string& str, int* start) {
        if (str.empty() || *start >= str.size()) { return nullptr; }
        T num = 0;
        while (*start < str.size() && str[*start] != '(' && str[*start] != ')') {
            T numHere = (T) (str[*start] - '0');
            num = num * 10 + numHere;
            *start = *start + 1;
        }
        Node* newRoot = nullptr;
        if (num > 0) { newRoot = new Node(num); }
        if (*start < str.size() && str[*start] == '(') {
            *start = *start + 1;
            newRoot -> left = fromString(str, start);
        }
        if (*start < str.size() && str[*start] == ')') {
            *start = *start + 1;
            return newRoot;
        }
        if (*start < str.size() && str[*start] == '(') {
            *start = *start + 1;
            newRoot -> right = fromString(str, start);
        }
        if (*start < str.size() && str[*start] == ')') { *start = *start + 1; }
        return newRoot;
     }
};

#endif //UNTITLED1_TREE_H
