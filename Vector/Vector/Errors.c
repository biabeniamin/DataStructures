#include "Errors.h"
void errorDetected(command *com, errorsTypes type)
{
	lastCommandWithError = com;
	switch (type)
	{
	case InstanceUnkown:
		WRITESTRING("Error: Instance unknown");
		break;
	case InexistantStructure:
		WRITESTRING("Error: Illegal operation. Data structure does not exist");
		break;
	case UnrecognizedCommand:
		WRITESTRING("Error: Unrecognized command: command");
		break;
	case TypeMismatch:
		WRITESTRING("Error: Type mismatch");
		break;
	case MissingValue:
		WRITESTRING("Error: Missing value");
		break;
	case IndexOutOfBounds:
		WRITESTRING("Error: Index out of bounds");
		break;
	case StructureEmpty:
		WRITESTRING("Printing: Structure is empty");
		break;
	case StructureAlreadyExists:
		WRITESTRING("Error: attempt to recreate an existing structure");
		break;
	case ItemNotFound:
		WRITESTRING("Cannot delete: Item not found");
		break;
	}
}
int checkParameters(command* com, dataType types[], int typesCount)
{
	if (typesCount > com->struc.dataTypeCount)
	{
		errorDetected(com, MissingValue);
		return 0;
	}
	for (int i = 0; i < typesCount; i++)
	{
		if (types[i] != com->struc.dataTypeOrder[i] && types[i]!=anything)
		{
			errorDetected(com, TypeMismatch);
			return 0;
		}
	}
	/*if (typesCount < com->struc.dataTypeCount)
	{
		errorDetected(com, UnrecognizedCommand);
		return 0;
	}*/
	return 1;
}
void checkUnrecognizedCommandAfterCommand(command *com, int typesCount)
{
	if (lastCommandWithError != com && typesCount < com->struc.dataTypeCount)
	{
		errorDetected(com, UnrecognizedCommand);
		for (int i = typesCount; i < com->struc.dataTypeCount; i++)
		{
			if (com->struc.dataTypeOrder[i] == integer)
				WRITEINT(com->parameters.values[i]);
			else
				if (com->struc.dataTypeOrder[i] == string)
					WRITESTRINGSAMELINE(com->parameters.values[i]);
		}
		WRITELINE();
		return;
	}
}