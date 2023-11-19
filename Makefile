GCC=gcc
CFLAGS=-std=c99 -g -Wall -Wshadow --pedantic -Wvla
LDFLAGS =

SRC_DIR = .
OBJ_DIR = .

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = AvlTreeInsertion

VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

testall: test0 test1 test2 test3 test4

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test0: $(EXECUTABLE)
	./$(EXECUTABLE) 1 7 8 2 4 9 3 > output0
	diff -w output0 expected/test0

test1: $(EXECUTABLE)
	./$(EXECUTABLE) 1 2 5 8 7 4 > output1
	diff -w output1 expected/test1

test2: $(EXECUTABLE)
	./$(EXECUTABLE) 1 9 3 6 7 8 2 4 > output2
	diff -w output2 expected/test2

test3: $(EXECUTABLE)
	./$(EXECUTABLE) 9 6 7 0 3 2 1 > output3
	diff -w output3 expected/test3

test4: $(EXECUTABLE)
	./$(EXECUTABLE) 1 2 3 4 5 > output4
	diff -w output4 expected/test4

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE) output? memcheck.txt

testmemory: $(EXECUTABLE)
	$(VAL) ./$(EXECUTABLE) 1 2 3 4 5