cmake_minimum_required(VERSION 3.30)
project(Monkey_Typer)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG         11.0.2
)

FetchContent_MakeAvailable(fmt)

add_executable(Monkey_Typer main.cpp
        GameState.h
        Menu.cpp
        Menu.h
        QuitMenu.cpp
        QuitMenu.h
        PlayState.cpp
        PlayState.h
        Difficulty.h
        PauseState.h
        SettingsMenu.cpp
        SettingsMenu.h
        PauseMenu.cpp
        PauseMenu.h
        GameOverMenu.cpp
        GameOverMenu.h
        StatsObject.cpp
        StatsObject.h
        TextBox.cpp
        TextBox.h
)

target_link_libraries(Monkey_Typer
        PRIVATE SFML::Graphics
        PRIVATE SFML::Audio
        fmt)
