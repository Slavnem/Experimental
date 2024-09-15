// Slavnem @2024-09-15
// HTTP Client

// Kütüphaneler
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SocketAddr;
typedef struct sockaddr_in SocketAddrIn;

// Ön Tanımlamalar
#define SERVER_PORT 4040 // Sunucu Portu

#define RESPONSE_SIZE 4096 // Yanıt Boyutu

// main
int main(int argc, const char* const argv[])
{
    // argüman zorunlu
    if(argc < 2)
    {
        printf("%s\n", "Arguman Zorunlu");
        return 1;
    }

    // adres
    const char* const address = argv[1];

    // kullanıcı soketi
    int clientSocket;

    // soket kontrol
    if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("%s\n", "Socket Olusturulamadi");
        return 1;
    }

    // adrese bağlantı
    SocketAddrIn remoteAddress = {
        .sin_family = AF_INET,
        .sin_port = htons(80)
    };

    inet_aton(address, &remoteAddress.sin_addr.s_addr);

    // bağlan
    if(connect(clientSocket, (SocketAddr*)&remoteAddress, sizeof(remoteAddress)) < 0)
    {
        printf("%s\n", "Baglanti Saglanamadi");
        return 1;
    }

    // sorgu ve yanıt değişkenleri
    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[RESPONSE_SIZE];

    // veri gönder
    send(clientSocket, request, sizeof(request), 0);

    // veriyi al
    recv(clientSocket, &response, sizeof(response), 0);

    // sunucu yanıtını çıktı ver
    printf("%s%s\n", "Sunucu Yaniti: ", response);

    // socketi kapat
    close(clientSocket);

    return 0;
}