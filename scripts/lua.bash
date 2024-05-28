#!/bin/bash

APP=lua
VERSION=5.4.6
SCRIPT_PATH=$(pwd)
BUILDER_PATH=$SCRIPT_PATH
DIR_APP=$BUILDER_PATH/lua-$VERSION
BIN=$SCRIPT_PATH/bin
LIB=$SCRIPT_PATH/lib
DOWNLOAD_APP="https://www.lua.org/ftp/lua-$VERSION.tar.gz"

dependencies() {
	sudo apt update
	sudo apt install \
		libreadline-dev \
		-y
}

download() {
	mkdir -p $BUILDER_PATH
	cd $BUILDER_PATH
	rm -rf $DIR_APP
	curl -L -R -O $DOWNLOAD_APP
	tar xzf $APP-$VERSION.tar.gz
	rm -f $APP-$VERSION.tar.gz
	rm -f lua
	ln -sr $APP-$VERSION $APP
}

build-linux() {
	cd $DIR_APP
	if [[ $VERSION == "5.2.4" ]]; then
		dependencies
		make linux
	elif [[ $VERSION == "5.4.6" ]]; then
		make all test PLATFORM=$PLATFORM
	fi
}

install-linux() {
	mkdir -p $BIN
	cd $DIR_APP/src
	mv $APP ${APP}c $BIN
}

if [[ -v 1 ]]; then
	$1
fi
