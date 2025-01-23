include_directories(../general_type/include)
include_directories(../text_parser/include)
include_directories(../EXCEPTION/include)
include_directories(../token/include)

file(GLOB SYNTAX_SOURCE_FILES "*.cpp")

add_library(syntax_parser OBJECT ${SYNTAX_SOURCE_FILES})