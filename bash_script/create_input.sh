# !/bin/bash

if [ $# != 2 ] || [ $2 -le 0 ] || [ $1 != "politicalParties.txt" ]; then 
    echo "Wrong arguments"
    exit 0
fi

> input_file

num_lines=$(wc -l < "$1")
((num_lines += 1))


CHARACTERS="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
a=$2
while [ $a -ne 0 ];
do
    random_line=$((1 + RANDOM % num_lines))
    random_name=$(sed -n "${random_line}p" "$1")
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
    echo $STRING1 $STRING2 $random_name>> input_file
    ((a -= 1))
done