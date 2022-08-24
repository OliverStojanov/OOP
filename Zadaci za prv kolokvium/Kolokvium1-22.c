#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Proizvod{
    char kod[20];
    int cena, kolicina;
} Proizvod;

typedef struct Narachka{
    char ime[15];
    Proizvod proizvodi[10];
    int kolicinaProizovdi[10];
    int brojProizvodi;
} Narachka;

void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void pecatiFaktura (Narachka n){
    printf("Faktura za %s\n", n.ime);
    for(int i = 0; i < n.brojProizvodi; i++){
        if(n.proizvodi[i].kolicina >= n.kolicinaProizovdi[i]){
            n.proizvodi[i].kolicina -= n.kolicinaProizovdi[i];
        }
        else{
            printf("Fakturata ne moze da se izgotvi");
            return 0;
        }
    }

    for(int i = 0; i < n.brojProizvodi; i++){
        for(int j = 0; j < n.brojProizvodi - 1; j++){
            if(strcmp(n.proizvodi[j].kod, n.proizvodi[j + 1].kod) > 0){
                char temp[15];
                strcpy(temp, n.proizvodi[j].kod);
                strcpy(n.proizvodi[j].kod, n.proizvodi[j + 1].kod);
                strcpy(n.proizvodi[j + 1].kod, temp);
                swap(&n.kolicinaProizovdi[j], &n.kolicinaProizovdi[j + 1]);
                swap(&n.proizvodi[j].cena, &n.proizvodi[j + 1].cena);
            }
        }
    }

    int vkupnaCena = 0;

    for(int i = 0; i < n.brojProizvodi; i++){
        printf("%s %d %d %d\n", n.proizvodi[i].kod, n.proizvodi[i].cena,  n.kolicinaProizovdi[i], n.proizvodi[i].cena * n.kolicinaProizovdi[i]);
        vkupnaCena += n.proizvodi[i].cena *= n.kolicinaProizovdi[i];
    }
    printf("Vkupnata suma na fakturata e %d", vkupnaCena);
}

int main(){
    Narachka narachka;

    scanf("%s", narachka.ime);
    scanf("%d", &narachka.brojProizvodi);

    for (int i = 0; i < narachka.brojProizvodi; ++i){
        scanf("%s %d %d", narachka.proizvodi[i].kod, &narachka.proizvodi[i].cena,  &narachka.proizvodi[i].kolicina);
    }
    for (int i = 0; i < narachka.brojProizvodi; i++){
        scanf("%d", &narachka.kolicinaProizovdi[i]);
    }

    pecatiFaktura(narachka);

    return 0;
}
