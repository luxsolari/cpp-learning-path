cmake_minimum_required(VERSION 3.21) # CMake version check
project(CMakeSFMLProject LANGUAGES CXX) # Create project "CMakeSFMLProject" with C++ support
set(CMAKE_CXX_STANDARD 17) # enable C++17 standard

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux-specific code here
    message(STATUS "Building for Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

    set(SFML_INCLUDE_DIR "/home/luciano.laje/Libraries/SFML-2.5.1/include")
    set(SFML_LIBRARY_DIR "/home/luciano.laje/Libraries/SFML-2.5.1/lib")
    set(SFML_DIR "/home/luciano.laje/Libraries/SFML-2.5.1/lib/cmake/SFML")

    link_directories(SFML_LIBRARY_DIR)
    include_directories(SFML_INCLUDE_DIR)

    find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

    if(SFML_FOUND)
        message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
        message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
        message(STATUS "SFML_VERSION: ${SFML_VERSION}")
    endif()

    add_executable(CMakeSFMLProject src/main.cpp src/managers/StateManager.cpp src/managers/StateManager.h src/states/State.h src/states/MainMenuState.cpp src/states/MainMenuState.h src/managers/WindowManager.cpp src/managers/WindowManager.h src/constants/Globals.h src/managers/InputManager.cpp src/managers/InputManager.h src/states/OptionsMenuState.cpp src/states/OptionsMenuState.h src/managers/EventManager.h src/managers/EventManager.cpp src/enums/StateType.h )
    target_link_libraries (CMakeSFMLProject sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
    target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows-specific code here
    message(STATUS "Building for Windows")
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)

    add_executable(CMakeSFMLProject src/main.cpp src/managers/StateManager.cpp src/managers/StateManager.h src/states/State.h   src/managers/WindowManager.cpp src/managers/WindowManager.h src/constants/Globals.h     src/managers/EventManager.h src/managers/EventManager.cpp src/enums/StateType.h "src/Game.cpp" "src/Game.h" "src/states/StateIntro.h" "src/states/StateIntro.cpp")
    include_directories(${CMAKE_SOURCE_DIR}/src/constants)
    include_directories(${CMAKE_SOURCE_DIR}/src/enums)
    include_directories(${CMAKE_SOURCE_DIR}/src/managers)
    include_directories(${CMAKE_SOURCE_DIR}/src/states)

    target_link_libraries(CMakeSFMLProject sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
    target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        # Debug-specific code here
        message(STATUS "Using Debug configuration")
        add_definitions(-DDEBUG)
    else ()
        # Release-specific code here
        message(STATUS "Using Release configuration")
        add_definitions(-DRELEASE)
    endif ()

    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)

    set_target_properties(CMakeSFMLProject
        PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
                   LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS-specific code here
    message(STATUS "Building for MacOS")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x) # fetch SFML from GitHub and checkout the 2.6.x branch
    FetchContent_MakeAvailable(SFML) # make SFML available to the build system

    set(LIBPROC_SRC "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/libproc.h") # For MacOS
    set(CMAKE_INCLUDE_CURRENT_DIR ON) # For MOC to find headers
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wno-unused-parameter")
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        # Debug-specific code here
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
        message(STATUS "Using Debug configuration")
        add_definitions(-DDEBUG)
        add_executable(CMakeSFMLProject src/main.cpp src/managers/StateManager.cpp src/managers/StateManager.h src/states/State.h   src/managers/WindowManager.cpp src/managers/WindowManager.h src/constants/Globals.h     src/managers/EventManager.h src/managers/EventManager.cpp src/enums/StateType.h "src/Game.cpp" "src/Game.h")
        target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
        target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

    elseif(CMAKE_BUILD_TYPE MATCHES Release)
        # Release-specific code here
        message(STATUS "Using Release configuration")
        add_definitions(-DRELEASE)
        add_executable(CMakeSFMLProject MACOSX_BUNDLE src/main.cpp src/managers/StateManager.cpp src/managers/StateManager.h src/states/State.h   src/managers/WindowManager.cpp src/managers/WindowManager.h src/constants/Globals.h     src/managers/EventManager.h src/managers/EventManager.cpp src/enums/StateType.h "src/Game.cpp" "src/Game.h")
        set_target_properties(CMakeSFMLProject PROPERTIES
                MACOSX_BUNDLE_NAME "CMakeSFMLProject"
                MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/Info.plist.in")
        target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
        target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

        install(TARGETS CMakeSFMLProject
                CONFIGURATIONS Release
                DESTINATION Release/bin)
    endif()
else ()
    # Other operating systems
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter")
    #add_executable(CMakeSFMLProject src/main.cpp src/managers/StateManager.cpp src/managers/StateManager.h src/states/State.h src/states/MainMenuState.cpp src/states/MainMenuState.h src/managers/WindowManager.cpp src/managers/WindowManager.h src/constants/Globals.h src/managers/InputManager.cpp src/managers/InputManager.h src/states/OptionsMenuState.cpp src/states/OptionsMenuState.h)
endif ()
