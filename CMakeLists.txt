cmake_minimum_required(VERSION 3.16)
project(BeatCovid)

set(CMAKE_CXX_STANDARD 14)
include_directories(./)
include_directories(include)
include_directories(include/Animation)
include_directories(include/Entities)
include_directories(include/Entities/Armors)
include_directories(include/Entities/Enemies)
include_directories(include/Entities/Transports)
include_directories(include/Game)
include_directories(include/Interface)
include_directories(include/Tinyxml)

add_definitions(-DFILES_PATH="../")

add_executable(${PROJECT_NAME}
        main.cpp
        ResourcePath.mm
        src/Level_map.cpp
        src/MusicManager.cpp
        src/SaveGame.cpp
        src/Animation/Animation.cpp
        src/Animation/AnimationManager.cpp
        src/Entities/Antibodies.cpp
        src/Entities/Bullet.cpp
        src/Entities/Entity.cpp
        src/Entities/Player.cpp
        src/Entities/Sick.cpp
        src/Entities/Armors/Armor.cpp
        src/Entities/Armors/Cap.cpp
        src/Entities/Armors/Robe.cpp
        src/Entities/Armors/Shoes.cpp
        src/Entities/Enemies/Enemy.cpp
        src/Entities/Enemies/Breaker.cpp
        src/Entities/Enemies/Delivery.cpp
        src/Entities/Enemies/Police.cpp
        src/Entities/Enemies/Virus.cpp
        src/Entities/Transports/SafeTransport.cpp
        src/Entities/Transports/Transport.cpp
        src/Entities/Transports/UnSafeTransport.cpp
        src/Game/GameLabel.cpp
        src/Game/GameLabelManager.cpp
        src/Game/GameManager.cpp
        src/Game/GameTreatPatientProgressBar.cpp
        src/Interface/Interface.cpp
        src/Interface/InterfaceButton.cpp
        src/Interface/InterfaceImage.cpp
        src/Interface/InterfaceLabel.cpp
        src/Interface/InterfaceTable.cpp
        src/Tinyxml/tinystr.cpp
        src/Tinyxml/tinyxml.cpp
        src/Tinyxml/tinyxmlerror.cpp
        src/Tinyxml/tinyxmlparser.cpp)

find_package(SFML REQUIRED system window graphics network audio)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
