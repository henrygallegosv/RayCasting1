cmake_minimum_required(VERSION 3.17)
project(RT1)

set(CMAKE_CXX_STANDARD 20)

add_executable(RT1 main.cpp
        Camara.h Camara.cpp
        Mundo.cpp Mundo.h
        vector.cpp vector.h
        Rayo.cpp Rayo.h
        Objeto.cpp Objeto.h
        Luz.cpp Luz.h
        Esfera.cpp Esfera.h
        Cilindro.cpp Cilindro.h
        Plano.cpp Plano.h
        )
        
set(YOU_NEED_X11 1)

if(${YOU_NEED_X11} EQUAL 1)
    message(STATUS "Looking for X11...")
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(RT1 ${X11_LIBRARIES} -pthread)
else()
    target_compile_definitions(RT1 PRIVATE cimg_display=0)
endif()
