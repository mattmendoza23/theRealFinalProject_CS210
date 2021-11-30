
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <time.h>

#include "crops.h"
#include "audioVisual.h"
#include "fileIO.h"

/*
typedef struct cropTileStruct{
    cropInfo staticInfo;
    double growthTimer;
    double wateredTimer;
    bool isDead;
    bool isGrown;
} cropTile;
*/
#define TEST_GROWTH_TIMER 15000
#define TEST_WATERED_TIMER 10000
#define TEST_IS_DEAD false
#define TEST_IS_GROWN false

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define ID_TIMER_TICK 1

cropInfo blueberry;
HWND screenSlots[16][10];

HWND mouseSlot;

char fileName[] = "testSave.bin";
cropTile** crops;
int plotWidth = 4;
int plotHeight = 5;
int playerCash = 100;

HBITMAP toolImages[8];
vector2 toolLocations[6];

time_t cropTime;

//HBITMAP testMap;
//HWND test;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow) {
    //windows api code from example
    MSG  msg;
    WNDCLASSW wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Farm";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"C Crop Simulator",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                200, // left  
                200, // upper corner
                IMAGE_SIZE_PIXELS * (SLOT_SIZE_HORIZONTAL + DISTANCE_FROM_SIDE_TO_CROPS) + 16, // width
                IMAGE_SIZE_PIXELS * SLOT_SIZE_VERTICAL + 40, // height
                NULL,// no menu 
                NULL,//
                hInstance, NULL);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {
    switch(msg) {  
        case WM_CREATE:          // window is created
            //initialization
            //need to see what message box does, might need it for testing
            MessageBox(hwnd, "test file\nclick OK to begin", 
"message box", MB_OK);
            //put code to be run in the beginning here

            //CreateWindowW(L"static",L"Enter Text Here :", WS_VISIBLE | WS_CHILD, 200, 100, 100, 50, hwnd, NULL, NULL, NULL);
            //testMap = (HBITMAP)LoadImageW(NULL, L"images\\testImages\\black.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
            //test = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60,100,100, hwnd, NULL, NULL, NULL);
            //SendMessageW(test, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) testMap);


            //testing draw image
            //---------------------
            InitializeControls(hwnd, screenSlots);

            HBITMAP testImage = (HBITMAP)LoadImageW(NULL, L"images\\testImages\\test20.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
            drawImage(screenSlots,testImage, 5,5);
            drawImage(screenSlots,testImage, 0,0);
            drawImage(screenSlots,testImage, 15,9);


            //testing save and open file
            //----------------------------
            crops = (cropTile**)malloc(sizeof(cropTile*)*plotWidth);
            for(int i = 0; i < plotWidth; i++){
                crops[i] = (cropTile*)malloc(sizeof(cropTile)*plotHeight);
            }

            saveFile(fileName, crops, &plotWidth, &plotHeight, &playerCash);

            //making new variables to place stuff into
            char testFileName[] = "testSave.bin";
            cropTile** testCrops;
            int testPlotWidth = 0;
            int testPlotHeight = 0;
            int testPlayerCash = 0;
            openFile(testFileName, testCrops, &testPlotWidth, &testPlotHeight, &testPlayerCash);


            //if values match, functions work
            if(testPlotWidth == plotWidth && testPlotHeight == plotHeight && testPlayerCash == playerCash){
                MessageBox(hwnd, "save and open file work! Good job!\nclick OK to move on", 
"message box", MB_OK);
            }
            else{
                MessageBox(hwnd, "save and open file don't work! :(\nclick OK to move on", 
"message box", MB_OK);
            }

            //initializing stuff for crop test
            blueberry = loadTestCrop(hwnd);
            for(int i = 0; i < plotWidth; i++){
                for(int j = 0; j < plotHeight; j++){
                    crops[i][j].isCrop = false;
                }
            }
            crops[0][1].staticInfo = blueberry;
            crops[0][1].growthTimer = TEST_GROWTH_TIMER;
            crops[0][1].wateredTimer = TEST_WATERED_TIMER;
            crops[0][1].isDead = TEST_IS_DEAD;
            crops[0][1].isGrown = TEST_IS_GROWN;
            crops[0][1].isCrop = true;
            crops[0][3].staticInfo = blueberry;
            crops[0][3].growthTimer = TEST_GROWTH_TIMER;
            crops[0][3].wateredTimer = TEST_WATERED_TIMER;
            crops[0][3].isDead = TEST_IS_DEAD;
            crops[0][3].isGrown = TEST_IS_GROWN;
            crops[0][3].isCrop = true;

            cropTime = time(0);
            drawCrops(screenSlots, crops, plotWidth, plotHeight);

            //initilization stuff for draw tools
            loadToolImages(toolImages, toolLocations);
            
            POINT p2;
            if (GetCursorPos(&p2)){
                drawTool(screenSlots, hwnd, &mouseSlot, toolImages, 0, 1, toolLocations, p2);
            }

            //dont put code past this for WM_CREATE, doesnt work
            int ret = SetTimer(hwnd, ID_TIMER_TICK, 50, NULL);
            if(ret == 0){
                MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | 
MB_ICONEXCLAMATION);
            }
            break;
        case WM_DESTROY:         // user pressed X button to close window
            PostQuitMessage(0);
            KillTimer(hwnd, ID_TIMER_TICK);
            //free mallocs here

            return 0;
  
        case WM_TIMER:
            //could use timer instead of delta time function i wrote, needs testing
            //draw crops maskes draw image test, but this really only works if draw image does
            switch (wParam){
                case ID_TIMER_TICK:
                
                    updateCrops(crops, plotWidth, plotHeight, &cropTime);
                    drawCrops(screenSlots, crops, plotWidth, plotHeight);

                    POINT p;
                    if (GetCursorPos(&p)){
                        if (ScreenToClient(hwnd, &p)){
                            drawTool(screenSlots, hwnd, &mouseSlot, toolImages, 1, 1, toolLocations, p);
                        }
                    }
                    break;
            }
           break;
        case WM_LBUTTONDOWN:
            //stuff that happens based on mouse click goes here
            
            POINT p3;
            if (GetCursorPos(&p3)){
                if (ScreenToClient(hwnd, &p3)){
                    playerUpdateCrops(crops, plotWidth, plotHeight, p3);
                }
            }

            break;
    } // end of switch
    
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
