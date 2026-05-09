cmake_minimum_required(VERSION 3.10)
project(SuperBulles C)

set(CMAKE_C_STANDARD 99)

add_executable(SuperBulles
        main.c jeu.c entites.c input.c affichage.c collisions.c sauvegarde.c
        collisions.h
)

target_link_libraries(SuperBulles -lmingw32 -lalleg44)