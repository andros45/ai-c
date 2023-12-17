#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Öppna filen för läsning
    FILE *file = fopen("filen", "r");

    // Kontrollera om filen kunde öppnas
    if (file == NULL) {
        perror("Kunde inte öppna filen");
        return 1;
    }

    // Buffert för att lagra varje rad
    char *line = NULL;
    size_t len = 0;  // För att hålla reda på längden av inlästa raden

    // Läs varje rad i filen
    while (getline(&line, &len, file) != -1) {
        int firstDigit, lastDigit;
        char *ptr = line;

        // Använd sscanf i en loop för att extrahera siffror från raden
        while (sscanf(ptr, "%1d%*[^0-9]%1d", &firstDigit, &lastDigit) == 2) {
            // Visa de två siffrorna för varje par
            printf("Första siffran: %d, Sista siffran: %d\n", firstDigit, lastDigit);
            
            // Flytta pekaren till nästa potentiella sifferpar
            ptr += strcspn(ptr, "0123456789");  // Hitta nästa siffra i strängen
            ptr += strspn(ptr, "0123456789");   // Hoppa över siffrorna
        }
    }

    // Frigör minnet för inlästa rader
    free(line);

    // Stäng filen
    fclose(file);

    return 0;
}
