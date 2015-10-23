all: httpd client

httpd: httpd.c
	gcc -W -Wall -lpthread -o httpd httpd.c

client: client.c
	gcc -W -Wall -o client client.c

clean:
	rm httpd client
