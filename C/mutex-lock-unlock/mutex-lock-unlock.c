// Slavnem @2024-09-13
// Mutex (Lock - Unlock)

/*
    GENEL AMAÇ:
    
    Thread kullanırken asıl amaç tek bir sayıyı
    farklı çekirdekler ile saymak değildir çünkü
    bu saçmadır. Bir ağırlığı tek elle kaldırmak
    yerine sürekli iki el arasında değiştirmek
    hem iki el için gereksiz güç harcamak hem de
    aşırı zaman kaybı demektir. Bunun yerine şu tarz
    bir örnek çok daha iyi olacaktır...

    Örnek:
    Bir elinde ağırlık kaldırırken diğer eli ile
    ocaktaki yemeği kontrol eden bir sporcuyu düşünelim.
    Sporcu bu işi yaparken ağırlık kaldırdığı eli ile
    1 thread ağırlık ile ilgilenirken diğer thread yemek
    ile ilgilenir ve bu sayede 2 thread ile işlemi hızlıca
    yapmış oluruz. Aksi senaryoyu düşünelim.

    Örnek:
    Bir elinde ağırlık kaldırıp diğer eli olmayan bir sporcu
    düşünelim. Bu sporcu eli ile ağırlık kaldırırken yemek ile
    ilgilenemez ve yemek olması gerekenden daha çok ocakta kalır.
    Sporcu eğer ara sıra ağırlık kaldırmayı bırakıp yemeğe bakmayı
    denerse, bu sefer de ağırlık bırakıp yemek ile ilgilenmeye çalışırken
    geçen süre ise ek gecikme olur çünkü anında ağrılık bırakılıp yemeğe
    bakılamaz, küçük bir gecikme yaşanır. Bir elle ağırlık
    kaldırıp biktikten sonra yemeğe bakmaktan daha yavaşdır ama daha güvenlidir.
    Aksi halde tek elle ağırlık kaldırma bittiken sonra yemeğe bakılabilir.

    Bu tarz olayları önlemek için "multi threading" vardır. Yani iki kol veya daha
    fazla kol ile birbirinden farklı işleri kollara ayrı ayrı şekilde ayırıp
    hem aynı anda daha fazla iş yapılması sağlanırır hem de zamandan
    tasaruf edilir. Aynı iş için kullanmak ise tam tersine neden olur.
    Hem daha az iş yapılır hem de zamandan kayıp yapılır.
*/

// Kütüphaneler
#include <stdio.h> // standart giriş/çıkış
#include <stdint.h> // standart sayı türleri
#include <pthread.h> // thread kütüphane

#define BIG 1000000000UL // en büyük sayı sınırı

/*
    _Atomic kullanarak thread ile yaptığımız saymanın
    basit sayılar ile işlem yapılırken normal sayı
    arttırma durumuna göre hareket etmesini sağlayabiliriz
    fakat daha önemli işlemlerde _Atomic kullanmak işe yaramaz

    Örnek:
    static _Atomic uint32_t counter = 0; // sayaç
*/

static uint32_t counter = 0; // sayaç

/*
    Mutex Kilidi
    
    thread'lerin birbiri ile yarışırcasına aynı anda
    işlem yapıp doğru sayıyı vermemesini çözmek için
    o anda sadece 1 işlem yapıp sonra diğer işlem yapılmasına
    izin veren mutex kilidini kullanacağız
*/
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// count_to_big
void * count_to_big(void *arg)
{
    for(uint32_t i = 0; i < BIG; i++)
    {
        pthread_mutex_lock(&lock); // mutex kilitle
        counter++; // genel sayaç sayısı
        pthread_mutex_unlock(&lock); // mutex kilit aç
    }

    return NULL; // boş dönsün
}

// main
int main(void)
{
    // thread nesnesi
    pthread_t t;

    // thread oluşturma
    pthread_create(&t, NULL, count_to_big, NULL);

    // sayaçlar ile ana sayıyı arttırma
    count_to_big(NULL);
    
    // thread bekleme
    pthread_join(t, NULL);

    // bilgi çıktısı
    printf("Sayac: %u\n", counter);

    return 0;
}