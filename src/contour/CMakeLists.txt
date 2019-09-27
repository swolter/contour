find_package(Freetype)
find_package(OpenGL)
find_package(GLEW)
find_package(glfw3 CONFIG)
find_package(glm CONFIG)

if("${CMAKE_SYSTEM}" MATCHES "Linux")
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(yaml-cpp REQUIRED IMPORTED_TARGET yaml-cpp)
elseif("${CMAKE_SYSTEM}" MATCHES "Windows")
	# installed via vcpkg
	find_package(yaml-cpp CONFIG REQUIRED)
endif()

add_executable(contour
	Contour.cpp Contour.h
	Config.cpp Config.h
	FileChangeWatcher.cpp FileChangeWatcher.h
	Flags.cpp Flags.h
	Window.cpp Window.h
	main.cpp
)

target_link_libraries(contour PRIVATE GLEW::GLEW OpenGL::GL glm glfw glterminal yaml-cpp)
