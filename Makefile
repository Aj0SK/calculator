CFLAGS = -Wall -O2 -std=c++17
CC = clang++
BUILD = build
SRC = src

GTEST_DIR = lib/googletest/googletest
USER_DIR = build_test
USER_TEST_DIR = test
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = sample1_unittest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

test: calculator prepare_test $(TESTS)

prepare_test:
	mkdir -p $(USER_DIR)

clean_test:
	rm -r -f $(TESTS) $(USER_DIR)

gtest-all.o : $(GTEST_SRCS_)
	$(CC) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $(USER_DIR)/$@

gtest_main.o : $(GTEST_SRCS_)
	$(CC) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $(USER_DIR)/$@

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $(USER_DIR)/$@ $(USER_DIR)/$^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $(USER_DIR)/$@ $(USER_DIR)/gtest-all.o $(USER_DIR)/gtest_main.o

sample1_unittest.o : $(USER_TEST_DIR)/sample1_unittest.cpp $(GTEST_HEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -I$(SRC) -I$(SRC)/generated -c $(USER_TEST_DIR)/sample1_unittest.cpp -o $(USER_DIR)/sample1_unittest.o

sample1_unittest : sample1_unittest.o gtest_main.a
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -I/$(SRC) -lpthread $(USER_DIR)/sample1_unittest.o $(USER_DIR)/gtest_main.a -o $(USER_DIR)/$@ $(BUILD)/variable.o $(BUILD)/driver.o $(BUILD)/parser.o $(BUILD)/scanner.o

all: prepare demo

clean:
	rm -r -f $(BUILD) $(SRC)/generated

prepare:
	mkdir -p $(BUILD)
	mkdir -p $(SRC)/generated

demo: prepare sample calculator
	${CC} ${CFLAGS} -o $(BUILD)/calc++ $(BUILD)/variable.o $(BUILD)/calc++.o $(BUILD)/driver.o $(BUILD)/parser.o $(BUILD)/scanner.o

sample: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -I$(SRC)/generated -c -o $(BUILD)/calc++.o $(SRC)/calc++.cc

calculator: prepare grammar scanner parser driver variable.o

variable.o:
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c $(SRC)/variable.cpp -o $(BUILD)/variable.o

parser: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -I$(SRC) -I$(SRC)/generated -c -o $(BUILD)/parser.o $(SRC)/generated/parser.cc

driver: parser
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -I$(SRC)/generated -c -o $(BUILD)/driver.o $(SRC)/driver.cc

scanner:
	flex  -o $(SRC)/generated/scanner.cc $(SRC)/scanner.ll
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -I$(SRC) -I$(SRC)/generated -c -o $(BUILD)/scanner.o $(SRC)/generated/scanner.cc

grammar:
	bison  --xml --graph=$(SRC)/generated/parser.gv -o $(SRC)/generated/parser.cc $(SRC)/parser.yy
