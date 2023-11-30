GCC=gcc
CFLAGS=-std=c99 -g -Wall -Wshadow --pedantic -Wvla
LDFLAGS =

SRC_DIR = .
OBJ_DIR = .

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = AvlTreeInsertion

VAL = valgrind --tool=memcheck --leak-check=full --verbose

testall: test0 test1 test2 test3 test4 test5

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test0: $(EXECUTABLE)
	./$(EXECUTABLE) inputs/input0 > output0
	diff -w output0 expected/test0

test1: $(EXECUTABLE)
	./$(EXECUTABLE) inputs/input1 > output1
	diff -w output1 expected/test1

test2: $(EXECUTABLE)
	./$(EXECUTABLE) inputs/input2 > output2
	diff -w output2 expected/test2

test3: $(EXECUTABLE)
	./$(EXECUTABLE) inputs/input3 > output3
	diff -w output3 expected/test3

test4: $(EXECUTABLE)
	./$(EXECUTABLE) inputs/input4 > output4
	diff -w output4 expected/test4

test5: $(EXECUTABLE)
	./$(EXECUTABLE) inputs/input5 > output5
	diff -w output5 expected/test5

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE) output? memcheck?.txt

testmemory: $(EXECUTABLE)
	$(VAL) --log-file=memcheck0.txt ./$(EXECUTABLE) inputs/input0
	$(VAL) --log-file=memcheck1.txt ./$(EXECUTABLE) inputs/input1
	$(VAL) --log-file=memcheck2.txt ./$(EXECUTABLE) inputs/input2
	$(VAL) --log-file=memcheck3.txt ./$(EXECUTABLE) inputs/input3
	$(VAL) --log-file=memcheck4.txt ./$(EXECUTABLE) inputs/input4
	$(VAL) --log-file=memcheck5.txt ./$(EXECUTABLE) inputs/input5