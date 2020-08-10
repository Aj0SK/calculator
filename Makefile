CFLAGS = -Wall -O2 -std=c++17
CC = g++
BUILD = build
SRC = src

all: prepare demo

prepare:
	mkdir -p $(BUILD)

demo: sample driver parser scanner
	${CC} ${CFLAGS} -o $(BUILD)/calc++ $(BUILD)/calc++.o $(BUILD)/driver.o $(BUILD)/parser.o $(BUILD)/scanner.o

sample: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/calc++.o $(SRC)/calc++.cc
	
parser: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/parser.o $(SRC)/parser.cc

driver:
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/driver.o $(SRC)/driver.cc

scanner:
	flex  -o $(SRC)/scanner.cc $(SRC)/scanner.ll
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/scanner.o $(SRC)/scanner.cc

grammar:
	bison  --xml --graph=$(SRC)/parser.gv -o $(SRC)/parser.cc $(SRC)/parser.yy
