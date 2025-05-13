cmake_minimum_required(VERSION 3.10)
project(KOD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: Make static linking easier (especially on Windows)
option(SFML_STATIC_LIBRARIES "Use SFML as static libraries" ON)

# Source files
set(SOURCES
    main.cpp
    Button.cpp
    MainMenu.cpp
    CesticeSimulacija.cpp
    Cestica.cpp
    State.cpp
)

# Include headers from current directory
include_directories(${CMAKE_SOURCE_DIR})

# Find SFML (adjust if not system-installed)
find_package(SFML 3.0 COMPONENTS graphics window system REQUIRED)

# Build the executable
add_executable(KOD ${SOURCES})
target_link_libraries(KOD sfml-graphics sfml-window sfml-system)

# If static linking, define macro and link extra Windows libs
if (SFML_STATIC_LIBRARIES)
    target_compile_definitions(KOD PRIVATE SFML_STATIC)
    if (WIN32)
        target_link_libraries(KOD
            opengl32
            gdi32
            winmm
            ws2_32
            freetype
            jpeg
            user32
        )
    endif()
endif()
