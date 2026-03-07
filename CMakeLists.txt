cmake_minimum_required(VERSION 3.24)

project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(tictactoe_test tests/tictactoe_test.cpp src/tictactoe.cpp)
add_executable(main main.cpp src/tictactoe.cpp)

target_link_libraries(tictactoe_test PRIVATE Catch2::Catch2WithMain)
