cmake_minimum_required(VERSION 3.22)
project(world C)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_C_STANDARD 23)

add_subdirectory(src/lib/glfw)

add_executable(world main.c src/lib/glad/glad.c src/lib/glad/glad.h src/lib/glad/khrplatform.h
        src/app.h
        src/gl.h
        src/err.h
        src/app.c
        src/gl.c
        src/arr.h
        src/arr.c
        src/lib/simplex/FastNoiseLite.h
        src/lib/simplex/FastNoiseLite.c
        src/map.h
        src/map.c
        src/world.h
        src/world.c
)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(world PRIVATE glfw assimp::assimp)
find_package(Stb REQUIRED)
target_include_directories(world PRIVATE ${Stb_INCLUDE_DIR})