// Slavnem @2024-09-13
// TCP Server

// Kütüphaneler
#include "TCPServer.h"// TCP Server

/*
    create_socket

    Soket oluşturup soketin durumuna göre
    ya program hata ile sonlandırılacak ya da devam edecek
*/
int create_socket(
    ESocketDomain _domain, // domain adresi
    ESocketType _type, // socket türü (TCP...)
    ESocketProtocol _protocol // protokol
)
{
    // soket oluşturursa başaryıla döner
    // aksi halde zaten kendi hata kodunu döndürür
    return socket((int)_domain, (int)_type, (int)_protocol);
}

/*
    check_socket

    Soket ile ilgili gnöderilen veri hata koduna tekabül ise
    hata mesajı ile program sonlandırılacak
*/
void check_socket(
    int code, // kod
    const char* const message // mesaj
)
{
    // hata koduna eşit ya da daha küçükse
    if(code <= SERVER_ERRCODE)
    {
        perror(message); // mesaj çıktısı
        exit(EXIT_FAILURE); // hatalı sonlandırma
    }
}