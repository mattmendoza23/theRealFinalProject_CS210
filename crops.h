#include <Windows.h>
#include <stdbool.h>
#include <time.h>

#define TILES_TO_TOP 10

#define SEED_TYPE_COUNT 4

//----------------
//crop struct info
//----------------

//Wheat info

#define WHEAT_NAME "Wheat"
#define WHEAT_SELL_PRICE 30
#define WHEAT_GROWTH_TIME 30
#define WHEAT_WATER_TIME 10
//define image paths here

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
    double growthTimer;
    double wateredTimer;
    bool isDead;
    bool isGrown;
} cropTile;

//funct 1
void updateCrops(cropTile** listOfCrops, int cropTotal, time_t* cropTime);

void loadCropImages(cropInfo* infoToEdit);

double deltaTime(time_t previousTime);