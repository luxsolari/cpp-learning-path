cmake_minimum_required(VERSION 3.10)
project(Cards)

# Define ANSI escape codes for text color
if(CMAKE_HOST_WIN32)
    # On Windows, use the WinAPI for console color
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
    set(ANSI_RESET "\033[0m")
    set(ANSI_RED "\033[1;31m")
    set(ANSI_GREEN "\033[1;32m")
    set(ANSI_YELLOW "\033[1;33m")
    set(ANSI_BLUE "\033[1;34m")
    set(ANSI_MAGENTA "\033[1;35m")
    set(ANSI_CYAN "\033[1;36m")
    set(ANSI_WHITE "\033[1;37m")
endif()

# Add your source files
set(SOURCE_FILES main.cpp)

# Define your target
add_executable(Cards ${SOURCE_FILES})

# Set the output path for the assembly listing
set(OUTPUT_PATH ${CMAKE_BINARY_DIR}/assembly_output)
set(ASSEMBLY_LISTING_FILE main.asm)
message("${ANSI_RED}Compiler is: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} ${CMAKE_CXX_COMPILER_VERSION}")
# Enable assembly output for MSVC
if(MSVC)
    message("MSVC-specific configurations...")
    set_target_properties(Cards PROPERTIES
            COMPILE_OPTIONS "/FAs"        # Generate assembly listing
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")  # Set working directory for debugging
    # Pass a preprocessor macro to the compiler
    target_compile_definitions(Cards PRIVATE YOUR_MACRO=42)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    message("GCC-specific configurations...")
    # Evil black magic for GCC compilers (usually *nixes)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Clang-specific configurations
    message("Clang-specific configurations...")
else()
    # Other compiler configurations
    message("Other compiler configurations...")
endif()