cmake_minimum_required(VERSION 3.16)
project(beatcovid)
set(CMAKE_CXX_STANDARD 14)

include_directories(project/include)
include_directories(project/include/tinyxml)
add_subdirectory(project/include/tinyxml)

add_executable(beatcovid
        main.cpp
        project/src/Player.cpp
        project/src/Enemy.cpp
        project/src/Bullet.cpp
        project/src/Level_map.cpp
        project/src/Animation.cpp
        project/src/AnimationManager.cpp
        project/src/Entity.cpp
        project/src/GameManager.cpp
        project/src/Antibodies.cpp
        project/src/GameLables.cpp
        project/src/Arrmor.cpp
        project/src/Robe.cpp
        project/src/Gloves.cpp
        project/src/Glasses.cpp
        project/src/Mask.cpp
        project/src/Interface.cpp
        project/src/SaveGame.cpp
        project/src/Breaker.cpp
        project/src/Delivery.cpp
        project/src/Police.cpp
        project/src/Virus.cpp)


find_package(SFML REQUIRED system window graphics network audio)
target_link_libraries(beatcovid sfml-graphics sfml-audio tinyxml)
