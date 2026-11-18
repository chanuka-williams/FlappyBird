include(FetchContent)

# Downloads raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

# Downloads spdlog
set(SPDLOG_HEADER_ONLY ON CACHE BOOL "" FORCE)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.16.0  # Use a specific version for reproducibility
)
FetchContent_MakeAvailable(spdlog)


add_library(engine STATIC)

file(GLOB_RECURSE ENGINE_SOURCES
        CONFIGURE_DEPENDS
        src/*.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
        CONFIGURE_DEPENDS
        "include/engine/*.h"
)

target_sources(engine
        PRIVATE
        ${ENGINE_SOURCES}
        PUBLIC
        ${ENGINE_HEADERS}
)

target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine
        PUBLIC
        raylib
        spdlog::spdlog_header_only
)

if (WIN32)
    target_compile_options(engine PUBLIC
            $<$<CXX_COMPILER_ID:MSVC>:/FI$<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/include/engine/Platform.h>>
            $<$<CXX_COMPILER_ID:GNU,Clang>:-include ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/Platform.h>
    )
endif ()