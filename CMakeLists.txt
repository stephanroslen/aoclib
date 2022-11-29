find_package(fmt REQUIRED)
find_package(Threads REQUIRED)

set(LIB_HEADERS
        include/aoclib/Coord2D.h
        include/aoclib/Coord3D.h
        include/aoclib/CT.h
        include/aoclib/Grid2D.h
        include/aoclib/Input.h
        include/aoclib/Overloaded.h
        )

set(LIB_SOURCES)

add_library(aoclib OBJECT ${LIB_HEADERS} ${LIB_SOURCES})
target_include_directories(aoclib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/aoclib)
target_link_libraries(aoclib PUBLIC fmt::fmt Threads::Threads)
