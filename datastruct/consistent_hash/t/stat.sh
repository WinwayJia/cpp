#!/bin/bash

if [ $# -lt 1 ]
then
    echo "unspecified file"
    exit;
fi

total=0
nodes="34 35 36 37 38 39 40 41 42 43"
for i in $nodes; do
    num=`grep "\<$i\>" $1 | wc -l`
    (((total = total + num)))
    printf "%s: %03d\n" $i $num
done

printf "total: %03d\n" $total

