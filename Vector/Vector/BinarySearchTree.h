#include "Types.h"
//creaza o instanta noua
void createBinarySearchTree(char* name);
//printeaza valorile din instanta sub forma de arbore
void printBinarySearchTree(char* name);
//adauga elementele in arbore
void addBinarySearchTreeItems(command *com);
//printeaza elementele in preordine
void preorderBinarySearchTree(char* name);
//printeaza elementele in postordine
void postorderBinarySearchTree(char* name);
//printeaza elementele in inorder
void inorderBinarySearchTree(char* name);
//sterge elementul care are valoarea egala cu ccea specificata 
Item *deleteBinarySearchTreeItem(char* name, Item *value);
//returneaza valoarea cautatata daca ii gasita
Item *searchBinarySearchTreeItem(char* name, Item *value);
//face merge la 2 instante
void mergeBinarySearchTrees(char *inst1, char *inst2);
//sterge o instanta
void deleteBinarySearchTree(char* name);