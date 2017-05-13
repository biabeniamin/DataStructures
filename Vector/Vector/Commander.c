#include "Errors.h"
#include "Commander.h"
#include "Vector.h"
#include "LinkedList.h"
#include "MinHeap.h"
#include "HashTable.h"
#include "BinarySearchTree.h"
#include "BalancedBST.h"
void giveBinarySearchTreeCommand(command *com)
{
	if (com->type == CreateBinarySearchTreeCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		createBinarySearchTree((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PrintBinarySearchTreeCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		printBinarySearchTree((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PreorderBinarySearchTreeCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		preorderBinarySearchTree((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == InorderBinarySearchTreeCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		inorderBinarySearchTree((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PostorderBinarySearchTreeCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		postorderBinarySearchTree((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == AddBinarySearchTreeItemsCommand)
	{
		dataType *types;
		types = malloc(com->struc.dataTypeCount * sizeof(dataType));
		if (com->struc.dataTypeCount < 2)
		{
			errorDetected(com, MissingValue);
			return;
		}
		if (com->struc.dataTypeOrder[1] != integer)
		{
			errorDetected(com, TypeMismatch);
			return;
		}
		types[0] = string;
		types[1] = integer;
		dataType last= anything;
		types = realloc(types, (((int)com->parameters.values[1]) + 2) * sizeof(dataType));
		for (int i = 2; i < (int)com->parameters.values[1] + 2; i++)
		{
			if (com->struc.dataTypeOrder[i] != last && last != anything)
			{
				errorDetected(com, TypeMismatch);
				return;
			}
			types[i] = com->struc.dataTypeOrder[i];
			last = com->struc.dataTypeOrder[i];
		}
		int typesCount = (int)com->parameters.values[1] + 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		free(types);
		addBinarySearchTreeItems(com);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == SearchBinarySearchTreeItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
		{
			return;
		}
		WRITEINTLINE(searchBinarySearchTreeItem((char*)com->parameters.values[0], com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteBinarySearchTreeItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteBinarySearchTreeItem((char*)com->parameters.values[0], com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == MergeBinarySearchTreeCommand)
	{
		dataType types[] = { string,string };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		mergeBinarySearchTrees((char*)com->parameters.values[0], (char*)com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == HightBinarySearchTree)
	{
		dataType types[] = { string,integer };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		WRITEINTLINE(hightBinarySearchTree((char*)com->parameters.values[0], (int)com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteBinarySearchTree)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteBinarySearchTree((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
}
void giveBalancedBSTCommand(command *com)
{
	if (com->type == CreateBalancedBSTCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		createBalancedBST((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PrintBalancedBSTCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		printBalancedBST((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PreorderBalancedBSTCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		preorderBalancedBST((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == InorderBalancedBSTCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		inorderBalancedBST((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PostorderBalancedBSTCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		postorderBalancedBST((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == AddBalancedBSTItemsCommand)
	{
		dataType *types;
		types = malloc(com->struc.dataTypeCount * sizeof(dataType));
		if (com->struc.dataTypeCount < 2)
		{
			errorDetected(com, MissingValue);
			return;
		}
		if (com->struc.dataTypeOrder[1] != integer)
		{
			errorDetected(com, TypeMismatch);
			return;
		}
		types[0] = string;
		types[1] = integer;
		dataType last= anything;
		types = realloc(types, (((int)com->parameters.values[1]) + 2) * sizeof(dataType));
		for (int i = 2; i < (int)com->parameters.values[1] + 2; i++)
		{
			if (com->struc.dataTypeOrder[i] != last && last != anything)
			{
				errorDetected(com, TypeMismatch);
				return;
			}
			types[i] = com->struc.dataTypeOrder[i];
			last = com->struc.dataTypeOrder[i];
		}
		int typesCount = (int)com->parameters.values[1] + 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		free(types);
		addBalancedBSTItems(com);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == SearchBalancedBSTItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
		{
			return;
		}
		WRITEINTLINE(searchBalancedBSTItem((char*)com->parameters.values[0], com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteBalancedBSTItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteBalancedBSTItem((char*)com->parameters.values[0], com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == MergeBalancedBSTCommand)
	{
		dataType types[] = { string,string };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		mergeBalancedBSTs((char*)com->parameters.values[0], (char*)com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == HightBalancedBST)
	{
		dataType types[] = { string,integer };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		WRITEINTLINE(hightBalancedBST((char*)com->parameters.values[0], (int)com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteBalancedBST)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteBalancedBST((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
}
void giveHashTableCommand(command *com)
{
	if (com->type == CreateHashTableCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		createHashTable((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PrintHashTableCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		printHashTable((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == AddHashTableItemsCommand)
	{
		dataType *types;
		types = malloc(com->struc.dataTypeCount * sizeof(dataType));
		if (com->struc.dataTypeCount < 2)
		{
			errorDetected(com, MissingValue);
			return;
		}
		if (com->struc.dataTypeOrder[1] != integer)
		{
			errorDetected(com, TypeMismatch);
			return;
		}
		types[0] = string;
		types[1] = integer;
		dataType last= anything;
		types = realloc(types, (((int)com->parameters.values[1]) + 2) * sizeof(dataType));
		for (int i = 2; i < (int)com->parameters.values[1] + 2; i++)
		{
			if (com->struc.dataTypeOrder[i] != last && last != anything)
			{
				errorDetected(com, TypeMismatch);
				return;
			}
			types[i] = com->struc.dataTypeOrder[i];
			last = com->struc.dataTypeOrder[i];
		}
		int typesCount = (int)com->parameters.values[1] + 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		free(types);
		addHashTableItems(com);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}

	else if (com->type == DeleteHashTableItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteHashTableItem((char*)com->parameters.values[0], com->parameters.values[1], com->struc.dataTypeOrder[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == SearchHashTableItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
		{
			return;
		}
		WRITEINTLINE(searchHashTableItem((char*)com->parameters.values[0], com->parameters.values[1], com->struc.dataTypeOrder[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}

	else if (com->type == DeleteHashTable)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteHashTable((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
}
void giveLinkedListCommand(command *com)
{
	if (com->type == CreateLinkedListCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		createLinkedList((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PrintLinkedListCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		printLinkedList((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == AddLinkedListItemsCommand)
	{
		dataType *types;
		types = malloc(com->struc.dataTypeCount * sizeof(dataType));
		if (com->struc.dataTypeCount < 2)
		{
			errorDetected(com, MissingValue);
			return;
		}
		if (com->struc.dataTypeOrder[1] != integer)
		{
			errorDetected(com, TypeMismatch);
			return;
		}
		types[0] = string;
		types[1] = integer;
		dataType last= anything;
		types = realloc(types, (((int)com->parameters.values[1]) + 2) * sizeof(dataType));
		for (int i = 2; i < (int)com->parameters.values[1] + 2; i++)
		{
			if (com->struc.dataTypeOrder[i] != last && last != anything)
			{
				errorDetected(com, TypeMismatch);
				return;
			}
			types[i] = com->struc.dataTypeOrder[i];
			last = com->struc.dataTypeOrder[i];
		}
		int typesCount = (int)com->parameters.values[1] + 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		free(types);
		addLinkedListItems(com);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PutLinkedListItemCommand)
	{
		dataType types[] = { string ,integer ,integer };
		int typesCount = 3;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		putLinkedListItems((char*)com->parameters.values[0], (int)com->parameters.values[1], (int)com->parameters.values[2]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}

	else if (com->type == GetLinkedListItemCommand)
	{
		dataType types[] = { string ,integer };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		WRITEINTLINE(getLinkedListItem((char*)com->parameters.values[0], (int)com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteLinkedListItemCommand)
	{
		dataType types[] = { string ,integer };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteLinkedListItem((char*)com->parameters.values[0], (int)com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == SearchLinkedListItemCommand)
	{
		dataType types[] = { string ,integer };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
		{
			return;
		}
		WRITEINTLINE(searchLinkedListItem((char*)com->parameters.values[0], com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == SortLinkedListCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		sortLinkedList((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == MergeLinkedLists)
	{
		dataType types[] = { string,string };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		mergeLinkedLists((char*)com->parameters.values[0], (char*)com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteLinkedList)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteLinkedList((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
}
void giveHeapCommand(command *com)
{
	if (com->type == CreateHeapCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		createHeap((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PrintHeapCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		printHeap((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == AddHeapItemsCommand)
	{
		dataType *types;
		types = malloc(com->struc.dataTypeCount * sizeof(dataType));
		if (com->struc.dataTypeCount < 2)
		{
			errorDetected(com, MissingValue);
			return;
		}
		if (com->struc.dataTypeOrder[1] != integer)
		{
			errorDetected(com, TypeMismatch);
			return;
		}
		types[0] = string;
		types[1] = integer;
		dataType last= anything;
		types = realloc(types, (((int)com->parameters.values[1]) + 2) * sizeof(dataType));
		for (int i = 2; i < (int)com->parameters.values[1] + 2; i++)
		{
			if (com->struc.dataTypeOrder[i] != last && last != anything)
			{
				errorDetected(com, TypeMismatch);
				return;
			}
			types[i] = com->struc.dataTypeOrder[i];
			last = com->struc.dataTypeOrder[i];
		}
		int typesCount = (int)com->parameters.values[1] + 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		free(types);
		addHeapItems(com);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == GetHeapMinCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		WRITEINTLINE(getHeapMin((char*)com->parameters.values[0]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}

	else if (com->type == DeleteHeapMinCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteHeapMin((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteHeapItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteHeapItem((char*)com->parameters.values[0], &com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == MergeHeapCommand)
	{
		dataType types[] = { string,string };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		mergeHeaps((char*)com->parameters.values[0], (char*)com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteHeap)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteHeap((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
}
void giveVectorCommand(command *com)
{
	if (com->type == CreateVectorCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		createVector((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PrintVectorCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		printVector((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == AddVectorItemsCommand)
	{
		dataType *types;
		types = malloc(com->struc.dataTypeCount * sizeof(dataType));
		if (com->struc.dataTypeCount < 2)
		{
			errorDetected(com, MissingValue);
			return;
		}
		if (com->struc.dataTypeOrder[1] != integer)
		{
			errorDetected(com, TypeMismatch);
			return;
		}
		types[0] = string;
		types[1] = integer;
		dataType last= anything;
		types = realloc(types, (((int)com->parameters.values[1]) + 2) * sizeof(dataType));
		for (int i = 2; i < (int)com->parameters.values[1] + 2; i++)
		{
			if (com->struc.dataTypeOrder[i] != last && last != anything)
			{
				errorDetected(com, TypeMismatch);
				return;
			}
			types[i] = com->struc.dataTypeOrder[i];
			last = com->struc.dataTypeOrder[i];
		}
		int typesCount = (int)com->parameters.values[1] + 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		free(types);
		addVectorItems(com);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == PutVectorItemCommand)
	{
		dataType types[] = { string ,integer ,anything };
		int typesCount = 3;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		putVectorItems((char*)com->parameters.values[0], (int)com->parameters.values[1], (int)com->parameters.values[2]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == GetVectorItemCommand)
	{
		dataType types[] = { string ,integer };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		WRITEINTLINE(getVectorItem((char*)com->parameters.values[0], (int)com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteVectorItemCommand)
	{
		dataType types[] = { string ,integer };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteVectorItem((char*)com->parameters.values[0], (int)com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == SearchVectorItemCommand)
	{
		dataType types[] = { string ,anything };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		WRITEINTLINE(searchVectorItem((char*)com->parameters.values[0], (int)com->parameters.values[1]));
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == SortVectorCommand)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		sortVector((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == MergeVectors)
	{
		dataType types[] = { string,string };
		int typesCount = 2;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		mergeVectors((char*)com->parameters.values[0], (char*)com->parameters.values[1]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
	else if (com->type == DeleteVector)
	{
		dataType types[] = { string };
		int typesCount = 1;
		if (checkParameters(com, types, typesCount) == 0)
			return;
		deleteVector((char*)com->parameters.values[0]);
		checkUnrecognizedCommandAfterCommand(com, typesCount);
	}
}
void giveCommand(command *com)
{
	giveVectorCommand(com);
	giveLinkedListCommand(com);
	giveHashTableCommand(com);
	giveHeapCommand(com);
	giveBinarySearchTreeCommand(com);
	giveBalancedBSTCommand(com);
}