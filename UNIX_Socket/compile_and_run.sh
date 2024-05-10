gcc tcp_server.c -o tcp_server -Wall
gcc tcp_client.c -o tcp_client -Wall

gcc udp_server.c -o udp_server -Wall
gcc udp_client.c -o udp_client -Wall

./tcp_server &
./udp_server &

sleep 3

./tcp_client &
./udp_client &

wait

rm -f udp_server udp_client tcp_client tcp_server