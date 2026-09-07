# Минимально требуемая версия CMake
cmake_minimum_required(VERSION 3.15)

# Описание проекта: имя, версия и используемые языки
project(neuron VERSION 0.0.0 LANGUAGES CXX)

# Опция сборки тестов (можно отключить через -DNEURON_BUILD_TESTS=OFF)
option(NEURON_BUILD_TESTS "Build neuron tests" ON)

# Включаем экспорт базы компиляции для LSP (clangd, ccls и т.п.)
# В результате в каталоге сборки будет файл compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Цель библиотеки neuron
# (статическая или динамическая, в зависимости от BUILD_SHARED_LIBS)
add_library(neuron
    src/neuron.cpp
    src/Neuron.cpp
    src/Layer.cpp
    src/math.cpp
)

# Публичные заголовочные файлы
# (папка include будет видна потребителям библиотеки)
# BUILD_INTERFACE — для сборки из исходников
# INSTALL_INTERFACE — для установленного пакета
target_include_directories(neuron
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Настройки стандарта C++
set_target_properties(neuron PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Экспорт символов при сборке динамической библиотеки под Windows
if(WIN32 AND BUILD_SHARED_LIBS)
    target_compile_definitions(neuron PRIVATE NEURON_EXPORTS)
endif()

# Настройки установки (install) – пути берем из GNUInstallDirs
include(GNUInstallDirs)

install(TARGETS neuron
    EXPORT neuronTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT neuronTargets
    FILE neuronTargets.cmake
    NAMESPACE neuron::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/neuron
)

# Блок для тестов
if(NEURON_BUILD_TESTS)
    include(FetchContent)

    # Подтягиваем GoogleTest через FetchContent
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )

    # Для старых версий CMake
    # необходимо явно вызывать FetchContent_MakeAvailable
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    add_subdirectory(tests)
endif()
