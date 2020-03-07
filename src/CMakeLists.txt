set(CODENAME ${CMAKE_PROJECT_NAME})

set(SOURCES "main.cpp")
add_executable(${CODENAME} ${SOURCES})
#add_library(${CODENAME} STATIC ${SOURCES})

target_include_directories(${CODENAME} PUBLIC "${CMAKE_SOURCE_DIR}/include/")
