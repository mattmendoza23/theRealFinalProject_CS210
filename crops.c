#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "crops.h"

void updateCrops(cropTile** listOfCrops, int cropTotal, time_t* cropTime){
    int i = 0;
    //while loop runs through each crop
    while(i < cropTotal){
        //for loop runs until tile limit is hit, or we run out of crops
        //this allows the crops to have a not-completely filled row
        for (int j = 0; j < TILES_TO_TOP && i < cropTotal; j++){
            //move timers
            double deltaTime = deltaTimeNum(cropTime);
            listOfCrops[i][j].growthTimer -= deltaTime;
            listOfCrops[i][j].wateredTimer -= deltaTime;

            //update status
            if (listOfCrops[i][j].growthTimer <= 0 || !listOfCrops[i][j].isDead){
                listOfCrops[i][j].isGrown == true;
            }
            if (listOfCrops[i][j].wateredTimer <= 0 || !listOfCrops[i][j].isGrown){
                listOfCrops[i][j].isDead == true;
            }
        }
    }
}


void loadCropImages(cropInfo* infoToEdit){
    if (strcmp(infoToEdit->name, WHEAT_NAME) == 0){
        //load images into struct info
        //HBITMAP infoToEdit->cropImages[0] = (HBITMAP)LoadImageW(NULL, IMAGE_CONST, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        //need to repeat for each individual image, doing in for loop is beyond my knowledge
        //image const is defined with the struct info in the h file
    }
}


double deltaTimeNum(time_t* previousTime){
    //function will return how much time has passed since the last function call
    //time is kept in variable defined in the main
    //that variable is updated when passed into this function
    time_t currentTime = time(0);
    double deltaTime = difftime(currentTime, *previousTime);
    *previousTime = currentTime;
    return deltaTime;
}