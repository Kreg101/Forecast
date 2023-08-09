cmake_minimum_required(VERSION 3.23)
project(labwork10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(labwork10 main.cpp Day/day.cpp Day/day.h City/city.cpp City/city.h Forecast/Forecast.h Forecast/Forecast.cpp)

include(FetchContent)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v3.0.0
        )

set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui GIT_TAG v4.0.0)

FetchContent_MakeAvailable(ftxui)

target_link_libraries(labwork10 PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 9190225da3bb732d59af020c45927f81fb37e5f4) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(labwork10 PRIVATE cpr::cpr)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(labwork10 PRIVATE nlohmann_json::nlohmann_json)


