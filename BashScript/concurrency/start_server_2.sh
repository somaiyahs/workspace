echo "Server 2 is running"
while true; do { echo -e 'HTTP/1.1 200 OK\r\n'; sh my_website_2.sh; } | nc -l 8081; done
