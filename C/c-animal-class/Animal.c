// Slavnem @2024-11-01
// Animal Sınıfı İşlemleri

// Kütüphaneler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Animal.h"

// Private Fonksiyon Prototip
private void setAnimalName (
    Animal* arg_animal,
    const unsigned long int arg_animal_name_size,
    const char* const arg_name
);

private void setAnimalGender (
    Animal* arg_animal,
    const boolean arg_gender_male
);

private void setAnimalCount(
    const boolean arg_increase
);

// Sınıf Yapısı
typedef struct Animal
{
    public char name[20]; // ad
    public boolean gender; // cinsiyet (erkek)
    public int age; // yaş
    public float weight; // ağırlık
} Animal;

// Hayvan Miktar Sayacı
private unsigned long int animal_counter = 0;

// Fonksiyon Türü
typedef char boolean;

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
)
{
    // yeni obje oluştursun
    Animal* animalptr = (Animal*)malloc(sizeof(Animal));

    // obje başarıyla oluştuysa değer ataması yapsın
    if(animalptr)
    {
        // değerleri atasın
        setAnimalName(animalptr, sizeof(animalptr->name), arg_animal_name);
        setAnimalAge(animalptr, arg_animal_age);
        setAnimalWeight(animalptr, arg_animal_weight);
        setAnimalGender(animalptr, arg_animal_gender_male);

        // hayvan sayacını 1 arttırsın
        setAnimalCount(TRUE);
    }

    // yeni oluşturulan objeyi döndürsün
    return animalptr;
}

const boolean // Yıkıcı
animal_delete
(
    Animal** arg_animalptr
)
{
    // boşsa otomatik kendisini döndürsün
    if(!*arg_animalptr)
        return FALSE;

    // belleği temizlesin
    free((Animal*)*arg_animalptr);

    // bellek işaretçisini boş göstersin
    *arg_animalptr = (Animal*)NULL;

    // temizlenmediyse false dönücek
    if(*arg_animalptr != NULL)
        return FALSE;

    // başarıyla temizlendi
    setAnimalCount(FALSE); // hayvan sayısını 1 azalt
    return TRUE;
}

public const char* const
getAnimalName // Adı Getir
(
    const Animal* const arg_animalptr
)
{
    return arg_animalptr->name;
}

public const int
getAnimalAge // Yaşı Getir
(
    const Animal* const arg_animalptr
)
{
    return arg_animalptr->age;
}

public const float
getAnimalWeight // Ağırlığı Getir
(
    const Animal* const arg_animalptr
)
{
    return arg_animalptr->weight;
}

public const char* const
getAnimalGender // Cinsiyeti Getir
(
    const Animal* const arg_animalptr
)
{
    // erkek (TRUE), dişi (FALSE)
    return isTrue(arg_animalptr->gender) ?
        MALE
        : FEMALE;
}

public void
setAnimalAge // Yaş Ata
(
    Animal* arg_animalptr,
    const int arg_age
)
{
    // geçersiz yaş değeri
    if(arg_age < 1)
        return;

    arg_animalptr->age = arg_age;
}

public void
setAnimalWeight // Ağırlık Ata
(
    Animal* arg_animalptr,
    const float arg_weight
)
{
    // geçersiz ağırlık değeri
    if(arg_weight < 1.0)
        return;

    arg_animalptr->weight = arg_weight;
}

public const unsigned long int
getAnimalCount // Hayvan Sayısını Getir
(
    void
)
{
    return animal_counter;
}

// PROTECTED
protected void
printAnimal // Hayvan Bilgisi Çıktı
(
    const Animal* const arg_animalptr
)
{    
    printf("%s: %s\n%s: %d\n%s: %.1f %s\n%s: %s\n%s: %lu\n\n",
        "Name", (arg_animalptr->name),
        "Age", (arg_animalptr->age),
        "Weight", (arg_animalptr->weight), " Kg",
        "Gender", (isTrue(arg_animalptr->gender) ? MALE : FEMALE),
        "Animals: ", (animal_counter)
    );
}

// PRIVATE
private void
setAnimalName // Adı Ata
(
    Animal* arg_animal,
    const unsigned long int arg_animal_name_size,
    const char* const arg_name
)
{
    // geçersiz isim uzunluğu
    if(strlen(arg_name) < 3)
        return;

    // değer ata
    snprintf(arg_animal->name, arg_animal_name_size - 1, "%s", arg_name);
}

private void
setAnimalGender // Cinsiyet Ata
(
    Animal* arg_animal,
    const boolean arg_gender_male
)
{
    // erkekse true, değilse false
    arg_animal->gender = isTrue(arg_gender_male);
}

private void
setAnimalCount(const boolean arg_increase) // Sayaç Değeri Arttır, Azalt
{
    // sayacı 1 arttır
    if(isTrue(arg_increase))
    {
        ++animal_counter;
        return;
    }

    // 1 azalt
    --animal_counter;
}