echo "Server 3 is running"
while true; do { echo -e 'HTTP/1.1 200 OK\r\n'; sh my_website_3.sh; } | nc -l 8082; done
