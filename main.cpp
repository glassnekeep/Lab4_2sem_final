#include <iostream>
#include "Tree.h"

using namespace std;

void menu() {
    int type;
    cout << "Choose data type: 1-Int, 2-Double: " << endl;
    cin >> type;
    if (type == 1) {
        Tree<int>* tree = nullptr;
        int input = 10;
        do {
            cout << "Choose the operation:" << endl;
            cout << "1) Insert element;\n"
                    "2) Delete element;\n"
                    "3) Search an element;\n"
                    "4) Path the binary search tree;\n"
                    "5) Print the tree;\n"
                    "6) Check the element;\n"
                    "7) Print the tree to string;\n"
                    "0) Exit the menu;\n" << endl;
            cin >> input;
            switch (input) {
                case 1:
                    int s;
                    int n;
                    cout << "Number of elements in the tree: " << endl;
                    cin >> n;
                    for (int i = 0; i < n; ++i) {
                        cout << "Enter value" << endl;
                        cin >> s;
                        tree -> Append(tree, s);
                    }
                    break;
                case 2:
                    cout << "Enter element" << endl;
                    int p;
                    cin >> p;
                    tree -> Remove(p);
                    cout << endl;
                    break;
                case 3:
                    cout << "Enter element" << endl;
                    int q;
                    cin >> q;
                    bool found = tree -> Search(q);
                    cout << found << endl;
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
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

int main() {
    cout << "Choose data type: 1-Double, 2-Int: " << endl;
    int type;
    cin >> type;
    auto *tree = new Tree<int>();
    int input;
    input = 10;
    while (input != 0) {
        cout << "Choose the operation:" << endl;
        cout << "1) Insert element;\n"
                "2) Delete element;\n"
                "3) Search an element;\n"
                "4) Pass the binary search tree;\n"
                "5) Print the tree;\n"
                "6) Check the element;\n"
                "7) Print the tree to string;\n"
                "0) Exit the menu;\n" << endl;
        cin >> input;
        if (input == 1) {
            int s;
            int n;
            cout << "Number of elements in the tree: " << endl;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                cout << "Enter value" << endl;
                cin >> s;
                tree -> Append(s);
            }
        }
        if (input == 2) {
            cout << "Enter element" << endl;
            int p;
            cin >> p;
            tree -> Remove(p);
            cout << endl;
        }
        if (input == 3) {
            cout << "Enter element" << endl;
            int q;
            cin >> q;
            tree -> Search(q);
            cout << endl;
        }
        /*if (input == 4) {
            cout << "Choose the passing algorithm: 1-PKL 2-PLK 3-LPK 4-LKP 5-KLP 6-KPL" << endl;
            int q;
            cin >> q;
            switch (q) {
                case 1:
                    cout << "Passing PKL:" << endl;
                    Tree->PKL(Tree);
                    break;
                case 2:
                    cout << "Passing PLK:" << endl;
                    Tree->PLK(Tree);
                    break;
                case 3:
                    cout << "Passing LPK:" << endl;
                    Tree->LPK(Tree);
                    break;
                case 4:
                    cout << "Passing LKP:" << endl;
                    Tree->LKP(Tree);
                    break;
                case 5:
                    cout << "Passing LKP:" << endl;
                    Tree->KLP(Tree);
                    break;
                case 6:
                    cout << "Passing KPL:" << endl;
                    Tree->KPL(Tree);
                    break;
            }
            cout << endl;
        }*/
        if (input == 5) {
            cout << "Binary tree: " << endl;
            tree->printOutput();
            tree -> Output();
            //tree -> printOutput();
        }
        if (input == 6) {
            int q;
            cout << "Enter element: " << endl;
            cin >> q;
            bool ans = tree->SearchNode(q);
            if (ans)
                cout << "Element is in the tree" << endl;
            else
                cout << "No such element in the tree" << endl;
        }
        /*if (input == 7) {
            string *line = new string();
            line = Tree->writeToString(Tree, line);
            cout << *line << endl;
        }*/
    }
    return 0;
}

ostream &operator<<(ostream &out, string *str) {
    for (int i = 0; i < str->length(); i++)
        out << str[i];
    return out;
}
