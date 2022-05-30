//
// Created by - on 30.05.2022.
//

#include "Tree.h"
#include <string>
#include <cassert>
#include "TreeTest.h"

using namespace std;

int multiplyTest(int a) {
    return a * 2;
}

bool isEvenTest(int a) {
    return (a % 2 == 0);
}

void testAppend() {
    auto* tree = new Tree<int>();
    tree -> Append(2);
    tree -> Append(1);
    tree -> Append(3);
    assert(tree -> getRoot() -> value == 2);
    assert(tree -> getRoot() -> left -> value == 1);
    assert(tree -> getRoot() -> right -> value == 3);
    int start = 0;
    auto* testTree = new Tree<int>(tree -> fromString("2(1()())(3()())", &start));
    assert(tree -> SearchSubTree(*testTree));
}

void testRemove() {
    auto* tree = new Tree<int>();
    tree -> Append(4);
    tree -> Append(2);
    tree -> Append(1);
    tree -> Append(3);
    tree -> Remove(4);
    assert(tree -> getRoot() -> value == 2);
    assert(tree -> getRoot() -> left -> value == 1);
    assert(tree -> getRoot() -> right -> value == 3);
    int start = 0;
    auto* testTree = new Tree<int>(tree -> fromString("2(1()())(3()())", &start));
    assert(tree -> SearchSubTree(*testTree));
}

void testSearch() {
    auto* tree = new Tree<int>();
    int start = 0;
    auto* testTree = new Tree<int>(tree -> fromString("2(1()())(3()())", &start));
    assert(testTree -> Search(2));
}

void testSearchSubTree() {
    auto* tree = new Tree<int>();
    tree -> Append(4);
    tree -> Append(2);
    tree -> Append(1);
    tree -> Append(3);
    int start = 0;
    auto* testTree = new Tree<int>(tree -> fromString("2(1()())(3()())", &start));
    assert(tree -> SearchSubTree(*testTree));
    tree -> Remove(2);
    assert(!(tree -> SearchSubTree(*testTree)));
}

void testMap() {
    auto* tree = new Tree<int>();
    int start = 0;
    auto* testTree = new Tree<int>(tree -> fromString("2(1()())(3()())", &start));
    start = 0;
    auto* testingMappedTree = new Tree<int>(testTree -> fromString("4(2()())(6()())", &start));
    auto* mappedTree = testTree -> Map(multiplyTest);
    assert(mappedTree -> SearchSubTree(*testingMappedTree));
    assert(mappedTree -> getRoot() -> value == testingMappedTree -> getRoot() -> value);
}

void testWhere() {
    auto* tree = new Tree<int>();
    int start = 0;
    auto* testTree = new Tree<int>(tree -> fromString("2(1()())(3()())", &start));
    start = 0;
    auto* testingWhereTree = new Tree<int>(testTree -> fromString("2()()", &start));
    auto* whereTree = testTree -> Where(isEvenTest);
    assert(whereTree -> SearchSubTree(*testingWhereTree));
    assert(whereTree -> getRoot() -> value == testingWhereTree -> getRoot() -> value);
}

void testToString() {
    auto* tree = new Tree<int>();
    tree -> Append(2);
    tree -> Append(3);
    tree -> Append(1);
    string line;
    string* result = tree ->IntoString(tree -> getRoot(), &line);
    assert(*result == "2(1()())(3()())");
}

void testFromString() {
    string testString = "2(1()())(3()())";
    int start = 0;
    auto* tree = new Tree<int>();
    tree -> setRoot(tree -> fromString(testString, &start));
    auto* testingTree = new Tree<int>();
    testingTree -> Append(2);
    testingTree -> Append(1);
    testingTree -> Append(3);
    assert(tree -> SearchSubTree(*testingTree));
    assert(tree -> getRoot() -> value == testingTree -> getRoot() -> value);
}

void tests() {
    testAppend();
    testRemove();
    testSearch();
    testSearchSubTree();
    testMap();
    testWhere();
    testToString();
    testFromString();
    cout << "All tree tests passed" << endl;
}