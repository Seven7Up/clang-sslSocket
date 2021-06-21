#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/crypto.h>
#include <openssl/ossl_typ.h>
#include <openssl/ssl.h>

void print_err(char msg[], ...){
  va_list comp;
  va_start(comp, msg);
  vfprintf(stderr, msg, comp);
  fflush(stderr);
  va_end(comp);
  exit(1);
}

int main(int argc, char *argv[]){
  if (argc != 3)
    print_err("Usage: %s <hostname> <file or path to get>\n", argv[0]);

  int net_socket;
  int conn_socket;
  struct sockaddr_in servaddr;
  char *IPbuffer;
  struct hostent *host_entry;
  char sendbuff[4096];
  int sendbytes;
  char recvbuff[4096];
  SSL_CTX *ctx;
  const SSL_METHOD *method;
  SSL *ssl;

  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();

  method = SSLv23_client_method();
  ctx = SSL_CTX_new(method);
  SSL_CTX_use_PrivateKey_file(ctx, "cert.pem", SSL_FILETYPE_PEM);
  SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM);

  if ((net_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    print_err("Could not create a socket!\n");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(443);

  host_entry = gethostbyname(argv[1]);

  if ((IPbuffer = inet_ntoa(*((struct in_addr *) host_entry -> h_addr_list[0]))) == NULL)
    print_err("Could not get the host ip address!\n");

  if (inet_pton(AF_INET, IPbuffer, &servaddr.sin_addr.s_addr) <= 0)
    print_err("Could not convert the ip address to a binary ip address!\n");

  if ((conn_socket = connect(net_socket, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0)
    print_err("Could not connect to the address!\n");

  ssl = SSL_new(ctx);
  SSL_set_fd(ssl, net_socket);
  SSL_connect(ssl);
  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

  bzero(&sendbuff, sizeof(sendbuff));
  sprintf(sendbuff,
          "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: "
          "Mozilla/5.0 (Microsoft Windows NT; Win64 x64; rv:86.0) "
          "Gecko/20100101 Firefox/86.0\r\nAccept: */*\r\n\r\n",
          argv[2], argv[1]);

  sendbytes = strlen(sendbuff);
  if (SSL_write(ssl, sendbuff, sendbytes) != sendbytes)
    print_err("Could not send the request!\n");

  bzero(&recvbuff, sizeof(recvbuff));
  while (SSL_read(ssl, &recvbuff, 4095) > 0) {
    printf("%s\n", recvbuff);
    bzero(&recvbuff, sizeof(recvbuff));
  }

  SSL_free(ssl);
  SSL_CTX_free(ctx);
  close(conn_socket);
  close(net_socket);

  return 0;
}
