CC = g++
LD = g++
CPPFLAGS = -std=c++11 -g -Wall -pedantic
LDFLAGS =

# Add any extra .cpp files to this line to
# have them compiled automatically.
SRCS = metatictactoe.cpp metagame.cpp board.cpp

OBJS = $(SRCS:.cpp=.o)

all: tictactoe

tictactoe: $(OBJS)
	g++ -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

clean :
	rm -f tictactoe *.o
