#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <resolv.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <openssl/crypto.h>
#include <openssl/ossl_typ.h>
#include <openssl/ssl.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <ip address> <file or path to get>\n", argv[0]);
    exit(1);
  }

  int net_socket;
  int conn_socket;
  struct sockaddr_in servaddr;
  char sendbuff[4096];
  char recvbuff[4096];
  SSL_CTX *ctx;
  const SSL_METHOD *method;
  SSL *ssl;

  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();

  method = SSLv23_client_method();
  ctx = SSL_CTX_new(method);
  SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM);
  SSL_CTX_use_PrivateKey_file(ctx, "cert.pem", SSL_FILETYPE_PEM);

  net_socket = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(443);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);

  conn_socket =
      connect(net_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));

  ssl = SSL_new(ctx);
  SSL_set_fd(ssl, net_socket);
  SSL_connect(ssl);
  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

  bzero(&sendbuff, sizeof(sendbuff));
  sprintf(sendbuff,
          "GET %s HTTP/1.0\r\nHost: 34.199.75.4\r\nUser-Agent: "
          "Mozilla/5.0 (Microsoft Windows NT; Win64 x64; rv:86.0) "
          "Gecko/20100101 Firefox/86.0\r\nAccept: */*\r\n\r\n",
          argv[2]);
  SSL_write(ssl, &sendbuff, strlen(sendbuff));

  bzero(&recvbuff, sizeof(recvbuff));
  while (SSL_read(ssl, &recvbuff, 4095) > 0) {
    printf("%s", recvbuff);
    bzero(&recvbuff, sizeof(recvbuff));
  }

  SSL_free(ssl);
  SSL_CTX_free(ctx);
  close(conn_socket);
  close(net_socket);

  return 0;
}
