BUILD_DIR := build
NAME ?= waddoups

build: build_dir
	cmake --build ${BUILD_DIR}
	@echo ""
	@echo "Binaries are found in ${BUILD_DIR}"

.PHONY: build_dir
build_dir:
	@mkdir -p $(BUILD_DIR);
	cd $(BUILD_DIR); cmake ..

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

.PHONY: cli_test
cli_test: build 
	@echo ""
	@echo "##### Basic test #####"
	@cd ${BUILD_DIR}; \
		./cli 4 10 0.0 5.0 100
	@echo ""
	@echo "##### Uneven Elements test #####"
	@cd ${BUILD_DIR}; \
		./cli 3 10 0.0 5.0 79

