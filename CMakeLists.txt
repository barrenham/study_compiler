cmake_minimum_required(VERSION 3.28.1)

project(study_compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(text_parser)
add_subdirectory(token)
add_subdirectory(EXCEPTION)
add_subdirectory(syntax_parser)

add_executable(test_TP $<TARGET_OBJECTS:text_parser> $<TARGET_OBJECTS:token> $<TARGET_OBJECTS:my_exception> $<TARGET_OBJECTS:syntax_parser>)