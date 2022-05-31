//
// Created by - on 31.05.2022.
//
#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

int reducer(int a, int b) {
    return a + b * 2;
}

int multiply(int a) {
    return a * 2;
}

bool isEven(int a) {
    return (a % 2 == 0);
}

void menu() {
    int type;
    cout << "Choose data type: 1-Int, 2-Double: " << endl;
    cin >> type;
    if (type == 1) {
        auto* tree = new Tree<int>();
        int input = 20;
        do {
            cout << "Choose the operation:" << endl;
            cout << "1) Insert element;\n"
                    "2) Delete element;\n"
                    "3) Search an element;\n"
                    "4) Path the binary search tree;\n"
                    "5) Print the tree;\n"
                    "6) Check the element;\n"
                    "7) Check the sub tree;\n"
                    "8) Balance the tree;\n"
                    "9) Map (multiply by two function);\n"
                    "10) Where (% 2 == 0 function);\n"
                    "11) Reduce (+ element * 3 function);\n"
                    "12) Print the tree to string;\n"
                    "13) Read the tree from string;\n"
                    "14) Balanced insert;\n"
                    "0) Exit the menu;\n" << endl;
            cin >> input;
            switch (input) {
                case 1: {
                    int s;
                    int n;
                    cout << "Number of elements in the tree: " << endl;
                    cin >> n;
                    for (int i = 0; i < n; ++i) {
                        cout << "Enter value" << endl;
                        cin >> s;
                        tree -> Append(s);
                    }
                    break;
                }
                case 2: {
                    cout << "Enter element" << endl;
                    int p;
                    cin >> p;
                    tree->Remove(p);
                    cout << endl;
                    break;
                }
                case 3: {
                    cout << "Enter element" << endl;
                    int q;
                    cin >> q;
                    bool found = tree -> Search(q);
                    if (found) {
                        cout << "Element found" << endl;
                    } else {
                        cout << "Element not found" << endl;
                    }
                    break;
                }
                case 4: {
                    int path = 0;
                    cout << "Choose the passing algorithm: 1-PKL 2-PLK 3-LPK 4-LKP 5-KLP 6-KPL" << endl;
                    cin >> path;
                    switch (path) {
                        case 1:
                            cout << "Passing PKL:" << endl;
                            tree -> PKL(tree -> getRoot());
                            break;
                        case 2:
                            cout << "Passing PLK:" << endl;
                            tree -> PLK(tree -> getRoot());
                            break;
                        case 3:
                            cout << "Passing LPK:" << endl;
                            tree -> LPK(tree -> getRoot());
                            break;
                        case 4:
                            cout << "Passing LKP:" << endl;
                            tree -> LKP(tree -> getRoot());
                            break;
                        case 5:
                            cout << "Passing LKP:" << endl;
                            tree -> KLP(tree -> getRoot());
                            break;
                        case 6:
                            cout << "Passing KPL:" << endl;
                            tree-> KPL(tree -> getRoot());
                            break;
                        default:
                            break;
                    }
                    cout << endl;
                    break;
                }
                case 5: {
                    cout << "Binary tree: " << endl;
                    tree -> printOutput();
                    //tree -> Output();
                    break;
                }
                case 6: {
                    int searchElement;
                    cout << "Enter element" << endl;
                    cin >> searchElement;
                    bool answer = tree -> Search(searchElement);
                    if (answer) { cout << "Element found" << endl; } else { cout << "No such element" << endl; }
                    break;
                }
                case 7: {
                    auto* subTree = new Tree<int>();
                    int number;
                    int newValue;
                    cout << "Number of element in subtree: " << endl;
                    cin >> number;
                    for (int i = 0; i < number; i++) {
                        cout << "Enter value" << endl;
                        cin >> newValue;
                        subTree -> Append(newValue);
                    }
                    bool containsSubTree = tree -> SearchSubTree(*subTree);
                    if (containsSubTree) {
                        cout << "Contains sub tree" << endl;
                    } else {
                        cout << "Does not contain sub tree" <<  endl;
                    }
                    //cout << containsSubTree << endl;
                    break;
                }
                case 8: {
                    //TODO Balance
                    break;
                }
                case 9: {
                    Tree<int>* mapTree = tree -> Map(multiply);
                    cout << "Mapped tree:" << endl;
                    mapTree -> printOutput();
                    break;
                }
                case 10: {
                    Tree<int>* whereTree = tree -> Where(isEven);
                    cout << "Where tree made" << endl;
                    whereTree -> printOutput();
                    break;
                }
                case 11: {
                    //TODO Reduce
                    //Tree<int>* reduceTree = tree -> Reduce(reducer, 0);
                    break;
                }
                case 12: {
                    cout << "Written the tree to string" << endl;
                    string line;
                    string* newString = tree -> IntoString(tree -> getRoot(), &line);
                    cout << *newString << endl;
                    break;
                }
                case 13: {
                    string treeString;
                    cout << "Enter the string please" << endl;
                    cin >> treeString;
                    auto* treeFromString = new Tree<int>();
                    int start = 0;
                    treeFromString -> setRoot(tree -> fromString(treeString, &start));
                    treeFromString -> printOutput();
                    break;
                }
                case 14: {
                    int s;
                    int n;
                    cout << "Number of elements in the tree: " << endl;
                    cin >> n;
                    for (int i = 0; i < n; ++i) {
                        cout << "Enter value" << endl;
                        cin >> s;
                        tree -> AppendBalanced(s);
                    }
                    break;
                }
                case 0: {
                    break;
                }
                default:
                    break;
            }
        } while (input != 0);
    } else {
        Tree<double>* tree = nullptr;
        int input = 10;
        do {
            cin >> input;
        } while (input != 0);
    }
}

