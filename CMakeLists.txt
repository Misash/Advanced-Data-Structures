cmake_minimum_required(VERSION 3.22)
project(EDA)

set(CMAKE_CXX_STANDARD 14)

add_executable(EDA main.cpp lab_2/3.4_Abstract_Data_Type.cpp)


add_executable(VectorFijo lab_1/vectorFijo.cpp)
add_executable(VectorDinamico lab_1/vectorOObjetos.cpp)
add_executable(vectorModular lab_1/vectorModular.cpp)
add_executable(vectorDinamico lab_1/vectorDinamico.cpp)
add_executable(3.5_Design_Patterns lab_2/3.5_Design_Patterns.cpp)
add_executable(3.7_Namespaces lab_2/3.7_Namespaces.cpp)
add_executable(3.8.2_Reducing_code lab_2/3.8.2_Reducing_code.cpp)
add_executable(3.6_Function_Object lab_2/3.6_Function_Object.cpp)
add_executable(3.4_Abstract_Data_Type lab_2/3.4_Abstract_Data_Type.cpp lab_3/comp.cpp lab_3/compVector.cpp)
add_executable(comp lab_3/comp.cpp)
add_executable(compVector lab_3/compVector.cpp)
add_executable(QuadTree ED/QuadTree.cpp)
add_executable(QTcompress lab_5/QTcompress.cpp)
add_executable(ReadWriteImg lab_4/ReadWriteImg.cpp)
add_executable(test ED/test.cpp)
add_executable(bitmap lab_5/bitmap.cpp)
add_executable(z lab_6/z.cpp)

add_executable(dbscan lab_7/dbscan.cpp)
add_executable(dbscan2 lab_7/dbscan2.cpp)