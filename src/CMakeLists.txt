set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Define sources and executable
set(EXECUTABLE_NAME "Tetris")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
add_executable(${EXECUTABLE_NAME} main.cpp Pit.cpp Game.cpp Pieces.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

