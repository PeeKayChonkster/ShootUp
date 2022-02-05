cmake_minimum_required(VERSION 3.18)
project(ShootUp VERSION 1.0 LANGUAGES C CXX)

set(BUILD_SHARED_LIBS NO)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}bin)


set(SHOOTUP_SRC
    main.cpp transform2D.cpp node2D.cpp
    )

list(TRANSFORM SHOOTUP_SRC PREPEND "src/")

add_subdirectory("external/raylib")

add_executable(${PROJECT_NAME} ${SHOOTUP_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

target_include_directories(${PROJECT_NAME} PUBLIC "external/raylib-cpp/include")