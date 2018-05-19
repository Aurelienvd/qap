EXE = qap
CC = g++
CPPFLAGS = -Wall -Wno-comment -pedantic -std=c++17
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $<

clean:
	rm *.o
	rm $(EXE)
