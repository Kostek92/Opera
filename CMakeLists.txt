cmake_minimum_required(VERSION 3.5)

project(opera LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(opera
    logicfunction.cpp logicfunction.h testcases.h testlogicfunction.cpp)

include(GNUInstallDirs)
install(TARGETS opera
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
