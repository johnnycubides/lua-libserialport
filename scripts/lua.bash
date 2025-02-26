#!/bin/bash

APP=lua
VERSION=5.4.6
SCRIPT_PATH=$(pwd)
BUILDER_PATH=$SCRIPT_PATH/build-app
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
  echo "Crear enlace simbólico de lua al src de libserial."
  rm -rf ../src/lib/lua
  ln -sr $APP-$VERSION/src/ ../src/lib/lua
}

build-linux() {
  cd $DIR_APP
  rm -f ../../src/lib/lua
  ln -sr src ../../src/lib/lua
  if [[ $VERSION == "5.2.4" ]]; then
    dependencies
    make linux
  elif [[ $VERSION == "5.4.6" ]]; then
    make clean
    make all test PLATFORM=$PLATFORM
  fi
  cp src/lua ../../src/lua
}

build-windows() {
  cd $DIR_APP
  # rm -f ../../src/lib/lua
  # ln -sr src ../../src/lib/lua
  if [[ $VERSION == "5.2.4" ]]; then
    dependencies
    make linux
  elif [[ $VERSION == "5.4.6" ]]; then
    make clean
    make CC=x86_64-w64-mingw32-gcc mingw
  fi
  # cp src/lua ../../src/lua
}

install-linux() {
  mkdir -p $BIN
  cd $DIR_APP/src
  mv $APP ${APP}c $BIN
}

install-windows() {
  mkdir -p $BIN
  cd $DIR_APP/src
  mv $APP.exe ${APP}c.exe ${APP}54.dll $BIN
}

if [[ -v 1 ]]; then
  $1
fi
