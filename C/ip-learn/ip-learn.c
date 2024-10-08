// Slavnem @2024-10-09
// Main

// Kütüphaneler
#include <stdio.h> // C Standart I/O Kütüphanesi
#include <stdlib.h> // C Standart Kütüphanesi
#include <string.h> // C Standart String Kütüphanesi
#include <curl/curl.h> // cURL Kütüphanesi

// Ön Tanımlama
#define __IP_LEARN_ADRESS__ "ifconfig.me/all"

// Yanıt Tutmak İçin Yapı
typedef struct MemoryStore
{
    char* memory; // bellek
    size_t size; // boyut
} MemoryStore;

// Fonksiyon Prototip
size_t write_memory
(
    void* contents, // içerik
    size_t size, // boyut
    size_t nmemb, // bellek boyutu
    MemoryStore* memoryPtr // bellek depolayıcı işaretçisi
);

// main
int main(void)
{
    // cURL
    CURL* curl; // nesne
    CURLcode response; // yanıt

    // bellek depolaması içn yapı
    MemoryStore store =
    {
        .memory = NULL, // boş alan
        .size = 0 // boyut 0
    };

    // küresel curl başlat
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    
    // nesneyi başlat
    curl = curl_easy_init();

    // başarısız olmuşsa temizle ve sonlandır
    if(!curl)
    {
        curl_global_cleanup(); // temizle
        return 0; // programı sonlandır
    }

    // url adresini ayarla
    curl_easy_setopt(curl, CURLOPT_URL, __IP_LEARN_ADRESS__);

    // yanıtı saklamak için ayarla
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory); // depolama fonksiyonu
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&store); // depolanacak nesne

    // cURL isteği gönder
    response = curl_easy_perform(curl);

    // istek durumuna göre yanıt
    switch(response)
    {
        // başarılı
        case CURLE_OK:
            printf("%s\n", store.memory);
            break;
        // hata
        default:
            printf("Failed\n");
    }

    // curl bağlantı nesnesini temizleme
    curl_easy_cleanup(curl);

    // depolamak için ayrılan belleği temizle
    store.memory != NULL ? free(store.memory) : NULL;

    // temizle
    curl_global_cleanup();

    // program sonu
    return 0;
}

// Yanıt verisini bellek tutmak
size_t write_memory
(
    void* contents, // içerik
    size_t size, // boyut
    size_t nmemb, // bellek boyutu
    MemoryStore* memoryPtr // bellek depolayıcı işaretçisi
)
{
    // gerçek boyutunu hesaplamak
    size_t realsize = size * nmemb;

    // bellek veri depolama alanını yeniden boyutlandırmak
    memoryPtr->memory = realloc(memoryPtr->memory, memoryPtr->size + realsize + 1);

    // boyutlandırma başarısız ise hata dönsün
    if(memoryPtr->memory == NULL)
    {
        printf("\n%s\n", "[WRITE_MEMORY] Memory Not Allocated!");
        return 0; // boş boyut dönsün
    }

    // veriyi kopyala
    memcpy(&(memoryPtr->memory[memoryPtr->size]), contents, realsize); // veriyi kopyala

    memoryPtr->size += realsize; // boyutu güncelle
    memoryPtr->memory[memoryPtr->size] = '\0'; // null karakterle sonlandır

    return realsize; // gerçek boyutu döndür
}