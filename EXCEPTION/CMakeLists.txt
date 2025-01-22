include_directories(../general_type/include)

file(GLOB EXCEPTION_SOURCE_FILES "*.cpp")

add_library(my_exception OBJECT ${EXCEPTION_SOURCE_FILES})