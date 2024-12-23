project(MTH9815Final)

set(CMAKE_CXX_COMPILER /usr/bin/g++) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


add_executable(generate_data GenerateData.cpp)

add_executable(trading_system main.cpp)
target_link_libraries(trading_system ${Boost_LIBRARIES})

add_executable(load_price LoadPrice.cpp)
add_executable(load_market LoadMarket.cpp)
add_executable(load_trade LoadTrade.cpp)
add_executable(load_inquiry LoadInquiry.cpp)