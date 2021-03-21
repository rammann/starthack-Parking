cmake_minimum_required(VERSION 3.16)

project(Starthack VERSION 1.0)

add_executable(${PROJECT_NAME} sbb.cpp)
add_executable(predictor predictor.cpp)

target_include_directories(
  ${PROJECT_NAME} PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/include/nlohmann"
  "${PROJECT_SOURCE_DIR}/data"
  "/home/ryan/.local/lib/eigen-3.3.9"
)
