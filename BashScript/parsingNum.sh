#!/bin/bash


# Extracting number using Parameter Expension
string="This is the number 1254"

number="${string##*[!0-9]}"

echo $number

# Extracting Regular Expressions
stringRegX="14,456"

numString="${stringRegX//,/}"

echo $stringRegX
echo "RegX: $numString"

numNumber=$((numString))

echo "Parsed Number: $numNumber"
