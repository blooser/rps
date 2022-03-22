add_library(Backend STATIC)

target_include_directories(Backend PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_sources(Backend
	PRIVATE
                Game.cpp
                Game.h
                player.h
                player.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(Backend PRIVATE Threads::Threads)
