# Clang-SSLSocket
Basic client SSL Socket writed in C.

This script was made for people who wanna basic get client service.

## First: Compile your script.
    $ gcc -g -Wall -lssl -lcrypto -o sslsocket sslsocket.c

## Second: Run It.
    $ ./sslsocket
    Usage: ./unidos <ip address> <file or path to get>

That's all.

## Little Test.
If you wanna to check it, you can send request to httpbin.org in https (443) port:
    
    $ ./sslsocket 34.231.30.52 /get
