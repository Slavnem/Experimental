// Slavnem @2024-09-14
// Connect

// Kütüphaneler
#include "TCPServer.h" // TCP Server Kütüphanem

// main
int main(void)
{
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
        "Baglanti Soketi Olusturma Hatasi!"
    );

    // adresi özelleştirme
    SocketAdrrIn server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    // bağlantı durumu kontrolü
    check_socket(
        connect(msocket.socketconn, // bağlantı durumu kodu
        (SocketAddr*)&server_addr, // nesneyi türe çevir ve adresini paylaş
        sizeof(server_addr)), // nesne boyutu
        "Sunucuya Baglanilamadi Hatasi!"
    );

    // sunucu tampon veri depolayıcı
    char server_buffer[SERVER_BUFFSIZE];

    // sunucudan yanıtı al
    recv(
        msocket.socketconn, // bağlantı durumu
        server_buffer, // veri tamponu
        sizeof(server_buffer), // tampon boyutu
        0 // bayraklar
    );

    // sunucu yanıtı
    printf("\r%s%s\n", "Sunucu Yaniti: ", server_buffer);

    // bağlantıyı kapat
    close(msocket.socketconn);

    // program sonu
    return 0;
}