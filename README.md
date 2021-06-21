# Clang-SSLSocket

Basic client SSL Socket writed in C.

This script was made for people who wanna basic get client service.

## Run ONE COMMAND!

Run this command in your terminal after clone it.

```
make sslsocket
```
Output:
```
openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout cert.pem -out cert.pem
Generating a RSA private key
.................+++++
..+++++
writing new private key to 'cert.pem'
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:US
State or Province Name (full name) [Some-State]:New-York
Locality Name (eg, city) []:New York
Organization Name (eg, company) [Internet Widgits Pty Ltd]:My Company Inc
Organizational Unit Name (eg, section) []:Basic
Common Name (e.g. server FQDN or YOUR name) []:Owner
Email Address []:owner@basic.org
gcc -g -Wall -o sslsocket sslsocket.c -lssl -lcrypto
```

Then run sslsocket:

```
./sslsocket
```
Output:
```
Usage: ./unidos <ip address> <file or path to get>
```

That's all.

## Little Test.

If you wanna to check it, you can send request to httpbin.org in 443 (https) port:

```
./sslsocket httpbin.org /get
```
Output:
```
HTTP/1.1 200 OK
Date: Mon, 21 Jun 2021 11:55:48 GMT
Content-Type: application/json
Content-Length: 327
Connection: close
Server: gunicorn/19.9.0
Access-Control-Allow-Origin: *
Access-Control-Allow-Credentials: true

{
  "args": {}, 
  "headers": {
    "Accept": "*/*", 
    "Host": "httpbin.org", 
    "User-Agent": "Mozilla/5.0 (Microsoft Windows NT; Win64 x64; rv:86.0) Gecko/20100101 Firefox/86.0", 
    "X-Amzn-Trace-Id": "Root=1-60d07e44-70075f4108c308e3399817a6"
  }, 
  "origin": "<I will NOT show you my ip address :) >", 
  "url": "https://httpbin.org/get"
}

```

## For help:

When you wanna help (I made basic http socket without ssl encryption):

```
make
```
or
```
make usage
```
Output:
```
Usage: make [usage|sslsocket|socket]

sslsocket: Basic ssl socket (https) in c from sslsocket.c file.
socket: Basic socket (http) in c from socket.c file.
```

Done!
