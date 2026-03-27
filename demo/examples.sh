#!/bin/bash

EXAMPLES=examples.dox
echo "/**" > $EXAMPLES

for f in *.c
do
    echo "\example $f" >> $EXAMPLES
    rg "/\*\*(.*?)\*/" --multiline-dotall --multiline $f -N | rg -v -N "/\*\*" | rg -v "\*/" >> $EXAMPLES
done

echo "*/" >> $EXAMPLES