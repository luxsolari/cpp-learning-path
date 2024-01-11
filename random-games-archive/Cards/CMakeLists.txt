cmake_minimum_required(VERSION 3.10)
project(Cards CXX ASM)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 11)

# Define ANSI escape codes for text ConsoleColor
if(CMAKE_HOST_WIN32)
    # On Windows, use the WinAPI for console ConsoleColor
    set(ANSI_RESET "")
    set(ANSI_RED "")
    set(ANSI_GREEN "")
    set(ANSI_YELLOW "")
    set(ANSI_BLUE "")
    set(ANSI_MAGENTA "")
    set(ANSI_CYAN "")
    set(ANSI_WHITE "")
else()
    # On non-Windows systems, use ANSI escape codes
    string(ASCII 27 Esc)
    set(ANSI_RESET "${Esc}[0m")
    set(ANSI_RED "${Esc}[1;31m")       # Red
    set(ANSI_GREEN "${Esc}[1;32m")     # Green
    set(ANSI_YELLOW "${Esc}[1;33m")    # Yellow
    set(ANSI_BLUE "${Esc}[1;34m")      # Blue
    set(ANSI_MAGENTA "${Esc}[1;35m")   # Magenta
    set(ANSI_CYAN "${Esc}[1;36m")      # Cyan
    set(ANSI_WHITE "${Esc}[1;37m")     # White
endif()

# Add your source files
set(SOURCE_FILES src/Program.cpp
        src/GameWin.cpp
        src/GameWin.h
        src/GameUnix.cpp
        src/GameUnix.h
        src/enums/Suits.h)

# Define your target
add_executable(Cards ${SOURCE_FILES})

# Set the output path for the assembly listing
set(OUTPUT_PATH ${CMAKE_BINARY_DIR}/assembly_output)
set(ASSEMBLY_LISTING_FILE ${OUTPUT_PATH}/main.asm)

# Ensure that the directory for the assembly listing map file exists
file(MAKE_DIRECTORY ${OUTPUT_PATH})

# Print compiler information
message("${ANSI_RED}Compiler is: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} ${CMAKE_CXX_COMPILER_VERSION}${ANSI_RESET}")

# Enable assembly output for MSVC
if(MSVC)
    message("MSVC-specific configurations...")
    # Set the output path for the assembly listing
    set_target_properties(Cards PROPERTIES
            COMPILE_OPTIONS "/FAs"        # Generate assembly listing
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")  # Set working directory for debugging
    # Pass a preprocessor macro to the compiler
    target_compile_definitions(Cards PRIVATE YOUR_MACRO=42)

elseif (CMAKE_COMPILER_IS_GNUCXX)
    message("GCC or Clang-specific configurations...")

    SET(CMAKE_ASM_FLAGS "${CFLAGS} -x assembler-with-cpp")
    # Set the output path for the assembly listing
    set_target_properties(Cards PROPERTIES
            COMPILE_OPTIONS "-Wa,-adhln=${ASSEMBLY_LISTING_FILE}"        # Generate assembly listing
            LINK_FLAGS "-Wl,-Map=${OUTPUT_PATH}/main.map")               # Generate a map file

    # Pass a preprocessor macro to the compiler
    target_compile_definitions(Cards PRIVATE YOUR_MACRO=42)

elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Clang-specific configurations...")

    SET(CMAKE_ASM_FLAGS "${CFLAGS} -x assembler-with-cpp")
    # Set the output path for the assembly listing and map file
    set_target_properties(Cards PROPERTIES
            COMPILE_OPTIONS "-save-temps=intel"  # Generate assembly listing in Intel syntax
            )

    # Pass a preprocessor macro to the compiler
    target_compile_definitions(Cards PRIVATE YOUR_MACRO=42)
else()
    # Other compiler configurations
    message("Other compiler configurations...")

endif()
