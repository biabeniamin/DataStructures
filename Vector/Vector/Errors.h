#include<stdio.h>
#include "Types.h"
command *lastCommandWithError;
void errorDetected(command *com,errorsTypes type);
int checkParameters(command* com, dataType types[], int typesCount);
void checkUnrecognizedCommandAfterCommand(command *com, int typesCount);