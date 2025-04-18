#!/bin/bash


# Define a function for sorting
sort_records() {
	field=$1
if [ "$field" -eq 9 ]; then
	field_type=9n 
else
	field_type=$1
fi
	split -l $chunk_size -d marketing_data.csv temp_chunk_
	
for chunk in temp_chunk_*; do 
    sort -t',' -k$field,$field_type "$chunk" > "$chunk.sorted" &
done

wait 

cat temp_chunk_*.sorted | sort -t',' -k$field,$field_type > sorted_data.csv

rm temp_chunk_*
}


if [ ! -f "marketing_data.csv" ]; then

	echo "Error: 'marketing_data.csv' file not found"
	exit 1
fi

echo "Fields available for sorting:"
echo "1. First Name"
echo "2. Last Name"
echo "3. Time Zone"
echo "4. Gender"
echo "5. Job Title"
echo "6. Department"
echo "7. Company"
echo "8. Salary"
echo "9. Age"
echo "10. exit" 

read -p "Enter the field number (1-10): " field_number

if [ "$field_number" -eq 10 ]; then
	exit 1
elif [ "$field_number" -ge "out_of_range" ]; then 

	echo "Invalid option"
	exit 1
fi

chunk_size=100

sort_records $field_number

cat sorted_data.csv
