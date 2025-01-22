include_directories(include)
include_directories(../general_type/include)

file(GLOB TOKEN_SOURCE_FILES "*.cpp")
add_library(token OBJECT ${TOKEN_SOURCE_FILES})