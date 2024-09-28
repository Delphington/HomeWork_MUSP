cmake_minimum_required(VERSION 3.27)
project(task_1_1_stack)

set(CMAKE_CXX_STANDARD 17)
link_directories("C:/Users/Professional/source")

add_executable(task_1_1_stack main.cpp)
# Найдите пакет SFML
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics network audio)

if (SFML_FOUND)
    # Добавьте директории с заголовками
    include_directories(${SFML_INCLUDE_DIR})

    # Создайте исполняемый файл
    add_executable(task_1_1_stack main.cpp)

    # Линкуйте библиотеки SFML
    target_link_libraries(task_1_1_stack ${SFML_LIBRARIES})
else()
    message(FATAL_ERROR "SFML not found")
endif()