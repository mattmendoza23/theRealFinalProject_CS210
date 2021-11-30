/** fileIO.h
 */

#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

#include "crops.h"

//funct 3
/* code was redundant
void createFile(char fileName[], cropTile** crops, int* plotWidth, int* plotHeight, int seedCountArray[], int* playerCash);
*/

FILE* safeOpenFile(char fileName[], char mode[]);
//funct 4
void openFile(char fileName[], cropTile** crops, int* plotWidth, int* plotHeight, int* playerCash);

//funct 5
void saveFile(char fileName[], cropTile** crops, int* plotWidth, int* plotHeight, int* playerCash);


#endif // FILEIO_H