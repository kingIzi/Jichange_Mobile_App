cmake_minimum_required(VERSION 3.5)

project(auth LANGUAGES CXX)

enable_testing()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Test)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "C:/Users/scott/Documents/cpp_tools/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "C:/Users/scott/Documents/cpp_tools/googletest")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

set (TEST_FILES
    tst_auth.cpp
    tst_setup_branch.cpp
    tst_company_users.cpp
    tst_company_users_form.cpp
    tst_vendor_registration_form.cpp
    tst_company_users_form.cpp
    tst_customer_form.cpp
    tst_vendor_report_form.cpp
    tst_invoice.cpp
    tst_invoice_form.cpp
)

add_executable(auth main.cpp ${TEST_FILES}
               ${GTestFiles})
add_test(NAME auth COMMAND auth)
target_link_libraries(auth PRIVATE Threads::Threads sources_test Qt6::Test)

