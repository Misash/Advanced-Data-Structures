cmake_minimum_required(VERSION 3.22)
project(EDA)

set(CMAKE_CXX_STANDARD 14)

add_executable(EDA main.cpp)


add_executable(VectorFijo lab_1/vectorFijo.cpp)
add_executable(VectorDinamico lab_1/vectorOObjetos.cpp)
add_executable(vectorModular lab_1/vectorModular.cpp)
add_executable(vectorDinamico lab_1/vectorDinamico.cpp)