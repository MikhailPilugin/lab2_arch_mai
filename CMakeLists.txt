cmake_minimum_required(VERSION 3.2)

project(hl_server C CXX)

SET (ACCOUNT "account")
SET (REPORT "report")
SET (CONFERENCE "conference")

find_package(OpenSSL)
find_package(Threads)
find_package(ZLIB)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL)


if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
include_directories("/usr/include/mysql")
include_directories("/usr/local/include/mysql")
link_directories("/usr/local/lib")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${ACCOUNT} account/main.cpp 
                                 config/config.cpp 
                                 database/database.cpp
                                 database/user.cpp)


target_include_directories(${ACCOUNT} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${ACCOUNT} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-variable )
set_target_properties(${ACCOUNT} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${ACCOUNT} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${ACCOUNT} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             "PocoData"
                             "PocoDataMySQL"
                             "mysqlclient"
                             ZLIB::ZLIB)


add_executable(${REPORT} report/main.cpp
                          config/config.cpp 
                          database/database.cpp
                          database/report.cpp)
                          
target_include_directories(${REPORT} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${REPORT} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-variable )
set_target_properties(${REPORT} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${REPORT} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${REPORT} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             "PocoData"
                             "PocoDataMySQL"
                             "mysqlclient"
                             ZLIB::ZLIB)


add_executable(${CONFERENCE} conference/main.cpp
                             config/config.cpp 
                             database/database.cpp
                             database/report.cpp
                             database/conference.cpp)
                            
target_include_directories(${CONFERENCE} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${CONFERENCE} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-variable )
set_target_properties(${CONFERENCE} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${CONFERENCE} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${CONFERENCE} PRIVATE 
                            ${CMAKE_THREAD_LIBS_INIT} 
                            ${Poco_LIBRARIES}
                            "PocoData"
                            "PocoDataMySQL"
                            "mysqlclient"
                            ZLIB::ZLIB)