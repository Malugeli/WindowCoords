#include <print>
#include <windows.h>
#include "C:\Users\aluge\Desktop\Mahers Headerfiles\unique_hotkey.h"
#include <cstdlib>
#include <dwmapi.h>

int main()
{
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HWND game = FindWindowW(NULL, L"masterduel");
    if(!game){
        std::cout << "Game not found";
        return 1;
    }
    RECT rect{};
    POINT p{};
    MSG msg;
    unique_hotkey a(NULL, 1, 0, VK_NUMPAD1);

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            std::print("\033[2J\033[H");
            GetCursorPos(&p);
            ScreenToClient(game, &p);
            GetClientRect(game, &rect);
            double length = rect.right - rect.left; //wir nutzen Client, Top und Left sind 0 aber zur Übersicht behalt ich das so
            double height = rect.bottom - rect.top;
            double faktorx = p.x / length; 
            double faktory = p.y / height;
            std::println("X Faktor = {} \nY Faktor = {}\n", faktorx, faktory);
            p.x = rect.right * faktorx; 
            p.y = rect.bottom * faktory;
            ClientToScreen(game, &p); //das hat die ganze Zeit gefehlt..
            std::println("X Koordinaten in Real: {} || Y Koordinaten in Real: {}", p.x, p.y);
            SetCursorPos(p.x, p.y);          
        }
    }
}