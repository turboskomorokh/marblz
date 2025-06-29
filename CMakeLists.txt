cmake_minimum_required(VERSION 3.31)
project(marbl)

set(CMAKE_CXX_STANDARD 23)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(PNG REQUIRED)
find_package(spdlog REQUIRED)

add_executable(marbl main.cpp
        game/Window.cpp
        game/Events.cpp
        game/gfx/Shader.cpp
        game/gfx/Texture.cpp
        game/Camera.cpp
        game/gfx/Geometry.cpp
)

add_custom_command(TARGET marbl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:marbl>/res
)

target_link_libraries(marbl PRIVATE OpenGL::GL glfw GLEW::glew glm::glm PNG::PNG spdlog::spdlog)