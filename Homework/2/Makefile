BUILD_DIR := build
RESULT_DIR := results
HISTOGRAM_PATH := ./histogram
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
	@rm -f ${HISTOGRAM_PATH}


.PHONY: submission
submission: 
	@echo "Zipping together project files..."
	cd ..; \
		tar --exclude='build*' --exclude='.cache*' --exclude='.venv*' \
		--exclude-vcs -cvzf ${NAME}_hw2.tar.gz -C ${CURDIR} .

.PHONY: histogram
histogram: build 
	@echo "Adding ./histogram symlink..."
	@rm -f ${HISTOGRAM_PATH}
	@ln -s ${CURDIR}/${BUILD_DIR}/cli ${HISTOGRAM_PATH}

.PHONY: test 
test: build 
	@./${BUILD_DIR}/test

.PHONY: log 
log: build
	@echo "Running timing analysis, this will take some time to complete..."
	@mkdir -p ${RESULT_DIR}
	@./${BUILD_DIR}/auto > ${RESULT_DIR}/log.csv
