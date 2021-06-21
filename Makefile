.PHONY: usage, clean, sslsocket, socket

# Change C compiler if you need
CC=gcc
CFLAGS=-g -Wall
CERT=cert.pem

all: usage

usage:
	@echo "Usage: make [usage|sslsocket|socket]" >&2
	@echo "" >&2
	@echo "sslsocket: Basic ssl socket (https) in c from sslsocket.c file." >&2
	@echo "socket: Basic socket (http) in c from socket.c file." >&2

sslsocket: sslsocket.c
	openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout $(CERT) -out $(CERT)
	$(CC) $(CFLAGS) -o sslsocket sslsocket.c -lssl -lcrypto

socket: socket.c
	$(CC) $(CFLAGS) -o socket socket.c

clean:
	rm -f sslsocket socket
