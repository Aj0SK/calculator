CFLAGS = -Wall -O2 -std=c++17
CC = g++
BUILD = build

all: prepare demo

prepare:
	mkdir -p $(BUILD)

demo: sample driver parser scanner
	${CC} ${CFLAGS} -o $(BUILD)/calc++ $(BUILD)/calc++.o $(BUILD)/driver.o $(BUILD)/parser.o $(BUILD)/scanner.o

sample: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/calc++.o calc++.cc
	
parser: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/parser.o parser.cc

driver:
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/driver.o driver.cc

scanner:
	flex  -oscanner.cc scanner.ll
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -o $(BUILD)/scanner.o scanner.cc

grammar:
	bison  --xml --graph=parser.gv -o parser.cc parser.yy
