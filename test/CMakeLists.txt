set(MAIN_TEST main_test.cpp)

add_executable(main_test ${MAIN_TEST})

target_link_libraries(main_test src)

add_test(NAME main_test COMMAND main_test)