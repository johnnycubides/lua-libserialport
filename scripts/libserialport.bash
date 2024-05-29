#!/bin/bash

APP=libserialport
SCRIPT_PATH=$(pwd)
BUILDER_PATH=$SCRIPT_PATH/build-app
DIR_APP=$BUILDER_PATH/$APP

dependencies() {
	sudo apt update
	sudo apt install \
		libtool \
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
	dependencies
	./autogen.sh
	# ./configure
	./configure --prefix=$(pwd)/../../src/
	make
	make install
	echo "ls -ltrh .libs/"
	ls -ltrh .libs/
}

if [[ -v 1 ]]; then
	$1
fi
