add_executable(GoL Main.cpp Game.cpp World.cpp Cell.cpp Grid.cpp)
target_link_libraries(GoL PRIVATE sfml-graphics sfml-window sfml-system)
