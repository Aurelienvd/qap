EXE = qap
TEST = unit
CC = g++
CPPFLAGS = -Wall -Wno-comment -pedantic -std=c++17
SRCS = $(filter-out test.cpp, $(wildcard *.cpp))
OBJS = $(SRCS:.cpp=.o)
TEST_SRCS = $(filter-out qap.cpp, $(wildcard *.cpp))
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(EXE) $(TEST)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

$(TEST): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TEST)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $<

clean:
	rm *.o
	rm $(EXE)
	rm $(TEST)
