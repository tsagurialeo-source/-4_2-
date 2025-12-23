cmake_minimum_required(VERSION 3.20)
project(products_db)

set(CMAKE_CXX_STANDARD 17)

add_executable(products_db main.cpp)

target_include_directories(products_db PRIVATE /opt/homebrew/include)

target_link_libraries(products_db
        /opt/homebrew/lib/libpqxx.dylib
        /opt/homebrew/lib/libpq.dylib
)
