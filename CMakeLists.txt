cmake_minimum_required(VERSION 3.30)

project(Coordinates CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ohne das haengt CMake bei C++23 an jeden g++-Aufruf -fmodules-ts,
# -fmodule-mapper und -fdeps-format an, um nach Modulen zu scannen.
# Wir nutzen keine Module: kostet nur Buildzeit und verwirrt clangd.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# ---------------------------------------------------------------------------
# coordinates_warnings: kompiliert selbst nichts, ist nur ein Bündel
# Compilerflags mit Namen. Wird an jedes Target gelinkt, das die Flags
# haben soll — damit steht der if(MSVC)-Block genau einmal im File.
# ---------------------------------------------------------------------------
add_library(coordinates_warnings INTERFACE)

if(MSVC)
    target_compile_options(coordinates_warnings INTERFACE
        /W4          # Höchstes normales Warnlevel
        /WX          # Behandelt Warnungen als Fehler
        /permissive- # Erzwingt strikte C++ Standardkonformität
    )
else()
    target_compile_options(coordinates_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow # Warnt, wenn eine lokale Variable eine äußere überdeckt
        -Werror  # Macht jede Warnung zu einem echten Fehler
    )
endif()

# ---------------------------------------------------------------------------
# Coordinates: das eigentliche Programm. Nur Windows-API, keine
# Third-Party-Abhängigkeiten.
# ---------------------------------------------------------------------------
add_executable(Coordinates main.cpp)

target_link_libraries(Coordinates PRIVATE coordinates_warnings)

# std::print/std::println liegen bei GCC 14/15 in libstdc++exp, nicht in
# libstdc++, weil ihr ABI noch nicht stabil ist. Ohne das fehlen
# __open_terminal/__write_to_terminal.
target_link_libraries(Coordinates PRIVATE $<$<CXX_COMPILER_ID:GNU>:stdc++exp>)

# MinGW linkt libstdc++/libgcc/libwinpthread standardmaessig als DLL. Statisch
# gelinkt haengt die Exe an gar keiner davon und laeuft auf jedem Windows-Rechner
# ohne DLL-Hell. Windows-MinGW-Workaround: auf Linux waere pauschales -static
# unnoetig und kann fehlende statische Systembibliotheken verursachen.
if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(Coordinates PRIVATE -static)
endif()
