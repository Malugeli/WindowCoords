# Coordinates

A tiny Windows tool that prints the **relative position of your mouse cursor** inside any window — game, app, whatever — as normalized coordinates (0.0–1.0). You tell it which window to track by name.

## The problem it solves

If you write macros or automation scripts, you need click coordinates. Absolute pixel coordinates break as soon as the window is moved or resized, or a different resolution is used. Relative coordinates don't — `x = 0.5, y = 0.5` is always the center of the target window, no matter its size or position.

## How it works

1. The tool looks up a window by its title and registers **Numpad 1** as a global hotkey.
2. Hover your mouse anywhere over that window and press **Numpad 1**.
3. The tool converts the cursor position into the window's client coordinates and divides them by the client area size, printing the resulting `X`/`Y` factors (0.0–1.0) to the console.

Example output:

```
X factor = 0.421875
Y factor = 0.631579
```

Use these factors in your scripts and map them back to pixels with `width * factor` / `height * factor` at runtime — window size and position become irrelevant.

## Building

Requirements: Windows, CMake ≥ 3.30, [Ninja](https://ninja-build.org/), clang and the MSVC toolchain (the Visual Studio Build Tools provide both). No third-party dependencies.

> **Note:** Sorry, but the Windows SDK headers only really work properly with MSVC-compatible compilers. The presets therefore use clang targeting the MSVC ABI. Building with other compilers (MSVC itself, MinGW g++, ...) may work — the CMakeLists keeps their flags ready — but it's not supported.

```bash
cmake --preset windows-release
cmake --build --preset windows-release
```

The binary ends up in `build/Release/Coordinates.exe` (a `windows-debug` preset is also available).

## Usage

1. Set the title of your target window in `main.cpp` (`L"REPLACE WINDOW NAME HERE"` — the text shown in its title bar) and build.
2. Open the target window and run the tool (it exits with an error if the window isn't found).
3. Press **Numpad 1** to read out the cursor position.

## Notes

- Coordinates are calculated against the window's client area, so window borders and the title bar don't skew the result.
- The process is per-monitor DPI aware (v2), so results stay correct on scaled displays.
