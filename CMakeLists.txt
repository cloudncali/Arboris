cmake_minimum_required(VERSION 2.8)
project(Arboris)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src/)

# includes cmake/FindSFML.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
# application include files
set(INC
	${SRCROOT}/RPG_types.hpp
	${SRCROOT}/Components.hpp
	${SRCROOT}/Components/Character.hpp
	${SRCROOT}/Components/Drawable.hpp
	${SRCROOT}/Components/MapObject.hpp
	${SRCROOT}/Components/Movable.hpp
	${SRCROOT}/Components/Transformable.hpp
	${SRCROOT}/Application.hpp
	${SRCROOT}/FontAsset.hpp
	${SRCROOT}/FontHandler.hpp
	${SRCROOT}/MusicAsset.hpp
	${SRCROOT}/MusicHandler.hpp
	${SRCROOT}/StateManager.hpp
	${SRCROOT}/TextureAsset.hpp
	${SRCROOT}/TextureHandler.hpp
	${SRCROOT}/IState.hpp
	${SRCROOT}/GameState.hpp
	${SRCROOT}/ConsoleState.hpp
	${SRCROOT}/TitleState.hpp
	${SRCROOT}/Systems.hpp
	${SRCROOT}/Systems/BehaviorSystem.hpp
	${SRCROOT}/Systems/CollisionSystem.hpp
	${SRCROOT}/Systems/CombatSystem.hpp
	${SRCROOT}/Systems/MovementSystem.hpp
	${SRCROOT}/Systems/RenderSystem.hpp
	${SRCROOT}/World.hpp
	${SRCROOT}/base64.h
	${SRCROOT}/tinyxml2.h
	${SRCROOT}/tmxparser.h
	${SRCROOT}/Console.hpp
	${SRCROOT}/FileSystem.hpp
	${SRCROOT}/Util.hpp
	${SRCROOT}/InputMapping.hpp
	${SRCROOT}/Tilemap.hpp
	${SRCROOT}/Events.hpp
	${SRCROOT}/DataParser.hpp
	${SRCROOT}/MenuManager.hpp
)

# application source files
set(SRC
	${SRCROOT}/Application.cpp
	${SRCROOT}/FontAsset.cpp
	${SRCROOT}/FontHandler.cpp
	${SRCROOT}/MusicAsset.cpp
	${SRCROOT}/MusicHandler.cpp
	${SRCROOT}/StateManager.cpp
	${SRCROOT}/TextureAsset.cpp
	${SRCROOT}/TextureHandler.cpp
	${SRCROOT}/main.cpp
	${SRCROOT}/IState.cpp
	${SRCROOT}/GameState.cpp
	${SRCROOT}/ConsoleState.cpp
	${SRCROOT}/TitleState.cpp
	${SRCROOT}/Systems/BehaviorSystem.cpp
	${SRCROOT}/Systems/CollisionSystem.cpp
	${SRCROOT}/Systems/CombatSystem.cpp
	${SRCROOT}/Systems/MovementSystem.cpp
	${SRCROOT}/Systems/RenderSystem.cpp
	${SRCROOT}/World.cpp
	${SRCROOT}/base64.cpp
	${SRCROOT}/Console.cpp
	${SRCROOT}/InputMapping.cpp
	${SRCROOT}/FileSystem.cpp
	${SRCROOT}/tinyxml2.cpp
	${SRCROOT}/tmxparser.cpp
	${SRCROOT}/Tilemap.cpp
	${SRCROOT}/DataParser.cpp
	${SRCROOT}/MenuManager.cpp
)

find_package(GExL REQUIRED)
find_package(SFML 2 COMPONENTS graphics audio window system main) 
find_package (entityx REQUIRED)
find_package (TGUI 0.7 REQUIRED)
include_directories(${ENTITYX_INCLUDE_DIR} ${GExL_INCLUDE_DIR} ${SFML_INCLUDE_DIR}  ${TGUI_INCLUDE_DIR} )

add_executable(${PROJECT_NAME}
                ${SRC} ${INC})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SFML_LIBRARIES} ${TGUI_LIBRARY})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} optimized ${ENTITYX_LIBRARY} optimized ${GExL_LIBRARY})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} debug ${ENTITYX_LIBRARY_DEBUG} debug ${GExL_DEBUG_LIBRARY})

file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_BINARY_DIR})
