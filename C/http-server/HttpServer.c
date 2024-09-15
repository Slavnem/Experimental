// Slavnem @2024-09-15
// HTTP Server

// Kütüphaneler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

// Ön Tanımlamalar
#define SERVER_PORT 4040 // Sunucu Portu
#define SERVER_LIMIT 10 // Kullanıcı Kabul Limiti

#define INDEX "index.html" // HTML Sayfası

#define RESPONSE_SIZE 1024 // HTTP Yanıt Boyutu
#define HEADER_SIZE 2048 // HTTP Header Boyutu

// Tür Tanımlamalar
typedef FILE File;
typedef File* FilePtr;

typedef struct sockaddr SocketAddr;
typedef struct sockaddr_in SocketAddrIn;

// main
int main(void)
{
    FilePtr htmlData; // html dosyası için

    // index dosyasını okuma modunda aç
    // açılamazsa hata ver
    if((htmlData = fopen(INDEX, "r")) == NULL)
    {
        printf("%s file didn't open or find!\n", INDEX);
        return 1;
    }

    // yanıt verisi için değişken
    char responseData[RESPONSE_SIZE];

    // dosyadan verileri okusun
    fgets(responseData, sizeof(responseData), htmlData);

    // http başlık verisi
    char httpHeader[HEADER_SIZE] = "HTTP/1.1 200 OK\r\n\n";

    // dönen yanıtı http başlığına ekle
    strcat(httpHeader, responseData);

    // tcp soket oluştur
    int serverSocket;

    // soket kontrolü
    if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("%s\n", "Socket Olusturulamadi");
        return 1;
    }

    // socket adresi
    SocketAddrIn serverAdress;

    // socket ayarlamaları
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(SERVER_PORT);
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    // bağlantı kabul etme
    if(bind(serverSocket, (SocketAddr*)&serverAdress, sizeof(serverAdress)) < 0)
    {
        printf("%s\n", "Sunucu Baglanti Kabulu Yapilamadi");
        return 1;
    }

    // sunucuyu dinleme
    if(listen(serverSocket, SERVER_LIMIT) < 0)
    {
        printf("%s\n", "Sunucu Dinlemesi Basarisiz");
        return 1;
    }

    // kullanıcı soketi
    int clientSocket;

    // döngüyle
    while(1)
    {
        // kullanıcı kabulü
        clientSocket = accept(serverSocket, NULL, NULL);
        
        // veri gönder
        send(clientSocket, httpHeader, sizeof(httpHeader), 0);
        
        // yük oluşmaması için soketi kapat
        close(clientSocket);
    }

    return 0;
}