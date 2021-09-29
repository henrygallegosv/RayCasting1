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