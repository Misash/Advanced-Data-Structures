cmake_minimum_required(VERSION 3.22)
project(EDA)

set(CMAKE_CXX_STANDARD 14)

add_executable(EDA main.cpp lab_2/3.4_Abstract_Data_Type.cpp)


add_executable(VectorFijo lab_1/vectorFijo.cpp)
add_executable(VectorDinamico lab_1/vectorOObjetos.cpp)
add_executable(vectorModular lab_1/vectorModular.cpp)
add_executable(vectorDinamico lab_1/vectorDinamico.cpp)
add_executable(3.4_Abstract_Data_Type lab_2/3.4_Abstract_Data_Type.cpp lab_2/3.5_Design_Patterns.cpp lab_2/3.6_Function_Object.cpp lab_2/3.6_CBinaryTree.cpp lab_2/3.7_Namespaces.cpp lab_2/3.8_Run_Time.cpp lab_2/MyNS.h lab_2/3.8.1_Pool.cpp lab_2/3.8.2_Reducing_code.cpp)
add_executable(3.5_Design_Patterns lab_2/3.5_Design_Patterns.cpp)
add_executable(3.6_Code_Workgroup lab_2/3.6_Function_Object.cpp)
add_executable(3.7_Namespaces lab_2/3.7_Namespaces.cpp)
add_executable(3.8_Run_Time lab_2/3.8_Run_Time.cpp)
add_executable(3.8.1_Pool lab_2/3.8.1_Pool.cpp)
add_executable(3.8.2_Reducing_code lab_2/3.8.2_Reducing_code.cpp)