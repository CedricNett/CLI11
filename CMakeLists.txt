cmake_minimum_required(VERSION 3.12)

# Add Project Attributes
project(  lagerhalterungsystem
          LANGUAGES CXX
          DESCRIPTION "Shows the integration of CLI11"
          HOMEPAGE_URL "http://vorlesung.nabla-b.engineering"
)

include(FetchContent)

# Add CLI11 Library to Project
find_package(cli11 QUIET)
if(NOT cli11_FOUND)
    FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11
        GIT_TAG main
    )
    FetchContent_MakeAvailable(cli11)
endif()

# Add nlohmann.json #https://json.nlohmann.me/integration/cmake/#supporting-both
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG master
)
    FetchContent_MakeAvailable(nlohmann_json)
endif()

add_executable( ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/lagerhalterungsystem.cc" )

target_link_libraries( ${PROJECT_NAME} CLI11::CLI11 nlohmann_json::nlohmann_json)