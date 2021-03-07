cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TESTS_SOURCES "tests/*.cpp")
file(GLOB_RECURSE BONUS_SOURCES "bonus/src/*.cpp")

include_directories(
    "include/"
    "include/Components"
    "include/Components/GateComponents"
    "include/Components/LogicComponents"
    "include/Components/IOComponents"
    "include/Components/IOComponents/Out"
    "include/Components/IOComponents/In"
    "include/Parser"
    "include/Shell"
)

# nanotekspice
project(nanotekspice)
add_executable(nanotekspice ${SOURCES})
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(nanotekspice PUBLIC -O3 -W -Wall -Wextra -pedantic)
endif()

# bonus
project(nanotekspice_graphic)
add_executable(nanotekspice_graphic EXCLUDE_FROM_ALL ${SOURCES} ${BONUS_SOURCES})
target_compile_options(nanotekspice_graphic PUBLIC -DBONUS)
target_include_directories(nanotekspice_graphic PUBLIC "bonus/include")
target_link_libraries(nanotekspice_graphic PUBLIC sfml-graphics sfml-window sfml-system -lpthread)

# unit_tests
project(tests_run)
add_executable(tests_run EXCLUDE_FROM_ALL ${SOURCES} ${TESTS_SOURCES})

target_include_directories(tests_run PUBLIC "tests/")
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(tests_run PUBLIC -DTESTS_RUN -O3 --coverage -W -Wall -Wextra -pedantic)
    target_link_libraries(tests_run PUBLIC criterion --coverage)

    add_custom_command(TARGET tests_run POST_BUILD
        COMMAND $<TARGET_FILE:tests_run>
        COMMAND rm -f $<TARGET_FILE:tests_run>
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    target_compile_options(tests_run PUBLIC -DTESTS_RUN)
    target_link_directories(tests_run PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/MSVC_DEPS/criterion/lib")
    target_link_libraries(tests_run PUBLIC criterion)
    target_include_directories(tests_run PUBLIC "MSVC_DEPS/criterion/include")

    add_custom_command(TARGET tests_run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/MSVC_DEPS/criterion/bin/criterion.dll" ${CMAKE_BINARY_DIR}/Debug
        COMMAND $<TARGET_FILE:tests_run>
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()