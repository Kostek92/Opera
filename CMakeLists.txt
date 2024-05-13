cmake_minimum_required(VERSION 3.5)

project(opera LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(opera
	testcases.h testlogicfunction.cpp
	logicfunctioninterface.h
	logicfunctionbase.h logicfunctionbase.cpp
	tablelogicfunction.h tablelogicfunction.cpp
	codelogicfunction.h codelogicfunction.cpp
	logicprocessor.h logicprocessor.cpp)

include(GNUInstallDirs)
install(TARGETS opera
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
