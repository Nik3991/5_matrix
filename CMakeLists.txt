cmake_minimum_required(VERSION 3.4)

if (NOT DEFINED INV{TRAVIS_BIULD_NUMBER})
    set (ENV{TRAVIS_BUILD_NUMBER} 1)
endif()

project (matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

if (WIN32)
    find_package(BOOST COMPONENTS unit_test_framework REQUIRED)
else()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()

if (NOT Boost_FOUND)
    message ("___BOOST_NOT_FOUND___")
endif()

link_libraries(${Boost_LINK_LIBRARIES})

SET (FILES ${PROJECT_SOURCE_DIR}/matrix/Matrix.h)

SET (TESTS tests)

add_executable(${PROJECT_NAME} matrix/main.cpp ${FILES})
add_executable(${TESTS} unit_tests/tests.cpp)

set_target_properties (${PROJECT_NAME} ${TESTS} PROPERTIES
                       CXX_STANDARD 17
                       CXX_STANDARD_REQUIRED ON
if (NOT WIN32)
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
endif()
)

set_target_properties(${TESTS} PROPERTIES
        COMPILE_DEFINIITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries (${TESTS} ${Boost_LIBRARIES})
target_link_libraries (${PROJECT_NAME})

#---------------------------

install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT nikbar93@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
