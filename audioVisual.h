/** audioVisual.h
 */

#ifndef AUDIOVISUAL_H
#define AUDIOVISUAL_H

#include <Windows.h>

#include "crops.h"

#define SLOT_SIZE_VERTICAL 10
#define SLOT_SIZE_HORIZONTAL 10
#define IMAGE_SIZE_PIXELS 32

#define DISTANCE_FROM_SIDE_TO_CROPS 6

#define WATERING_CAN_X_POS 1
#define WATERING_CAN_Y_POS 4
#define SCYTHE_X_POS 3
#define SCYTHE_Y_POS 4

#define WHEAT_SEED_X_POS 1
#define WHEAT_SEED_Y_POS 6
#define WATERMELON_SEED_X_POS 3
#define WATERMELON_SEED_Y_POS 6
#define CACTUS_SEED_X_POS 1
#define CACTUS_SEED_Y_POS 8
#define CARROT_SEED_X_POS 3
#define CARROT_SEED_Y_POS 8

#define TIME_BETWEEN_TICKS 50

//defining struct to hold positional values
typedef struct vector2Struct{
    int x;
    int y;
} vector2;


void InitializeControls(HWND hWnd ,HWND screenSlots[16][10]);

//funct 1
void drawImage(HWND screenSlots[16][10] ,HBITMAP image, int x, int y);

//funct 6
void drawCrops(HWND screenSlots[16][10], cropTile** crops, int plotWidth, int plotHeight);

//funct 7
void drawTool(HWND screenSlots[16][10], HWND hwnd, HWND* mouseSlot, HBITMAP toolImages[], int toolInHand, int wateringCanCount, vector2 toolLocations[], POINT mouseLocation);

void loadToolImages(HBITMAP toolImages[], vector2 toolLocations[]);

#endif // AUDIOVISUAL_H