# CMakeList.txt : CMake project for Rocket Launch Simulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

Set(EXEC_NAME
	"Rocket_Launch_Simulator")
project (${EXEC_NAME})

include_directories(
	"Dependencies/GLEW/include/"
	"Dependencies/stbi_image/"
	"Dependencies/GLM/"
	"src/Core/"
	"src/Input/"
	"src/Math/"
	"src/Rendering/"
	"src/Viewing/"
	"assets/"
)

Set(SOURCE_FILES 
	"Rocket Launch Simulator.h"
	"Rocket Launch Simulator.cpp"
	"Dependencies/GLEW/include/GL/glew.h"
	"Dependencies/GLEW/src/glew.c" 
	"Dependencies/stbi_image/stbi_image.h"

	
	
	"src/Viewing/Window.h"
	"src/Viewing/Window.cpp"
	"src/Viewing/Camera.h"
	"src/Viewing/Camera.cpp"
	"src/Rendering/FrameBuffer.h"
	"src/Rendering/FrameBuffer.cpp"
	"src/Rendering/Mesh.h"
	"src/Rendering/Mesh.cpp"
	"src/Rendering/Renderer.h"
	"src/Rendering/Renderer.cpp"
	"src/Rendering/Texture.h"
	"src/Rendering/Texture.cpp"
	"src/Rendering/Shader.h"
	"src/Rendering/Shader.cpp")
	
# Add source to this project's executable
add_executable (${EXEC_NAME} WIN32 ${SOURCE_FILES} "src/Rendering/Shader.h")

find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} ${OPENGL_gl_LIBRARY})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
