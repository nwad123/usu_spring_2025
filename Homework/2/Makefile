BUILD_DIR := build
NAME ?= waddoups

build: build_ 
	cmake --build ${BUILD_DIR}

.PHONY: build_ 
build_: build_dir
	cd $(BUILD_DIR); cmake ..

.PHONY: build_dir
build_dir:
	@mkdir -p $(BUILD_DIR);

.PHONY: clean
clean:
	@echo "Removing build directory (${BUILD_DIR})..."
	@rm -rf ${BUILD_DIR}

.PHONY: submission
submission: 
	@echo "Zipping together project files..."
	cd ..; \
		tar --exclude='build*' --exclude='.cache*' --exclude='.venv*' \
		--exclude-vcs -cvzf ${NAME}_hw2.tar.gz -C ${CURDIR} .
