SHELL   = /bin/sh
CC      = gcc

FLAGS       = -Iinclude
CFLAGS      = -fPIC -pedantic -Wall -Wextra
LDFLAGS     = -shared

HEADERS = $(shell echo include/*.h)
SOURCES = $(shell echo src/*.c)
TESTS   = $(shell echo tests/*.c)
# SOURCE_OBJECTS  = $(SOURCES:.c=.so)
# TEST_OBJECTS    = $(TESTS:.c=.so)

TEST_BIN    = bin/tests

# $(SOURCE_OBJECTS): $(SOURCES)
# 	$(CC) $(SOURCES) $(FLAGS) $(CFLAGS) $(LDFLAGS) -o $(SOURCE_OBJECTS)

# $(TEST_BIN): $(TESTS) $(SOURCE_OBJECTS)
# 	$(CC) $(TESTS) $(FLAGS) -Lsrc $(CFLAGS) -o $(TEST_BIN) -l:fmt.so

$(TEST_BIN): $(TESTS) $(SOURCES)
	mkdir -p bin
	$(CC) $(SOURCES) $(TESTS) $(FLAGS) $(CFLAGS) -o $(TEST_BIN)

tests: $(TEST_BIN)
	$(TEST_BIN)

clean:
	rm -rf bin