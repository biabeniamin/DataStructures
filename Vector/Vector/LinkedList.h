#include "Types.h"
//creaza instanta de lista
void createLinkedList(char* name);
//printeaza instanta
void printLinkedList(char* name);
//adauga valori in instanta
void addLinkedListItems(command *com);
//pune o valoare la un index specificat
void putLinkedListItems(char* name, int index, Item value);
//returneaza valoarea la un index specificat
Item getLinkedListItem(char* name, int index);
//sterge o valoare la un index specificat
void deleteLinkedListItem(char* name, int index);
//cauta o valoarea in lista si returneazza daca a fost gasit
int searchLinkedListItem(char* name, Item value);
//sorteaza lista
void sortLinkedList(char* name);
//face merge la 2 liste
void mergeLinkedLists(char *inst1, char *inst2);
//sterge o lista
void deleteLinkedList(char* name);