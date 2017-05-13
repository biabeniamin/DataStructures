#include "Types.h"
//creare instanta vector
void createVector(char* name);
//comanda printare vector
void printVector(char* name);
//adaugarea valorilor in instanta pasata ca parametru
void addVectorItems(command *com);
//pune o valoare la o anumita pozitie
void putVectorItems(char* name, int index, Item value);
//returneaza valoarea care se afla la pozitia indicata
Item getVectorItem(char* name, int index);
//sterge un element la pozitia indicata
void deleteVectorItem(char* name, int index);
//cauta o anumita valoare in vector
int searchVectorItem(char* name, Item value);
//sorteaza valorile
void sortVector(char* name);
//face merge la 2 instante
void mergeVectors(char *inst1, char *inst2);
//sterge instanta de vector specifficata
void deleteVector(char* name);