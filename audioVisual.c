#include <Windows.h>

#include "audioVisual.h"

void InitializeControls(HWND hWnd ,HWND** screenSlots){
    for (int i = 0; i < SLOT_SIZE_VERTICAL; i++){
        for(int j = 0; j < SLOT_SIZE_HORIZONTAL; j++){
            screenSlots[i][j] = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, i*IMAGE_SIZE_PIXELS, j*IMAGE_SIZE_PIXELS,0,0, hWnd, NULL, NULL, NULL);
            HBITMAP emptyImage = (HBITMAP)LoadImageW(NULL, L"images\\empty.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
            SendMessageW(screenSlots[i][j], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)emptyImage);
        }
    }
}

//funct 2
void drawImage(HWND** screenSlots ,HBITMAP image, int x, int y){
    //function just makes loading an image less ambiguous for future coding
    SendMessageW(screenSlots[x][y], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
}