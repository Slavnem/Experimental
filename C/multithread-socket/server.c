// Slavnem @2024-09-13
// Multi Thread Socket Server

// Kütüphaneler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>

// Ön Tanımlamalar
#define SERVERPORT 2020 // Sunucu Portu
#define BUFSIZE 4096 // Tampon Boyutu
#define SOCKETERROR (-1) // Socket Hatası
#define SERVER_BACKLOG 10 // Aynı Anda İş Yapma Limiti

// Socket Değişken Tür Tanımlama
typedef struct sockaddr_in SocketIn;
typedef struct sockaddr Socket;

// Fonksiyon Prototipi
void * handle_connection(void* p_client_socket);
int check(int exp, const char* msg);

// main
int main(void)
{
    int server_socket, client_socket, addr_size; // sunucu, kullanıcıya ait soket ve adres boyutu
    SocketIn server_addr, client_addr; // sunucu ve kullanıcı adresi

    // yeni soket oluşturma kontrolü
    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)),
        "Socket Olusturma Basarisiz");

    // socket ayarlamalarını yapma
    server_addr.sin_family = AF_INET; // Ipv4 Protokolü
    server_addr.sin_addr.s_addr = INADDR_ANY; // Yerel de herhangi bir IP'ye bağlanabilir
    server_addr.sin_port = htons(SERVERPORT); // Verinin gideceği port yolu

    // Ip adresine ve Port'a bağlamak
    check(bind(server_socket, (Socket*)&server_addr, sizeof(server_addr)),
        "Sunucu Baglanti Hatasi!");

    // Sunucuyu dinlemek
    // "SERVER_BACKLOG" => İzin Verilen Bağlantı Limiti Parametresi
    check(listen(server_socket, SERVER_BACKLOG),
        "Sunucu Dinleme Hatasi");

    // döngü
    while(true)
    {
        printf("\r%s", "Baglanti Icin Bekleniliyor..."); // bildiri
        fflush(stdout); // standart çıktıyı hemen ekrana yazdır

        // bekle ve gelen bağlantıyı kabul et
        addr_size = sizeof(SocketIn);
        check(client_socket =
            // bağlantıyı kabul et
            accept(server_socket, (Socket*)&client_addr, (socklen_t*)&addr_size),
            "Baglanti Kabul Edilemedi");
        
        // bağlantı sağlandı
        printf("\r%s", "Basariyla Baglandi!");
        fflush(stdout);

        // bağlantıyla istediğini yap
        pthread_t t; // thread nesnesi
        
        int *pclient = malloc(sizeof(int)); // bellek alanı ayır
        *pclient = client_socket; // bağlantı adresini ata
        
        // thread oluştur
        pthread_create(&t, NULL, handle_connection, pclient);
    }

    return 0;
}

// check
int check(int exp, const char* msg)
{
    if(exp == SOCKETERROR)
    {
        perror(msg); // hata çıktısı
        exit(EXIT_FAILURE); // hatalı sonlandırma
    }

    // kodu döndür
    return exp;
}

// handle_connection
void * handle_connection(void* p_client_socket)
{
    int client_socket = *((int*)p_client_socket); // oturum soketi
    free(p_client_socket); // daha fazla ihtiyacımız yok
    char buffer[BUFSIZE]; // tampon
    size_t bytes_read; // okunan baytlar
    int msgsize = 0; // mesaj boyutu
    char actualpath[PATH_MAX + 1];

    // dosya için sunucu mesajını oku, 
    while((bytes_read = read(client_socket, buffer + msgsize, sizeof(buffer) - msgsize - 1)) > 0)
    {
        // mesaj boyutuna okunanları ekle
        msgsize += bytes_read;

        // sona gelmişse bitir
        if(msgsize > BUFSIZE - 1 || buffer[msgsize - 1] == '\n') break;
    }

    // hata kontrolü
    check(bytes_read, "Gonderici Veri Hatasi");
    buffer[msgsize - 1] = 0; // mesajı sonlandır

    // sorgu bilgilendirmesi
    printf("SORGU: %s\n", buffer);
    fflush(stdout);

    // doğruluk kontrolü eğer başarısız ise
    if(realpath(buffer, actualpath) == NULL)
    {
        printf("%s\n", "[ERROR] Hatali Bolum", buffer); // hata çıktısı
        close(client_socket); // kullanıcı soket bağlantısını kapat

        return NULL; // boş döndür
    }

    // dosya oku ve içeriği kullanıcıya gönder
    FILE *fp = fopen(actualpath, "r");
    
    // eğer dosya açılmamışsa
    if(fp == NULL)
    {
        printf("%s\n", "[ERROR] Acma Hatasi");
        close(client_socket); // soketi kapat
        
        return NULL;
    }

    // dosya içeriklerini oku ve sunucuya gönder
    while((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0)
    {
        // ne kadar byte veri gönderildiğini çıktı versin
        printf("%zu Byte Veri Gonderiliyor...", bytes_read);
        write(client_socket, buffer, bytes_read);
    }

    // sunucuyu sonlandır ve dosyayı kapat
    close(client_socket);
    fclose(fp);

    // bağlantı sonlandırılıyor mesajı
    printf("Baglangi Sonlandiriliyor...\n");

    return NULL;
}