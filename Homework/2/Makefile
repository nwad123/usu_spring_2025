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
submission: main_artifact
# Add anything here that you want repeated for each submission
	@echo "Copying file(s) to artifact directory"
	cd ..; \
		tar --exclude='*/${BUILD_DIR}/*' --exclude='tests/*' --exclude='*/\.*' \
		--exclude='*.tar.gz' -cvzf ${NAME}_hw2.tar.gz ${CURDIR}
