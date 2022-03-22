add_library(Backend STATIC)

target_include_directories(Backend PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_sources(Backend
	PRIVATE
                Game.cpp
                Game.h
                player.h
                player.cpp
)
