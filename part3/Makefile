everything : client1 client2 client3 server1

client1 : a3p3Client1.c
	gcc a3p3Client1.c -o client1

client2 : a3p3Client2.c
	gcc a3p3Client2.c -o client2

client3 : a3p3Client3.c
	gcc a3p3Client3.c -o client3

server1 : a3p3Server1.c
	gcc a3p3Server1.c -o server1 -lpthread -std=gnu99

clean : 
	rm -f server1 client1 client2 client3 a3p3Server1.log a3p3Client1.log a3p3Client2.log a3p3Client3.log junk.txt
