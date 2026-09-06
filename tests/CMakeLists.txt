# Тест (GoogleTest)
add_executable(neuron_test
    neuron_test.cpp
)

# Линкуем с основной библиотекой neuron и GoogleTest
target_link_libraries(neuron_test
    PRIVATE
        neuron
        GTest::gtest_main
)

# Регистрируем тест в CTest
include(GoogleTest)
gtest_discover_tests(neuron_test)
