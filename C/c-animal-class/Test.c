// Slavnem @2024-11-01
// Test

// Kütüphaneler
#include <stdio.h>
#include "Animal.h"

// main
int main(void)
{
    Animal* catptr = animal_create("Pati", 3, 4.5, TRUE);
    printAnimal(catptr);

    Animal* dogptr = animal_create("Max", 4, 15.5, FALSE);
    printAnimal(dogptr);

    animal_delete(&dogptr);
    // printAnimal(dogptr); !ERROR!

    printAnimal(catptr);
    animal_delete(&catptr);

    printf("Animal Count: %lu\n", getAnimalCount());
}