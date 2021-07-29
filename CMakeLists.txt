# CMake entry point.
# Note that this CMakeLists.txt in fully independent from the one in the parent directory
# (since that's the goal of this tutorial !)

# For an introduction to CMake, see
# http://www.cmake.org/cmake/help/cmake_tutorial.html (at least steps 1 and 2)

cmake_minimum_required (VERSION 2.6)
project (OPENGL_VS)

find_package(OpenGL REQUIRED)


# Ask the user to give the paths to GLFW, GLEW and GLM.
# On Linux this can be found automatically with pkg-config; 
# see http://stackoverflow.com/questions/6889264/cmake-flags-for-opengl-using-glew-and-glfw, for instance.
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE MY_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

add_executable(${PROJECT_NAME}
	
	${MY_SOURCE_FILES}
)

add_library(GLAD ${PROJECT_SOURCE_DIR}/tools/glad.c)

add_library(STB_IMAGE ${PROJECT_SOURCE_DIR}/tools/stb_imge.cpp)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/glfw)
target_link_libraries(${PROJECT_NAME} "glfw" ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/dependencies/glfw/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

link_libraries(${PROJECT_SOURCE_DIR}/lib/libassimp.dylib)
link_libraries(${PROJECT_SOURCE_DIR}/lib)




set(LIBS STB_IMAGE GLAD)

include_directories(
	${INCLUDE_PATH}
)

target_link_libraries(${PROJECT_NAME}
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
    ${LIBS}
)





# HOW-TO. You can safely remove anything below.  

# test if linux, mac or windows : 

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("You're on Mac OS !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("You're on Windows !")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Yes this is weird but you have to repeat the "if" here.

