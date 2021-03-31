cmake_minimum_required(VERSION 2.8)

project(BA_test)

include_directories("/usr/local/include/eigen3")
include_directories(include)
include_directories($({OpenCV_INCLUDE_DIRS}))


find_package(OpenCV  REQUIRED)


add_executable(BA_test src/main.cpp src/BA_test.cpp)
target_link_libraries(BA_test  ${OpenCV_LIBS})


