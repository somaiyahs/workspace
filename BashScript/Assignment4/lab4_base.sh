#!/bin/bash

memory=$(ps -eo pid,user,%mem,vsz,rss,cmd)  # allows us to see memory by process, virtual memory, available memory
process=$(top -b -o +%MEM | head -n 15)  #Lists all memory sorted by the process number and the memory associated with that number.
General_Virtual_Mem=$(free -m) # gives a general overview of mem
virtual=$(top -b -o +VIRT | head -n 15) #gives the top memory using VM.
user=$(top -b -o +USER | head -n 15) #gives the top memory usage by user.
currentDate=$(LC_TIME=ru_RU date "+%d %B %Y (%A)") # generates the date
First_month=$(date -d "-1 month 00:00" +%s) #Logs time for use.
last_month=$(date -d "this month -1 second 00:00" +%s) #Logs time for use.

{

echo "Report Generated on: *$currentDate*"  # Alllows us to see what day the report was generated on
echo
echo "-----------------------------------Memory Audit Script----------------------------------------"
echo
echo "---------------------------General and Virtual Memory Overview -------------------------------"
vmstat
echo
free -m  # Gives an overview of the free memory available.
echo
echo "Memory Overview:"
echo "------------------------------------Memory Usage----------------------------------------------"
echo
echo "$memory" #The above command. Created a variable in case of further use.
echo
echo "------------------------------Top Memory Usage By Process-------------------------------------"
echo
echo "$process" # The above command, shows the top 5 processes using memory.
echo
echo "--------------------------------- Top Memory Usage By VM --------------------------------------"
echo "$virtual" # shows the top processes using virtual memory
echo
echo "-------------------------------------Top Memory by User----------------------------------------"
echo
echo "$user" # retrieves the user information
echo

echo sar -f /var/log/sa/sar_memory_data -s "$(date -d "last Sunday" "+%Y-%m-%d 00:00:00")" | grep -E '^[0-9]{2}:[0-9]{2}:[0-9]{2} [APM]{2}' > weekly_memory_report.txt

} >> "DailyReport.txt"
