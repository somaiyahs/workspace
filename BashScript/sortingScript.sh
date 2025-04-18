#!/bin/bash

# List of variables
exit_value=10
out_of_range_min=0
out_of_range_max=11
chunk_size=100
records_file="marketing_data.csv"
output_file="sorted_records.csv"

# Define a function to sort the records
sort_records(){
	field=$1

	# split/devide the records into smaller chunks
	split -l $chunk_size -d $records_file tmp_chunk_

	# to specify that the type of the given field is a number we need to add "n" in the -k option
	# ex. field = 9, then -k option should be -k9,9n
	if [ $field -eq 9 ]; then 
		for chunk in tmp_chunk_*; do
			sort -t',' -k9,9n "$chunk" > "$chunk.sorted" &
		done
	elif [ $field -eq 8 ]; then 
		for chunk in tmp_chunk_*; do
			sort -t',' -k8,8 -n -t, -k3,3r "$chunk" > "$chunk.sorted" &
		done
	else

		# sort each chunk of data using a for loop 
		for chunk in tmp_chunk_*; do 
			sort -t',' -k$field,$field "$chunk" > "$chunk.sorted" &
		done
	fi

	# Wait until all the chunks of records are sorted and finished excuting
	wait 

	# 1) Put all the data together: "cat tmp_chunk_*.sorted" 
	# 2) Sort through all as one set of records: "sort -t',' -k$field,$field"
	# 3) Output the sorted records in a file to be outputted: "> $output_file"

	cat tmp_chunk_*.sorted | sort -t',' -k$field,$field > $output_file
	
	# Clean the temporary files.
	rm tmp_chunk_*
}

# Checking if the $record_file exists
if [ ! -f "$records_file" ]; then
	echo "Error: 'marketing_data.csv' file was not found" 
	exit 1
fi 

# Checking if the $output_file exists
if [ ! -f "$output_file" ]; then
	touch "$output_file"
else 
	rm "$output_file"
	touch "$output_file"
fi

# Providing the available options to the user
echo "Fields available for sorting: "
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

# Reading the user input and saving it in the "field_number" variable 
read -p "Enter the field number (1-10): " field_number


# Validating the user input
if [ "$field_number" -eq "$exit_value" ]; then
	exit 1
elif [ "$field_number" -ge "$out_of_range_max" ]; then
	echo "Invalid option! Please provide a number between 1 and 10"
	exit 1
elif [ "$field_number" -le "$out_of_range_min" ]; then 
	echo "Invalid option! Please provide a number between 1 and 10"
	exit 1
fi 

# Calling the sort_records function to sort the records
sort_records $field_number 

# Print the content of the $output_file for testing purposes
cat $output_file

