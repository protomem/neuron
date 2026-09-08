BUILD_DIR ?= build
CMAKE_BUILD_TYPE ?= Debug
CXX_COMPILER ?= clang++

## Генерация файлов сборки CMake
configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-DCMAKE_CXX_COMPILER=$(CXX_COMPILER) \
		..

## Сборка всего проекта
all: configure
	cmake --build $(BUILD_DIR)

## Запуск тестов (ctest из каталога сборки)
tests: all
	cd $(BUILD_DIR) && ctest --output-on-failure

## Установка (путь задаётся через DESTDIR или CMAKE_INSTALL_PREFIX)
install: all
	cmake --build $(BUILD_DIR) --target install

## Очистка артефактов сборки
clean:
	rm -rf $(BUILD_DIR)

# Параллельная сборка (можно вызывать как `make -j`)
.PHONY: all configure clean install tests help

## Краткая справка по целям Makefile (генерируется автоматически из комментариев)
help:
	@echo "Доступные цели:" && \
	awk 'BEGIN { FS = ":" } \
	     /^##/ { sub(/^##[[:space:]]*/, "", $$0); desc = $$0; next } \
	     /^[a-zA-Z0-9_.-]+:/ && desc { name = $$1; gsub(/[[:space:]]*/, "", name); printf "  make %-10s - %s\n", name, desc; desc = "" }' $(MAKEFILE_LIST)
