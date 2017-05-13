#include "Types.h"
//creaza o instanta noua
void createHeap(char* name);
//printeaza valorile din instanta specificata
void printHeap(char* name);
//adauga elemente la instanta specificata
void addHeapItems(command *com);
//returneaza valoarea minima din instana specificata
Item getHeapMin(char* name);
//sterge valoarea cea mai mica
void deleteHeapMin(char* name);
//sterge o valoare specificata daca este gasita
void deleteHeapItem(char* name, Item *value);
//face merge la doua instante
void mergeHeaps(char *inst1, char *inst2);
//sterge o instanta specificata
void deleteHeap(char* name);