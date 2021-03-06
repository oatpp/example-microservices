#!/bin/sh

build_service () {

    echo "building project $1"
    mkdir -p "$1/build"

    cd "$1/build/"

    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

    cd ../../

}

cd ../../

build_service user-service
build_service book-service
build_service facade
