TEST_ENTRYPOINT = ./tests/test.c
TEST_OUT = test.o
CC = gcc

.PHONY: test tags

test:
	make test_build && make test_run && make test_clean

test_build: $(TEST_ENTRYPOINT)
	$(CC) $(TEST_ENTRYPOINT) -o $(TEST_OUT)

test_run: $(TEST_OUT)
	./$(TEST_OUT)

test_clean: $(TEST_OUT)
	rm $(TEST_OUT)

memory_test_build:
	docker build -t cee-unit-memory-test ./tests/

memory_test_run:
	docker run -it \
		-v "$(shell PWD)":/src/dev/ \
		cee-unit-memory-test:latest \
		bash -c \
			'cd /src/dev/ && \
			gcc ./tests/test.c -o test.o && \
			valgrind \
				--leak-check=full \
				--error-exitcode=1 \
				-v ./test.o;'

pwd_check:
	echo $(shell pwd)

tags:
	ctags -R .
