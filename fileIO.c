#include <stdio.h>

#include "crops.h"

//funct 3
void createFile(char fileName[], cropTile** crops, int* plotCount, int seedCountArray[], int* playerCash){
    FILE* file = safeOpenFile(fileName, 'w');

    //places cash info, seed counts, plot count, then crops
    fwrite(playerCash, sizeof(int), 1, file);
    fwrite(seedCountArray, sizeof(int), SEED_TYPE_COUNT, file);
    fwrite(plotCount, sizeof(int), 1, file);

    //loop iterates and writes info file
    int i = 0;
    while (i < *plotCount / TILES_TO_TOP + 1){
        if (*plotCount / TILES_TO_TOP + 1 >= 10){
            fwrite(crops[i], sizeof(cropTile), 10, file);
            i++;
        }
        else{
            fwrite(crops[i], sizeof(cropTile), i, file);
            i++;
        }
    }

    fclose(file);
}

//funct 4
void openFile(char fileName[], cropTile** crops, int* plotCount, int seedCountArray[], int* playerCash){
    FILE* file = safeOpenFile(fileName, 'r');

    //grabs cash info, seed counts, plot count, then crops
    fread(playerCash, sizeof(int), 1, file);
    fread(seedCountArray, sizeof(int), SEED_TYPE_COUNT, file);
    fread(plotCount, sizeof(int), 1, file);

    //start reallocing, should be malloced in main
    realloc((cropTile**)crops, sizeof(cropTile*) * *plotCount / TILES_TO_TOP + 1);

    //loop iterates over all plots, reallocs the row, then fills the items
    int i = 0;
    while (i < *plotCount / TILES_TO_TOP + 1){
        if (*plotCount / TILES_TO_TOP + 1 >= 10){
            realloc((cropTile*)crops, sizeof(cropTile) * *plotCount / TILES_TO_TOP + 1);
            fread(crops[i], sizeof(cropTile), 10, file);
            i++;
        }
        else{
            realloc((cropTile*)crops, sizeof(cropTile) * *plotCount / TILES_TO_TOP + 1);
            fread(crops[i], sizeof(cropTile), i, file);
            i++;
        }
    }

    fclose(file);
}

//funct 5
void saveFile(char fileName[], cropTile** crops, int* plotCount, int seedCountArray[], int* playerCash){
    FILE* file = safeOpenFile(fileName, 'w');

    //places cash info, seed counts, plot count, then crops
    fwrite(playerCash, sizeof(int), 1, file);
    fwrite(seedCountArray, sizeof(int), SEED_TYPE_COUNT, file);
    fwrite(plotCount, sizeof(int), 1, file);

    //writes all items into the file
    int i = 0;
    while (i < *plotCount / TILES_TO_TOP + 1){
        if (*plotCount / TILES_TO_TOP + 1 >= 10){
            fwrite(crops[i], sizeof(cropTile), 10, file);
            i++;
        }
        else{
            fwrite(crops[i], sizeof(cropTile), i, file);
            i++;
        }
    }

    fclose(file);
}


FILE* safeOpenFile(char fileName[], char mode){
    //file open function 
    FILE* file = fopen(fileName, mode);

    if (file == NULL){
        fprintf(stderr, "ERR: Failed file open\n");
        exit(1);
    }

    return file;
}