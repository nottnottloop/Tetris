cmake_minimum_required (VERSION 3.12)
set (CMAKE_CXX_STANDARD 17)

project ("Tetris")

#set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/ase/app.rc")

set (SOURCES
	src/main.cpp
	src/renderwindow.cpp
	src/entity.cpp
	src/game.cpp
	src/gamestate.cpp
	src/introstate.cpp
	src/playingstate.cpp
	src/text.cpp
	src/basicbutton.cpp
	src/tetromino.cpp
	${APP_ICON_RESOURCE_WINDOWS}
)

add_executable (Tetris ${SOURCES})
#add_executable (Tetris WIN32 ${SOURCES})
set_target_properties(Tetris PROPERTIES OUTPUT_NAME "Tetris")

target_include_directories (Tetris PUBLIC
	C:/dev/Libraries/SDL2-2.0.16vc/include/SDL2
	#"C:/dev/Libraries/SDL2-2.0.16gcc/x86_64-w64-mingw32/include/SDL2"
	include
)

target_link_directories (Tetris PUBLIC
	C:/dev/Libraries/SDL2-2.0.16vc/lib/x64
	#"C:/dev/Libraries/SDL2-2.0.16gcc/x86_64-w64-mingw32/lib"
)

target_link_libraries(Tetris SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)