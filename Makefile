
CC = g++

CFLAGS = -Wall -g

LIBS = -lsfml-window -lsfml-graphics -lsfml-system

SRCS = main.cpp TravelingSalesman.cpp City.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = Traveling_Salesman

.PHONY: depend clean

all:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: 
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
