CC = gcc
CFLAGS = -Wall -shared -fPIC
LIBS = -Llua -llua -Llibserialport/.libs -lserialport
INCLUDE = -Ilua -Ilibserialport

TARGET = libserial.so

all: $(TARGET)

$(TARGET): libserial.o
	$(CC) -o $(TARGET) $(CFLAGS) $(INCLUDE) $(LIBS) libserial.o

libserial.o: libserial.c
	$(CC) $(CFLAGS) -c libserial.c $(INCLUDE)

clean:
	rm -f *.o $(TARGET)

# Notes:
# gcc -o libserial.so -shared -fPIC -Wall -Ilua -Llua -llua -Llibserialport/.libs -lserialport libserial.c
