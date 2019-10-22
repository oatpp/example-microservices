#!/bin/sh

run_service () {

    echo "running project $1"
    cd "$1/build/"

    ./$1-exe &

    cd ../../

}

run_service user-service
run_service book-service
run_service facade

