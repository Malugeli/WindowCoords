#include <print>
#include <windows.h>
#include "unique_hotkey.h"

int main()
{
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    HWND window = FindWindowW(NULL, L"REPLACE WINDOW NAME HERE"); //Replace Content of "" with your Window Name
    if (!window) {
        std::println(stderr, "Window not found - is the window running?");
        return 1;
    }

    RECT rect{};
    POINT p{};
    MSG msg;
    unique_hotkey hotkey(NULL, 1, 0, VK_NUMPAD1);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_HOTKEY) {

            GetCursorPos(&p);
            ScreenToClient(window, &p);

            GetClientRect(window, &rect);

            double factor_x = static_cast<double>(p.x) / rect.right;
            double factor_y = static_cast<double>(p.y) / rect.bottom;

            std::println("X factor = {}\nY factor = {}\n", factor_x, factor_y);
        }
    }
}
