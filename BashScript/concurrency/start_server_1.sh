echo "Server 1 is running!"
while true; do { echo -e 'HTTP/1.1 200 OK\r\n'; sh my_website_1.sh; } | nc -l 8080; done
