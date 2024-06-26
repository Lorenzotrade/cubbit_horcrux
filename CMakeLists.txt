cmake_minimum_required(VERSION 3.10)

project(horcrux LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
set(CMAKE_CXX_FLAGS_INIT "-Werror -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address,undefined, thread, leak -fsanitize-undefined-trap-on-error")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fsanitize=address,undefined -static-libasan")
endif()
find_package(GTest)
if(GTEST_FOUND)
set(Gtest_FOUND TRUE)
endif()
if(GTest_FOUND)
message("Gtest_FOUND = TRUE")
include(GoogleTest)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CXX_FILESYSTEM_LIBRARIES "stdc++fs")
endif()

# ============================================================================
# Project sources
# ============================================================================

message (STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
#Sources
set(${PROJECT_NAME}_SRC_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/src/file.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/file_split_merge.cpp 
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp  
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC_FILES}
)
# ============================================================================
# Project includes
# ============================================================================
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CXX_FILESYSTEM_LIBRARIES})

target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC  gtest gtest_main pthread GTest::GTest stdc++fs ) 

add_subdirectory(UnitTest)

