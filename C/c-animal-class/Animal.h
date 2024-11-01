// Slavnem @2024-11-01
// Animal Sınıfı
#ifndef ANIMAL_H
#define ANIMAL_H

// Sınıf Değişken Erişim Türleri
#define public // genel
#define private static // gizli
#define protected const // korumalı

// Sınıf Yapısı
typedef struct Animal Animal;

// Fonksiyon Türü
typedef char boolean;

// Doğru, Yanlış Değerleri
#define FALSE 0
#define TRUE 1

// Cinsiyet Değerleri
#define MALE "Male"
#define FEMALE "Female"

// Doğru yanlış kontrolü
#define isTrue(x) (x > 0)

// Fonksiyon Prototipler
Animal* // Kurucu
animal_create
(
    const char* const arg_animal_name, // adı
    const int arg_animal_age, // yaşı
    const float arg_animal_weight, // ağırlık
    const boolean arg_animal_gender_male // erkek mi dişi mi
);

Animal* // Yıkıcı
animal_delete
(
    Animal** arg_animalptr
);

protected const char* const
getAnimalName // Adı Getir
(
    const Animal* const arg_animalptr
);

protected const int
getAnimalAge // Yaşı Getir
(
    const Animal* const arg_animalptr
);

protected const float
getAnimalWeight // Ağırlığı Getir
(
    const Animal* const arg_animalptr
);

protected const char* const
getAnimalGender // Cinsiyeti Getir
(
    const Animal* const arg_animalptr
);

public void
setAnimalAge // Yaş Ata
(
    Animal* arg_animal,
    const int arg_age
);

public void
setAnimalWeight // Ağırlık Ata
(
    Animal* arg_animal,
    const float arg_weight
);

protected const unsigned long int
getAnimalCount // Hayvan Sayısını Getir
(
    void
);

protected void
printAnimal // Hayvan Bilgisi Çıktı
(
    const Animal* const arg_animalptr
);

#endif // ANIMAL_H