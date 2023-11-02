# Variables
CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lpthread
TARGET = a4
SRC = a4.c

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)
