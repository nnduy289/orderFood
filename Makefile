TARGET = test

SRCS = check.cpp main.cpp order.cpp

OBJS = $(SRCS:.c=.o)

CC = g++
CFLAGS = -Wall -g

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.cpp order.h check.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean