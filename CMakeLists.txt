project(superServer)
cmake_minimum_required(VERSION 2.8)

add_executable(superServer
   main.c
   connections.c
   fileutils.c
   opts.c
   )

target_link_libraries(superServer
   pthread
   )

