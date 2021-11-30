#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "crops.h"
#include "audioVisual.h"

void updateCrops(cropTile** listOfCrops, int plotWidth, int plotHeight, time_t* cropTime){
    //loop iterates over each crop tile
    for (int i = 0; i < plotWidth; i++){
        for (int j = 0; j < plotHeight; j++){
            int deltaTime = TIME_BETWEEN_TICKS;
            listOfCrops[i][j].growthTimer += deltaTime;
            listOfCrops[i][j].wateredTimer -= deltaTime;

            //update status
            if (listOfCrops[i][j].growthTimer >= listOfCrops[i][j].staticInfo.growthTime && !listOfCrops[i][j].isDead){
                listOfCrops[i][j].isGrown = true;
            }
            if (listOfCrops[i][j].wateredTimer <= 0){
                listOfCrops[i][j].isDead = true;
                listOfCrops[i][j].isGrown = false;
            }
        }
    }
}

cropInfo loadTestCrop(HWND hwnd){
    cropInfo testCrop;
    
    strcpy(testCrop.name,TEST_CROP_NAME);
    testCrop.growthTime = TEST_CROP_GROWTH_TIME;
    testCrop.sellPrice = TEST_CROP_SELL_PRICE;
    testCrop.waterTime = TEST_CROP_WATER_TIME;
    loadCropImages(testCrop.cropImages,TEST_CROP_NAME,hwnd);
    
    return testCrop;
}

void loadCropImages(HBITMAP toEdit[], char name[],HWND hwnd){
    if (strcmp(name, WHEAT_NAME) == 0){
        //load images into struct info
        //HBITMAP infoToEdit->cropImages[0] = (HBITMAP)LoadImageW(NULL, IMAGE_CONST, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        //need to repeat for each individual image, doing in for loop is beyond my knowledge
        //image const is defined with the struct info in the h file
    }
    if (strcmp(name, TEST_CROP_NAME) == 0){
        //load images into struct info

        toEdit[0] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_1, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[1] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_2, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[2] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_3, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[3] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_4, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[4] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_5, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[5] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_6, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[6] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_7, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[7] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_8, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[8] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_9, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[9] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_10, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[10] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_11, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        toEdit[11] = (HBITMAP)LoadImageW(NULL, TEST_CROP_IMAGE_PATH_12, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        //need to repeat for each individual image, doing in for loop is beyond my knowledge
        //image const is defined with the struct info in the h file
        
    }
}

void playerUpdateCrops(cropTile** listOfCrops, int plotWidth, int plotHeight, POINT mousePosition){
    //int division should give screen values
    int xPos = mousePosition.x / IMAGE_SIZE_PIXELS - DISTANCE_FROM_SIDE_TO_CROPS;
    int yPos = mousePosition.y / IMAGE_SIZE_PIXELS;
    if (xPos >= 0 && xPos < plotWidth){
        if (yPos >= 0 && yPos < plotHeight){
            listOfCrops[xPos][yPos].wateredTimer = listOfCrops[xPos][yPos].staticInfo.waterTime;
        }
    }

}