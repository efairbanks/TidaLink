#ifndef DIRTYUDP_HPP
#define DIRTYUDP_HPP
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/osc/OscReceivedElements.h"
#include "oscpack/osc/OscPrintReceivedElements.h"
void error(char* message) {
  perror(message);
  exit(0);
}
class UdpSender {
  private:
    int socketFile;
    int port;
    int bufferSize;
    char* buffer;
    char* host;
    struct sockaddr_in serverAddress;
    struct hostent* server;
  public:
    UdpSender(char* host, int port, int bufferSize) {
      this->host = host;
      this->port = port;
      this->bufferSize = bufferSize;
      this->buffer = (char*)calloc(this->bufferSize, sizeof(char));
      // create socket
      this->socketFile = socket(AF_INET, SOCK_DGRAM, 0);
      if(this->socketFile < 0) error("ERROR: Could not open socket\n");
      // get DNS entry for server
      this->server = gethostbyname(this->host);
      if(this->server == NULL) {
        fprintf(stderr, "ERROR: Could not find host %s\n", this->host);
        exit(0);
      }
      // construct server address
      bzero((char*)&this->serverAddress, sizeof(this->serverAddress));
      this->serverAddress.sin_family = AF_INET;
      bcopy((char*)this->server->h_addr,
            (char*)&this->serverAddress.sin_addr.s_addr,
            this->server->h_length);
      this->serverAddress.sin_port = htons(this->port);
    }
    void Send(char* packet, int packetSize) {
      int tempFile;
      if(packetSize > this->bufferSize)
        error("ERROR: Packet length exceeds buffer size\n");
      bzero(this->buffer, this->bufferSize*sizeof(char));
      bcopy(packet, this->buffer, packetSize);
      tempFile = sendto(this->socketFile,
                        this->buffer,
                        packetSize,
                        0,
                        (struct sockaddr *)&this->serverAddress,
                        sizeof(this->serverAddress));
      if(tempFile < 0)
        error("ERROR: There was an issue sending UDP");
      return;
    }
};
class UdpReceiver {
  private:
    int socketFile;
    int port;
    int bufferSize;
    int socketOptions;
    char* buffer;
    char* clientIP;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    struct hostent* client;
    socklen_t clientLength;
  public:
    UdpReceiver(int port, int bufferSize) {
      this->port = port;
      this->bufferSize = bufferSize;
      this->buffer = (char*)calloc(this->bufferSize, sizeof(char));
      // create socket
      this->socketFile = socket(AF_INET, SOCK_DGRAM, 0);
      if(this->socketFile < 0) error("ERROR: Could not open socket\n");
      // speedhax
      this->socketOptions = 1;
      setsockopt( this->socketFile,
                  SOL_SOCKET,
                  SO_REUSEADDR,
                  (const void*)&this->socketOptions,
                  sizeof(int));
      // construct server address
      bzero((char*)&this->serverAddress, sizeof(this->serverAddress));
      this->serverAddress.sin_family = AF_INET;
      this->serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
      this->serverAddress.sin_port = htons((unsigned short)this->port);
      // bind socket
      if(bind(this->socketFile,
              (struct sockaddr *)&this->serverAddress,
              sizeof(this->serverAddress)) < 0)
        error("ERROR: There was an issue binding the socket");
      this->clientLength = sizeof(this->clientAddress);
    }
    void Loop(void (*udpCallback)(char* packet, int packetSize)) {
      int packetSize;
      bzero(this->buffer, this->bufferSize*sizeof(char));
      packetSize = recvfrom(  this->socketFile,
                              this->buffer,
                              this->bufferSize,
                              0,
                              (struct sockaddr *)&this->clientAddress,
                              &this->clientLength);
      if(packetSize < 0)
        error("ERROR: There was a problem receiving data from a client");
      this->client = gethostbyaddr( (const char*)&this->clientAddress.sin_addr.s_addr,
                                    sizeof(this->clientAddress.sin_addr.s_addr),
                                    AF_INET);
      if(this->client == NULL)
        error("ERROR: Error getting client host info");
      this->clientIP = inet_ntoa(this->clientAddress.sin_addr);
      if(this->clientIP == NULL)
        error("ERROR: Error getting client IP.");
      // ----------------------------- //
      // --- Some old info logging --- //
      // ----------------------------- //
      /*
      printf("Received datagram from %s (%s):\n",
              this->client->h_name,
              this->clientIP);
      for(int i=0; i<strlen(this->buffer)&&i<this->bufferSize; i++)
        printf("%c", this->buffer[i]);
      printf("\n");
      */
      udpCallback(this->buffer, packetSize);
    }
};
#endif
