CFLAGS = -Wall -O2 -std=c++17
CC = g++

all: demo

demo: sample driver parser scanner
	${CC} ${CFLAGS} -o calc++ calc++.o driver.o parser.o scanner.o

sample: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -ocalc++.o calc++.cc
	
parser: grammar
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -oparser.o parser.cc

driver:
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -odriver.o driver.cc

scanner:
	flex  -oscanner.cc scanner.ll
	${CC} ${CFLAGS} -Wno-unused-result -DDG=1 -c -oscanner.o scanner.cc

grammar:
	bison  --xml --graph=parser.gv -o parser.cc parser.yy
