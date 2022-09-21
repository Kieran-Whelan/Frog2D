include(FetchContent)
cmake_minimum_required(VERSION 3.20.0)

#toolchain file doesnt work properly
#set(CMAKE_TOOLCHAIN_FILE "G:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Frog2D)

add_executable(${PROJECT_NAME} 
        src/main.cpp 
        src/glad.c 
        src/core/ShaderProgram.cpp src/core/ShaderProgram.hpp 
        src/core/Sprite.cpp src/core/Sprite.hpp
        src/core/math/Transformation.cpp src/core/math/Transformation.hpp
        src/core/math/VAO.cpp src/core/math/VAO.hpp
        src/core/math/VBO.cpp src/core/math/VBO.hpp
	src/core/Window.cpp src/core/Window.hpp
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)

FetchContent_MakeAvailable(glfw)

#set your own vcpkg path
set(CMAKE_PREFIX_PATH "G:/dev/vcpkg/installed/x64-windows/share")
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad glm::glm glfw)
