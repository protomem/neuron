# Тест (GoogleTest)
add_executable(iris_test_suite
    iris_test.cpp
)

# Линкуем с основной библиотекой neuron и GoogleTest
target_link_libraries(iris_test_suite
    PRIVATE
        neuron
        GTest::gtest_main
)

# Регистрируем тест в CTest
include(GoogleTest)
gtest_discover_tests(iris_test_suite)
