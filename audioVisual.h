#include <Windows.h>

#define SLOT_SIZE_VERTICAL 10
#define SLOT_SIZE_HORIZONTAL 10
#define IMAGE_SIZE_PIXELS 8

void InitializeControls(HWND hWnd ,HWND** emptySlots);

//funct 1
void drawImage(HBITMAP image, int x, int y);