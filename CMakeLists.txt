cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project ("fastboard-cpp")

add_executable (fastboard-cpp 
	"src/main.cpp"  
	"src/application.cpp"
	 "src/game.cpp")


#Debugging purposes only
