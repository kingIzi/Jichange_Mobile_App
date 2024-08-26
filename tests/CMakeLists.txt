#cmake_minimum_required(VERSION 3.5)

#project(login_tests LANGUAGES CXX)

#enable_testing()

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)


## add_executable(login_tests tst_login_tests.cpp
##     tst_setup_tests.cpp)
#add_executable(login_tests tst_login_tests.cpp
#    tst_chatbot_tests.cpp)
#add_test(NAME login_tests COMMAND login_tests)

#add_executable(setup_tests setup/tst_setup_tests.cpp
#    setup/tst_branch_tests.cpp setup/tst_country_tests.cpp
#)
#add_test(NAME setup_tests COMMAND setup_tests)




## target_link_libraries(login_tests PRIVATE sources_test Qt${QT_VERSION_MAJOR}::Test)
#target_link_libraries(login_tests PRIVATE sources_test Qt${QT_VERSION_MAJOR}::Test)
#target_link_libraries(setup_tests PRIVATE sources_test Qt${QT_VERSION_MAJOR}::Test)



project(login_tests LANGUAGES CXX)
enable_testing()
find_package(Qt6 REQUIRED COMPONENTS Test)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(login_tests tst_login_tests.cpp)
add_test(NAME login_tests COMMAND login_tests)

add_executable(setup_tests setup/tst_branch_tests.cpp)
add_test(NAME setup_tests COMMAND setup_tests)


target_link_libraries(login_tests PRIVATE sources_test Qt6::Test)
target_link_libraries(setup_tests PRIVATE sources_test Qt6::Test)
