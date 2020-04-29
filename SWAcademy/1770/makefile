CC = g++
CFLAGS = -g -W -Wall
TARGET = main
OBJECTS = solution.o main.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o  $@ $^

clean :
	rm *.o main