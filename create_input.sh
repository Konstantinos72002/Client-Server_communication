# !/bin/bash

if [ $# != 2 ] || [ $2 -le 0 ]; then 
    echo "Wrong arguments"
    exit 0
fi

> $1

CHARACTERS="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
a=$2
while [ $a -ne 0 ];
do
    LENGTH1=$((RANDOM % 10 + 3))
    STRING1=""
    LENGTH2=$((RANDOM % 10 + 3))
    STRING2=""
    for ((i=0; i<LENGTH1; i++)); do
        STRING1+=${CHARACTERS:RANDOM%${#CHARACTERS}:1}
    done
    for ((i=0; i<LENGTH2; i++)); do
        STRING2+=${CHARACTERS:RANDOM%${#CHARACTERS}:1}
    done
    if [ $a -eq 1 ]; then
        echo -n $STRING1 $STRING2>> $1
    else 
        echo $STRING1 $STRING2>> $1
    fi
    ((a -= 1))
done