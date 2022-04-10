project(main)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "aarch64-himix100-linux-gcc")
set(CMAKE_CXX_COMPILER "aarch64-himix100-linux-g++")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_EXE_LINKER_FLAGS "-lpthread -lrt -ldl")


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/opencv/include/opencv4)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/hisisdk/include/)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/ SRCS)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/hisisdk/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/opencv/lib)

add_executable(main main.cpp ${SRCS})
TARGET_LINK_LIBRARIES(main
   VoiceEngine
   upvqe
   securec
   mpi
   tde
   dnvqe
   ive
   opencv_core
   opencv_imgcodecs
   opencv_imgproc)
