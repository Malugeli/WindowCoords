#include <iostream>
#include <windows.h>
#include "C:\Users\aluge\Desktop\Mahers Headerfiles\unique_hotkey.h"
#include <cstdlib>
#include <dwmapi.h>

int main()
{
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HWND game = FindWindowW(NULL, L"masterduel");
    RECT rect{};
    POINT p{};
    MSG msg;
    unique_hotkey a(NULL, 1, 0, VK_NUMPAD1);
    // Versuche, die DWM-Rahmen zu bekommen (Visuell korrekt)

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            std::system("cls");
            HRESULT hr = DwmGetWindowAttribute(game, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(rect));
            GetCursorPos(&p);
            ScreenToClient(game, &p);
            double length = rect.right - rect.left;
            double height = rect.bottom - rect.top;
            std::cout << "Nimm x mal: " << p.x / length << '\n';
            std::cout << "Nimm y mal: " << p.y / height << '\n' << '\n';
            std::cout << "Pixel x: " << p.x << "||" << "Pixel y: " << p.y << '\n' << '\n';
            std::cout << "Real x = " << rect.right * (p.x / length) << '\n';
            std::cout << "rect.right = " << rect.right << " rect.left = " << rect.left << '\n' << "Length = " << rect.right - rect.left << '\n';
        }
    }
}