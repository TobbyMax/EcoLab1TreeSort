cmake_minimum_required(VERSION 3.22)
project(Lab2 C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "/TC /Gz")
set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE")
set(CMAKE_EXE_LINKER_FLAGS "/DYNAMICBASE")

add_definitions(-DECO_WINDOWS)
add_definitions(-D_DEBUG)
add_definitions(-DECO_DLL)
add_definitions(-DUGUID_UTILITY)
add_definitions(-DECO_WIN32)
add_definitions(-DWIN32)
add_definitions(-D_WINDOWS)
add_definitions(-D_CONSOLE)

include_directories(HeaderFiles)
include_directories(SharedFiles)
include_directories(UnitTestFiles/HeaderFiles)

include_directories(CalculatorComponents/SharedFiles)

include_directories(
        $ENV{ECO_FRAMEWORK}/Eco.List1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.Core1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.System1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/SharedFiles
)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3A
        SHARED
        SourceFiles/CEcoLab1.c
        SourceFiles/CEcoLab1Factory.c
        SharedFiles/IdEcoLab1.h
        SharedFiles/IEcoLab1.h
        HeaderFiles/CEcoLab1.h
        HeaderFiles/CEcoLab1Factory.h

        CalculatorComponents/SharedFiles/IEcoCalculatorY.h
        CalculatorComponents/SharedFiles/IEcoCalculatorX.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorD.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorE.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorA.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorB.h
)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3D
        SHARED
        SourceFiles/CEcoLab1RBTree.c
        SourceFiles/CEcoLab1RBTreeFactory.c
        SharedFiles/IdEcoLab1RBTree.h
        SharedFiles/IEcoLab1.h
        HeaderFiles/CEcoLab1RBTree.h
        HeaderFiles/CEcoLab1RBTreeFactory.h

        CalculatorComponents/SharedFiles/IEcoCalculatorY.h
        CalculatorComponents/SharedFiles/IEcoCalculatorX.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorD.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorE.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorA.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorB.h
)

add_executable(
        Lab2
        UnitTestFiles/SourceFiles/EcoLab2.c
        SharedFiles/IdEcoLab1.h
        SharedFiles/IEcoLab1.h
        HeaderFiles/CEcoLab1.h
        HeaderFiles/CEcoLab1Factory.h
        SharedFiles/IdEcoLab1RBTree.h
        HeaderFiles/CEcoLab1RBTree.h
        HeaderFiles/CEcoLab1RBTreeFactory.h

        CalculatorComponents/SharedFiles/IEcoCalculatorY.h
        CalculatorComponents/SharedFiles/IEcoCalculatorX.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorD.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorE.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorA.h
        CalculatorComponents/SharedFiles/IdEcoCalculatorB.h
)

include_directories(Lab2/HeaderFiles)
include_directories(Lab2/SharedFiles)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3E
        SHARED
        Lab2/SharedFiles/IEcoLab1.h
        Lab2/SharedFiles/IdEcoLab2.h
        Lab2/HeaderFiles/CEcoLab2.h
        Lab2/HeaderFiles/CEcoLab2Factory.h
        Lab2/SourceFiles/CEcoLab2.c
        Lab2/SourceFiles/CEcoLab2Factory.c
)

target_link_libraries(
        Lab2
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000042757331.lib
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/BuildFiles/Windows/x86/StaticRelease/0000000000000000000000004D656D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000046534D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.System1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000000000100.lib
        $ENV{ECO_FRAMEWORK}/Eco.List1/BuildFiles/Windows/x86/StaticRelease/53884AFC93C448ECAA929C8D3A562281.lib

        1F5DF16EE1BF43B999A434ED38FE8F3A
        1F5DF16EE1BF43B999A434ED38FE8F3D
        1F5DF16EE1BF43B999A434ED38FE8F3E
)