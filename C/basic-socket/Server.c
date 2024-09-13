// Slavnem @2024-09-14
// Server

// Kütüphaneler
#include "TCPServer.h" // TCP Server Kütüphanem

// main
int main(void)
{
    // Sunucu mesajı
    char server_message[] = "Sunucuya Hosgeldiniz!";

    // soket nesnesi oluştur
    MySocket msocket = {
        .domain = (ESocketDomain)ESOCK_DOMAIN_IPV4,
        .type = (ESocketType)ESOCK_TYPE_TCP,
        .protocol = (ESocketProtocol)ESOCK_PROTO_TCP,
        .socketconn = create_socket(msocket.domain, msocket.type, msocket.protocol)
    };

    // eğer oluşturma başarısız ise hata verip sonlansın
    check_socket(
        msocket.socketconn,
        "Soket Olusturma Hatasi!"
    );

    // adresi özelleştirme
    SocketAdrrIn server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    // bağlantı kabul etme durumu
    check_socket(
        bind(msocket.socketconn, // bağlantı durumu kodu
        (SocketAddr*)&server_addr, // nesneyi türe çevir ve adresini paylaş
        sizeof(server_addr)), // nesne boyutu
        "Sunucu Baglanti Hatasi!"
    );

    // sunucuyu dinle
    check_socket(
        listen(msocket.socketconn, // bağlantı durumu kodu
        SERVER_CONNLIMIT), // dinleme limiti
        "Sunucu Limitli Dinlemesi Basarisiz!"
    );

    // kullanıcıyu kabul etme
    int client_socket = accept(msocket.socketconn, NULL, NULL);

    // kullanıcıya veri gönder
    send(
        client_socket, // kullanıcı soketi
        server_message, // sunucu mesajı
        sizeof(server_message), // sunucu mesajı boyutu
        0 // bayraklar
    );

    // sunucu soketini kapat
    close(msocket.socketconn);

    // program sonu
    return 0;
}