#include <stdio.h>

#include <Windows.h>

#include "audioVisual.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
const int ID_TIMER = 1;
int animate = 1;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    //windows api code from example
    PWSTR lpCmdLine, int nCmdShow) {
    MSG  msg;
    WNDCLASSW wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Lines";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"C Crop Simulator",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                200, // left  
                100, // upper corner
                IMAGE_SIZE_PIXELS * SLOT_SIZE_HORIZONTAL, // width
                IMAGE_SIZE_PIXELS * SLOT_SIZE_VERTICAL, // height
                NULL,// no menu 
                NULL,//
                hInstance, NULL);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //my code

    //

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {
    switch(msg) {  
        case WM_CREATE:          // window is created
            MessageBox(hwnd, "[esc] key will pause animation\nclick OK to begin", 
"CS210 rocks!", MB_OK);
            int ret = SetTimer(hwnd, ID_TIMER, 10, NULL);
            if(ret == 0){
                MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | 
MB_ICONEXCLAMATION);
            }
            break;
        case WM_DESTROY:         // user pressed X button to close window
            PostQuitMessage(0);
            KillTimer(hwnd, ID_TIMER);
            return 0;
  
        case WM_TIMER:
            updateCrops();        
           break;
        case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            animate = !animate;
        } else if(isalnum(wParam)) {
           char msg[100];
           sprintf(msg, "you pressed a: %c", wParam);
           MessageBox(hwnd, msg, "Info", MB_OK);
        }
        break;
    } // end of switch
    
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}