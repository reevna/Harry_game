cmake_minimum_required(VERSION 3.8 FATAL_ERROR)


set(SFML_DIR "c:/SFML-2.5.1/lib/cmake/SFML")

project(sfml-game)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2.4 COMPONENTS window graphics  system REQUIRED)

add_subdirectory(01)


