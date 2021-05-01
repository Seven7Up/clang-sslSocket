# Clang-SSLSocket

Basic client SSL Socket writed in C.

This script was made for people who wanna basic get client service.

## Firstly: Setup your certification file and privatekey file.

    $ openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout cert.pem -out cert.pem

Note IF YOU HAVE ANOTHER CERTIFICATION FILE NAME or PRIVATEKEY FILE NAME, you need to change some lines of code.
Go to sslsocket.c and change cert and privkey file name:

    SSL_CTX_use_certificate_file(ctx, "<certification file>", SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, "<privatekey file>", SSL_FILETYPE_PEM);

## Secondly: Compile your script.

    $ gcc -g -Wall -o sslsocket sslsocket.c -lssl -lcrypto

## Thirdly: Run It.

    $ ./sslsocket
    Usage: ./unidos <ip address> <file or path to get>

That's all.

## Little Test.

If you wanna to check it, you can send request to httpbin.org in 443 (https) port:

'''
$ ./sslsocket 34.231.30.52 /get
HTTP/1.1 200 OK
Date: Wed, 14 Apr 2021 13:43:02 GMT
Content-Type: application/json
Content-Length: 328
Connection: close
Server: gunicorn/19.9.0
Access-Control-Allow-Origin: \*
Access-Control-Allow-Credentials: true

{
"args": {},
"headers": {
"Accept": "_/_",
"Host": "34.231.30.52",
"User-Agent": "Mozilla/5.0 (Microsoft Windows NT; Win64 x64; rv:86.0) Gecko/20100101 Firefox/86.0",
"X-Amzn-Trace-Id": "Root=1-6076f166-356138672c6ae5874ce563fa"
},
"origin": "<I can\'t show you my ip address :)>",
"url": "https://34.231.30.52/get"
}
'''

Done!
