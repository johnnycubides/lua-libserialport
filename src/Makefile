CC = gcc -v
CFLAGS = -O2 -fPIC
LDFLAGS = -shared
LIBSERIALPORT_DIR =.
INCLUDES = -Iinclude
LIBS = -L$(LIBSERIALPORT_DIR)/lib -lserialport

f=./luatest/test.lua

all: libserial.so

libserial.so: libserial.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) -Wl,-rpath,$(LIBSERIALPORT_DIR)/lib

libserial.o: libserial.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test:
	./lua $f

dist-linux:
	rm -f libserial.zip
	zip -r libserial.zip ./lib/libserialport.so.0 ./libserial.so

clean:
	rm -f *.o libserial.so *.zip
# Notes:
# gcc -o libserial.so -shared -fPIC -Wall -Ilua -Llua -llua -Llibserialport/.libs -lserialport libserial.c
# gcc -o mi_aplicacion main.c -I./libserialport -L./libserialport/.libs -lserialport -static
# Saber los símbolos que tienen una librería: 
# nm -D libserialport.so | grep sp_ope
# ldd libserial.so
