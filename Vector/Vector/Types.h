/*
1.commander=add value of diffrent type
2.CreateHashTable - creare instan?? HashTable i. Se transmite ca parametru func?ia de dispersie
*/
#include<stdio.h>
#ifndef TYPES_H
#define TYPES_H

FILE *outputFIle;

#define WRITETOFILE 1
#if WRITETOFILE==0
#define WRITESTRING(text) printf("%s\n",text)
#define WRITEINT(value) printf("%d ",(int)value)
#define WRITEINTLINE(value) printf("%d\n",(int)value)
#define WRITELINE() printf("\n")
#define WRITESTRINGSAMELINE(text) printf("%s ",text)
#else
#define WRITESTRING(text) fprintf(outputFIle,"%s\n",text)
#define WRITESTRINGSAMELINE(text) fprintf(outputFIle,"%s ",text)
#define WRITEINT(value) fprintf(outputFIle,"%d ",(int)value)
#define WRITEINTLINE(value) fprintf(outputFIle,"%d\n",(int)value)
#define WRITELINE() fprintf(outputFIle,"\n")
#endif // WRITETOFILE==0
#define WRITESPACES(count) for(int i=0;i<count;++i) WRITESTRINGSAMELINE("");

typedef enum
{
	CreateVectorCommand,
	PrintVectorCommand,
	AddVectorItemsCommand,
	PutVectorItemCommand,
	GetVectorItemCommand,
	DeleteVectorItemCommand,
	SearchVectorItemCommand,
	SortVectorCommand,
	MergeVectors,
	DeleteVector,
	CreateLinkedListCommand,
	PrintLinkedListCommand,
	AddLinkedListItemsCommand,
	PutLinkedListItemCommand,
	GetLinkedListItemCommand,
	DeleteLinkedListItemCommand,
	SearchLinkedListItemCommand,
	SortLinkedListCommand,
	MergeLinkedLists,
	DeleteLinkedList,
	CreateHashTableCommand,
	PrintHashTableCommand,
	AddHashTableItemsCommand,
	DeleteHashTableItemCommand,
	SearchHashTableItemCommand,
	ReaHashTableCommand,
	DeleteHashTable,
	CreateHeapCommand,
	PrintHeapCommand,
	AddHeapItemsCommand,
	GetHeapMinCommand,
	DeleteHeapMinCommand,
	DeleteHeapItemCommand,
	MergeHeapCommand,
	DeleteHeap,
	CreateBinarySearchTreeCommand,
	PrintBinarySearchTreeCommand,
	PreorderBinarySearchTreeCommand,
	InorderBinarySearchTreeCommand,
	PostorderBinarySearchTreeCommand,
	AddBinarySearchTreeItemsCommand,
	SearchBinarySearchTreeItemCommand,
	DeleteBinarySearchTreeItemCommand,
	MergeBinarySearchTreeCommand,
	HightBinarySearchTree,
	DeleteBinarySearchTree,
	CreateBalancedBSTCommand,
	PrintBalancedBSTCommand,
	PreorderBalancedBSTCommand,
	InorderBalancedBSTCommand,
	PostorderBalancedBSTCommand,
	AddBalancedBSTItemsCommand,
	SearchBalancedBSTItemCommand,
	DeleteBalancedBSTItemCommand,
	MergeBalancedBSTCommand,
	HightBalancedBST,
	DeleteBalancedBST
} commandType;
typedef enum
{
	integer,
	real,
	string,
	anything,
} dataType;
typedef struct
{
	int intCount;
	int doubleCount;
	int stringCount;
	int* dataTypeOrder;
	int dataTypeCount;
} structure;
typedef void* Item;
typedef struct linkedListStructure
{
	Item data;
	struct linkedListStructure *next;
	
} LinkedItem;
typedef struct binaryItemStructure
{
	Item data;
	struct binaryItemStructure *left;
	struct binaryItemStructure *right;

} BinaryItem;
typedef struct
{
	char* data;
	Item *values;
	int valuesCount;
} info;
typedef struct
{
	commandType type;
	info parameters;
	structure struc;
} command;
typedef enum
{
	InexistantStructure,
	UnrecognizedCommand,
	TypeMismatch,
	MissingValue,
	InstanceUnkown,
	IndexOutOfBounds,
	StructureEmpty,
	StructureAlreadyExists,
	ItemNotFound,
} errorsTypes;
#endif // !TYPES_H