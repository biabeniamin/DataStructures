#include "Types.h"
//creaza o instanta noua
void createBalancedBST(char* name);
//printeaza valorile din instanta sub forma de arbore
void printBalancedBST(char* name);
//adauga elementele in arbore si face auto echilibrarea
void addBalancedBSTItems(command *com);
//printeaza elementele in preordine
void preorderBalancedBST(char* name);
//printeaza elementele in postordine
void postorderBalancedBST(char* name);
//printeaza elementele in inorder
void inorderBalancedBST(char* name);
//sterge elementul care are valoarea egala cu ccea specificata 
Item *deleteBalancedBSTItem(char* name, Item *value);
//returneaza valoarea cautatata daca ii gasita
Item *searchBalancedBSTItem(char* name, Item *value);
//face merge la 2 instante
void mergeBalancedBSTs(char *inst1, char *inst2);
//sterge o instanta
void deleteBalancedBST(char* name);
