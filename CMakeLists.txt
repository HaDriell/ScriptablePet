cmake_minimum_required(VERSION 3.10)

project(
    ScriptablePet
    VERSION 1.0
    LANGUAGES CXX
)


#Extern dependencies
add_subdirectory(extern)

#Project
add_subdirectory(src)