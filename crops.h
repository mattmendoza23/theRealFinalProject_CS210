/** crops.h
 */

#ifndef CROPS_H
#define CROPS_H

#include <Windows.h>
#include <stdbool.h>
#include <time.h>

#define TILES_TO_TOP 10

#define SEED_TYPE_COUNT 4

//tool in hand, allows info to pass about what player is holding
#define NONE_IN_HAND 0
#define TOOL_WATERING_CAN 1
#define TOOL_SCYTHE 2
#define TOOL_WHEAT_SEED 3
#define TOOL_WATERMELON_SEED 4
#define TOOL_CACTUS_SEED 5
#define TOOL_CARROT_SEED 6
#define TOOL_EMPTY_WATERING_CAN 7

#define TOOL_TOTAL 6

#define TOOL_IMAGE_PATH_1 L"images\\testImages\\empty.bmp"
#define TOOL_IMAGE_PATH_2 L"images\\testImages\\test13.bmp"
#define TOOL_IMAGE_PATH_3 L"images\\testImages\\test14.bmp"
#define TOOL_IMAGE_PATH_4 L"images\\testImages\\test15.bmp"
#define TOOL_IMAGE_PATH_5 L"images\\testImages\\test16.bmp"
#define TOOL_IMAGE_PATH_6 L"images\\testImages\\test17.bmp"
#define TOOL_IMAGE_PATH_7 L"images\\testImages\\test18.bmp"
#define TOOL_IMAGE_PATH_8 L"images\\testImages\\test19.bmp"

//----------------
//crop struct info
//----------------

//Wheat info

#define WHEAT_NAME "Wheat"
#define WHEAT_SELL_PRICE 30
#define WHEAT_GROWTH_TIME 30
#define WHEAT_WATER_TIME 10
//define image paths here

//test crop
#define TEST_CROP_NAME "Blueberry"
#define TEST_CROP_SELL_PRICE 35
#define TEST_CROP_GROWTH_TIME 20000
#define TEST_CROP_WATER_TIME 8000
#define TEST_CROP_IMAGE_PATH_1 L"images\\testImages\\test1.bmp"
#define TEST_CROP_IMAGE_PATH_2 L"images\\testImages\\test2.bmp"
#define TEST_CROP_IMAGE_PATH_3 L"images\\testImages\\test3.bmp"
#define TEST_CROP_IMAGE_PATH_4 L"images\\testImages\\test4.bmp"
#define TEST_CROP_IMAGE_PATH_5 L"images\\testImages\\test5.bmp"
#define TEST_CROP_IMAGE_PATH_6 L"images\\testImages\\test6.bmp"
#define TEST_CROP_IMAGE_PATH_7 L"images\\testImages\\test7.bmp"
#define TEST_CROP_IMAGE_PATH_8 L"images\\testImages\\test8.bmp"
#define TEST_CROP_IMAGE_PATH_9 L"images\\testImages\\test9.bmp"
#define TEST_CROP_IMAGE_PATH_10 L"images\\testImages\\test10.bmp"
#define TEST_CROP_IMAGE_PATH_11 L"images\\testImages\\test11.bmp"
#define TEST_CROP_IMAGE_PATH_12 L"images\\testImages\\test12.bmp"

//finish structs later
#define WATERMELON_NAME "Watermelon"
#define CACTUS_NAME "Cactus"
#define CARROT_NAME "Carrot"


//struct inside of a struct
//this is static info that crops under the same name share
typedef struct cropInfoStruct{
    char name[30];
    int sellPrice;
    int growthTime;
    int waterTime;
    HBITMAP cropImages[12];
} cropInfo;

//tile struct
//this is a dynamic struct, gets adjusted by the update crops function
typedef struct cropTileStruct{
    cropInfo staticInfo;
    int growthTimer;
    int wateredTimer;
    bool isDead;
    bool isGrown;
    bool isCrop;
} cropTile;

//funct 1
void updateCrops(cropTile** listOfCrops, int plotWidth, int plotHeight, time_t* cropTime);

cropInfo loadTestCrop(HWND hwnd);

void loadCropImages(HBITMAP toEdit[], char name[],HWND hwnd);

void playerUpdateCrops(cropTile** listOfCrops, int plotWidth, int plotHeight, POINT mousePosition);

#endif // CROPS_H