#!/bin/bash

APP=libserialport
SCRIPT_PATH=$(pwd)
BUILDER_PATH=$SCRIPT_PATH/build-app
DIR_APP=$BUILDER_PATH/$APP

dependencies-linux() {
	sudo apt update
	sudo apt install \
		libtool \
		-y
}

dependencies-windows() {
	sudo apt update
	sudo apt install \
		libtool \
		mingw-w64 \
		-y
}

download() {
	mkdir -p $BUILDER_PATH
	cd $BUILDER_PATH
	rm -rf $DIR_APP
	git clone git@github.com:sigrokproject/libserialport.git $APP
}

build-linux() {
	cd $DIR_APP
	make clean
	./autogen.sh
	# ./configure
	./configure --prefix=$(pwd)/../../src/
	make
	make install
	echo "ls -ltrh .libs/"
	ls -ltrh .libs/
}

build-windows() {
	cd $DIR_APP
	make clean
	./autogen.sh
	# Configuración para windows 64 bits
	./configure --prefix=$(pwd)/../../src/ --host=x86_64-w64-mingw32
	# Configuración para windows de 32 bits
	# ./configure --prefix=$(pwd)/../../src/ --host=i686-w64-mingw32
	make
	make install
	echo "ls -ltrh .libs/"
	ls -ltrh .libs/
}

if [[ -v 1 ]]; then
	$1
fi
