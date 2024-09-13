// Slavnem @2024-09-13
// TCP Server
#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

// Kütüphaneler
#include <stdio.h> // Standart I/O
#include <stdlib.h> // Standart

#include <unistd.h> // Küresel Standart

#include <sys/types.h> // Sistem Türleri
#include <sys/socket.h> // Sistem Socket

#include <arpa/inet.h> // Bağlantı Kütüphanesi

// Ön Tanımlamalar
#define SERVER_PORT 1234 // Sunucu Portu (Dosyadan Okuma İle Yapılabilir)
#define SERVER_CONNLIMIT 10 // Sunucu Bağlantı Limiti
#define SERVER_ERRCODE -1 // Sunucu Hata Kodu
#define SERVER_BUFFSIZE 4096 // Sunucu Tampon Boyutu

// Tür Tanımlamaları
typedef struct sockaddr SocketAddr;
typedef struct sockaddr_in SocketAdrrIn;

// Domain Türleri
typedef enum
{
    ESOCK_DOMAIN_IPV4 = AF_INET, // Ipv4
    ESOCK_DOMAIN_IPV6 = AF_INET6, // Ipv6
    ESOCK_DOMAIN_LOCAL = AF_UNIX // Yerel
} ESocketDomain;

// Soket Türleri
typedef enum
{
    ESOCK_TYPE_TCP = SOCK_STREAM, // TCP (3 lü El Sıkışma) (Güvenlik Fazla)
    ESOCK_TYPE_UDP = SOCK_DGRAM, // UDP (2 li El Sıkışma) (Güvenlik Az)
    ESOCK_TYPE_RAW = SOCK_RAW // Ham (Düşük Seviyeli İşlem)
} ESocketType;

// Protokol Türleri
typedef enum
{
    ESOCK_PROTO_TCP = IPPROTO_TCP, // TCP Protokolü
    ESOCK_PROTO_UDP = IPPROTO_UDP // UDP Protokolü
} ESocketProtocol;

// Özel Socket Nesnesi
typedef struct MySocket
{
    ESocketDomain domain;
    ESocketType type;
    ESocketProtocol protocol;
    int socketconn;
} MySocket;

typedef MySocket* MySocketPtr; // işaretçi

// Fonksiyon Prototipi
int create_socket(
    ESocketDomain _domain, // domain adresi
    ESocketType _type, // socket türü (TCP...)
    ESocketProtocol _protocol // protokol
);

void check_socket(
    int code, // kod
    const char* const message // mesaj
);

#endif