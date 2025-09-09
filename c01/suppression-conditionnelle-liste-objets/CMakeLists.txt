cmake_minimum_required(VERSION 3.10.0)
project(c01-suppression-conditionnelle-liste-objets VERSION 0.1.0 LANGUAGES C CXX)

set(SRC_FILES
    main.cpp
)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)
