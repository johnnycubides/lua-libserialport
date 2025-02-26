CFLAGS = -O2 -fPIC
INCLUDES = -Iinclude -Ilib/lua
LDFLAGS = -shared
LIBSERIALPORT_DIR =.

ifeq ($(AR),w64)
CC = x86_64-w64-mingw32-gcc -v
LIBS = -L$(LIBSERIALPORT_DIR)/lib  -L$(LIBSERIALPORT_DIR)/lib/lua -lserialport -llua
OBJ=libserial.dll
CFLAGS += -D_WIN64
else	ifeq ($(AR),w32)
CC = i686-w64-mingw32-gcc -v
LIBS = -L$(LIBSERIALPORT_DIR)/lib -L$(LIBSERIALPORT_DIR)/lib/lua -lserialport -llua
OBJ=libserial.dll
else
CC = gcc -v
LIBS = -L$(LIBSERIALPORT_DIR)/lib -lserialport
OBJ=libserial.so
endif

h: help

all: $(OBJ)

libserial.dll: libserial.o
	@echo "##> ENLAZAR"
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) -Wl,-rpath,$(LIBSERIALPORT_DIR)/lib

libserial.so: libserial.o
	@echo "##> ENLAZAR"
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) -Wl,-rpath,$(LIBSERIALPORT_DIR)/lib

libserial.o: libserial.c
	@echo "##> COMPILAR"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test-linux:
	../bin/lua ./luatest/linux-test.lua

test-windows:
	wine ../bin/lua ./luatest/windows-test.lua

dist-linux: $(OBJ)
	rm -f libserial.zip
	zip -r libserial.zip ./lib/libserialport.so.0 ./libserial.so

dist-windows:
	cp ./bin/libserialport-0.dll .

clean:
	rm -f *.o libserial.dll libserial.so *.zip

help:
	@echo "make all -> Construye la librería para Linux"
	@echo "make all AR=w64 -> Construye la librería para Windows"
	@echo "make clean -> Borra los objetos creados"
# Notes:
# gcc -o libserial.so -shared -fPIC -Wall -Ilua -Llua -llua -Llibserialport/.libs -lserialport libserial.c
# gcc -o mi_aplicacion main.c -I./libserialport -L./libserialport/.libs -lserialport -static
# Saber los símbolos que tienen una librería: 
# nm -D libserialport.so | grep sp_ope
# ldd libserial.so
