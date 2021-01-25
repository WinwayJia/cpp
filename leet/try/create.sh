#!/bin/bash

echo "create file"
if [ -f ../done/$1.cpp ]; then
    echo $1 "has done"
    exit
fi

if [ -f ./$1.cpp ]; then
    echo $1 "trying"
    exit
fi

cp ./template2.cpp ./$1.cpp
