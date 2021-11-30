#include <Windows.h>

#include "audioVisual.h"

void InitializeControls(HWND hWnd ,HWND screenSlots[16][10]){
    for (int i = 0; i < SLOT_SIZE_HORIZONTAL+DISTANCE_FROM_SIDE_TO_CROPS; i++){
        for(int j = 0; j < SLOT_SIZE_VERTICAL; j++){
            screenSlots[i][j] = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, i*IMAGE_SIZE_PIXELS, j*IMAGE_SIZE_PIXELS,0,0, hWnd, NULL, NULL, NULL);
            HBITMAP emptyImage = (HBITMAP)LoadImageW(NULL, L"images\\testImages\\black.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
            SendMessageW(screenSlots[i][j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)emptyImage);
        }
    }
}

//funct 2
void drawImage(HWND screenSlots[16][10] ,HBITMAP image, int x, int y){
    //function just makes loading an image less ambiguous for future coding
    SendMessageW(screenSlots[x][y], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
}

//funct 6
void drawCrops(HWND screenSlots[16][10], cropTile** crops, int plotWidth, int plotHeight){
    //loop iterates over each crop tile
    for (int i = 0; i < plotWidth; i++){
        for (int j = 0; j < plotHeight; j++){
            if(!crops[i][j].isCrop){
                //will load the empty image, for now doing nothing is okay
            }
            else{
                //crop images, each set of three is determined by growth time
                //which to use in those sets is determined by watered time
                
                int imgToUse = 0;
                if (crops[i][j].growthTimer > (crops[i][j].staticInfo.growthTime)){
                    imgToUse += 9;
                }
                else if (crops[i][j].growthTimer > (crops[i][j].staticInfo.growthTime * 2)/3){
                    imgToUse += 6;
                }
                else if (crops[i][j].growthTimer > (crops[i][j].staticInfo.growthTime)/3) {
                    imgToUse += 3;
                }
                //if it just started growing it would be at zero, no point in coding that

                if (crops[i][j].wateredTimer > (crops[i][j].staticInfo.waterTime)/2){
                    imgToUse += 2;
                }
                else if (!crops[i][j].isDead) {
                    imgToUse += 1;
                }

                drawImage(screenSlots, crops[i][j].staticInfo.cropImages[imgToUse], i+DISTANCE_FROM_SIDE_TO_CROPS, j);
                
            }
        }
    }
}

void drawTool(HWND screenSlots[16][10], HWND hwnd, HWND* mouseSlot, HBITMAP toolImages[], int toolInHand, int wateringCanCount, vector2 toolLocations[], POINT mouseLocation){

    for (int i = 1; i <= TOOL_TOTAL; i++){
        drawImage(screenSlots, toolImages[i], toolLocations[i-1].x, toolLocations[i-1].y);
        if (i == TOOL_WATERING_CAN && wateringCanCount == 0){
            drawImage(screenSlots, toolImages[TOOL_EMPTY_WATERING_CAN], toolLocations[i-1].x, toolLocations[i-1].y);
        }
    }

    
    //clears if none, also clears previous
    SendMessageW(*mouseSlot, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)toolImages[NONE_IN_HAND]);

    //draw image at mouse location
    //not using draw image because it follows mouse
    if (toolInHand != NONE_IN_HAND){
        *mouseSlot = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, mouseLocation.x, mouseLocation.y,0,0, hwnd, NULL, NULL, NULL);
        if (toolInHand == TOOL_WATERING_CAN && wateringCanCount == 0){
            SendMessageW(*mouseSlot, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)toolImages[TOOL_EMPTY_WATERING_CAN]);
        }
        else{
            SendMessageW(*mouseSlot, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)toolImages[toolInHand]);
        }
    }
}

void loadToolImages(HBITMAP toolImages[], vector2 toolLocations[]){
    //load in all files with tool images
    toolImages[0] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_1, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    toolImages[1] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_2, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    toolImages[2] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_3, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    toolImages[3] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_4, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    toolImages[4] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_5, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    toolImages[5] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_6, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    toolImages[6] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_7, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    toolImages[7] = (HBITMAP)LoadImageW(NULL, TOOL_IMAGE_PATH_8, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    //load locations on screen
    toolLocations[0].x = WATERING_CAN_X_POS;
    toolLocations[0].y = WATERING_CAN_Y_POS;
    toolLocations[1].x = SCYTHE_X_POS;
    toolLocations[1].y = SCYTHE_Y_POS;

    toolLocations[2].x = WHEAT_SEED_X_POS;
    toolLocations[2].y = WHEAT_SEED_Y_POS;
    toolLocations[3].x = WATERMELON_SEED_X_POS;
    toolLocations[3].y = WATERMELON_SEED_Y_POS;
    toolLocations[4].x = CACTUS_SEED_X_POS;
    toolLocations[4].y = CACTUS_SEED_Y_POS;
    toolLocations[5].x = CARROT_SEED_X_POS;
    toolLocations[5].y = CARROT_SEED_Y_POS;
}