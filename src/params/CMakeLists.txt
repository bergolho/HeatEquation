set(SOURCE_FILES_PARAMS params.h params.cpp)

ADD_LIBRARY(params STATIC ${SOURCE_FILES_PARAMS})

if(NOT MSVC)
    set_property(TARGET params PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()