client1 : a3p2Client1.c
	gcc a3p2Client1.c -o client1

client2 : a3p2Client2.c
	gcc a3p2Client2.c -o client2

server1 : a3p2Server1.c
	gcc a3p2Server1.c -o server1 -lpthread -std=gnu99

clean : 
	rm -f server1 client1 client2 a3p2Server1.log a3p2Client1.log a3p2Client2.log junk.txt
