cmake_minimum_required(VERSION 3.16)
project(beatcovid)

set(CMAKE_CXX_STANDARD 14)

include_directories(project/include)
include_directories(project/include/Animation)
include_directories(project/include/Interface)
include_directories(project/include/Tinyxml)
include_directories(project/include/Entities)
include_directories(project/include/Entities/Armors)
include_directories(project/include/Entities/Enemies)
include_directories(project/include/Entities/Transports)

add_definitions(-DFILES_PATH="../")

add_executable(beatcovid
        main.cpp
        project/src/Level_map.cpp
        project/src/GameManager.cpp
        project/src/GameLables.cpp
        project/src/Interface/Interface.cpp
        project/src/Interface/InterfaceButton.cpp
        project/src/Interface/InterfaceLabel.cpp
        project/src/Interface/InterfaceTable.cpp
        project/src/Interface/InterfaceMultiLineLabel.cpp
        project/src/Interface/InterfaceSprite.cpp
        project/src/SaveGame.cpp
        project/src/Animation/Animation.cpp
        project/src/Animation/AnimationManager.cpp
        project/src/Entities/Entity.cpp
        project/src/Entities/Antibodies.cpp
        project/src/Entities/Bullet.cpp
        project/src/Entities/Player.cpp
        project/src/Entities/Armors/Armor.cpp
        project/src/Entities/Armors/Cap.cpp
        project/src/Entities/Armors/Shoes.cpp
        project/src/Entities/Armors/Robe.cpp
        project/src/Entities/Enemies/Enemy.cpp
        project/src/Entities/Enemies/OrdinaryEnemies.cpp
        project/src/Entities/Enemies/Police.cpp
        project/src/Entities/Transports/Transport.cpp
        project/src/Entities/Transports/SafeTransport.cpp
        project/src/Entities/Transports/UnSafeTransport.cpp
        project/src/Entities/Sick.cpp
        project/src/MusicManager.cpp
        project/src/Tinyxml/tinyxml.cpp
        project/src/Tinyxml/tinystr.cpp
        project/src/Tinyxml/tinyxmlparser.cpp
        project/src/Tinyxml/tinyxmlerror.cpp)

find_package(SFML REQUIRED system window graphics network audio)
target_link_libraries(beatcovid sfml-graphics sfml-audio)
