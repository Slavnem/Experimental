// Slavnem @2024-09-12
// Thread Oluşturma

// Kütüphaneler
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Test Amaçlı Fonksiyonlar
void* threadtest(void* arg)
{
    const char* msg = (const char*)arg;

    for(int i = 0; i < 10; i++)
    {
        sleep(2);
        printf("%d: %s\n", i+1, msg);
    }
}

void dongu(void)
{
    for(int i = 0; i < 5; i++)
    {
        sleep(1);
        printf("%d: Dongu\n", i+1);
    }
}

// main
int main(void)
{
    // thread nesnesi oluşturma
    pthread_t newthread;

    // mesaj
    const char* const msg1 = "Thread Mesaji!";

    // threadleri oluşturma
    pthread_create(&newthread, NULL, threadtest, (void*)msg1);

    // normal döngü
    dongu();

    // iş parçacıklarının bitmesini bekleme
    pthread_join(newthread, NULL);

    // son bildiri mesajı
    puts("\n* Tum Olaylar Sona Erdi *");

    return 0;
}