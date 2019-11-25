project(TrtSet)

set(HEADER_FILES
        Trit.h
        TritSet.h
        )

set(SOURCE_FILES
        Trit.cpp
        TritSet.cpp
        )

add_library(TritSet_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})