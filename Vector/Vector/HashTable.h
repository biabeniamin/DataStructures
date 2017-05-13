#include "Types.h"
//creaza o instanta noua cu functia standard
void createHashTable(char* name);
//creaza o instana noua cu o functie specificata
void createHashTableWithFunction(char* name, unsigned long(*hashFunction)(unsigned char*));
//printeaza o lista sortata
void printHashTable(char* name);
//adauga valori in instanta specificata
void addHashTableItems(command *com);
//se executa rehash la tablou,primind o functie de dispersie
void reHashTable(char* name, unsigned long(*hashFunction)(unsigned char*));
//sterge o valoare specificata
void deleteHashTableItem(char* name, Item *value, dataType type);
//cauta o valoare in tabel
int searchHashTableItem(char* name, Item value, dataType type);
//sterge instanta specificata
void deleteHashTable(char* name);