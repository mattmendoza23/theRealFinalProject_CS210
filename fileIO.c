#include <stdio.h>
#include <stdlib.h>

#include "crops.h"

//funct 3
/*
void createFile(char fileName[], cropTile** crops, int* plotWidth, int* plotHeight, int seedCountArray[], int* playerCash){
    FILE* file = safeOpenFile(fileName, 'wb');

    //places cash info, seed counts, plot counts, then crops
    fwrite(playerCash, sizeof(int), 1, file);
    fwrite(seedCountArray, sizeof(int), SEED_TYPE_COUNT, file);
    fwrite(plotWidth, sizeof(int), 1, file);
    fwrite(plotHeight, sizeof(int), 1, file);

    //loop iterates and writes info file
    for (int i = 0; i < plotWidth; i++){
        fwrite(crops[i], sizeof(cropTile), plotHeight, file);
    }

    fclose(file);
}
*/

FILE* safeOpenFile(char fileName[], char mode[]){
    //file open function 
    FILE* file = fopen(fileName, mode);

    if (file == NULL){
        fprintf(stderr, "ERR: Failed file open\n");
        exit(1);
    }

    return file;
}

//funct 4
void openFile(char fileName[], cropTile** crops, int* plotWidth, int* plotHeight, int* playerCash){
    FILE* file = safeOpenFile(fileName, "rb");

    fseek(file, 0, SEEK_SET);

    //grabs cash info, seed counts, plot count, then crops
    fread(playerCash, sizeof(int), 1, file);
    fread(plotWidth, sizeof(int), 1, file);
    fread(plotHeight, sizeof(int), 1, file);
    
    //start reallocing, should be malloced in main
    crops = (cropTile**)malloc(sizeof(cropTile*) * *plotWidth);
    
    //loop iterates over all plots, reallocs the row, then fills the items
    for (int i = 0; i < *plotWidth; i++){
            crops[i] = (cropTile*)malloc(sizeof(cropTile) * *plotHeight);
            fread(crops[i], sizeof(cropTile), *plotHeight, file);
    }
    
    fclose(file);
}

//funct 5
void saveFile(char fileName[], cropTile** crops, int* plotWidth, int* plotHeight, int* playerCash){
    FILE* file = safeOpenFile(fileName, "wb");

    //places cash info, seed counts, plot count, then crops
    fwrite(playerCash, sizeof(int), 1, file);
    fwrite(plotWidth, sizeof(int), 1, file);
    fwrite(plotHeight, sizeof(int), 1, file);

    //loop iterates and writes info file
    for (int i = 0; i < *plotWidth; i++){
        fwrite(crops[i], sizeof(cropTile), *plotHeight, file);
    }

    fclose(file);
}