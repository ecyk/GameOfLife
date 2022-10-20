cmake_minimum_required(VERSION 3.15)

project(App
  LANGUAGES CXX
  VERSION 1.0
)

add_subdirectory(ext)
add_subdirectory(src)




# -DBUILD_SHARED_LIBS=ON

# project(App)

# add_subdirectory(${PROJECT_SOURCE_DIR}/ext/SFML)

# add_executable(App main.cpp)
# target_include_directories(App PUBLIC ${PROJECT_SOURCE_DIR}/ext/SFML/include)
# find_package(SFML COMPONENTS graphics window system)
# target_link_libraries(App sfml-graphics sfml-window sfml-system)
