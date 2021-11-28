#include <stdio.h>

#include "crops.h"

//funct 3
void createFile(char fileName[], cropTile** crops, int* plotCount, int seedCountArray[], int* playerCash);

//funct 4
void openFile(char fileName[], cropTile** crops, int* plotCount, int seedCountArray[], int* playerCash);

//funct 5
void saveFile(char fileName[], cropTile** crops, int* plotCount, int seedCountArray[], int* playerCash);

FILE* safeOpenFile(char fileName[], char mode);