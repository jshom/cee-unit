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

tags:
	ctags -R .
