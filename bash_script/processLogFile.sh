# !/bin/bash

declare -A parties_map

if [ ! -e "$1" ]; then
    echo " poll-log doesn't exists."
    exit 0
fi 

names_array=()

exec < "$1"

while read line 
do  
    words=($line)
    name=${words[$((0))]}
    lastname=${words[$((1))]}
    party=${words[$((2))]}
    total="$name $lastname" 

    string_exists=false
    
    for element in "${names_array[@]}"; do
        if [[ "$element" == "$total" ]]; then
            string_exists=true
            break
        fi
    done

    if [ $string_exists == false ]; then
    
        if [[ -v parties_map["$party"] ]]; then
            number="${parties_map["$party"]}"
            ((number += 1))
            parties_map["$party"]=$number
        else
            parties_map["$party"]=1
        fi
    fi

    > pollerResultsFile
    for key in "${!parties_map[@]}"
    do
        value="${parties_map[$key]}"
        echo "Party: $key, Votes: $value" >> pollerResultsFile
    done
done