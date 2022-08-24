#include <stdio.h>
struct Proizvod{
    char Ime[15];
    float cena;
    float kolicina;
};
typedef struct Proizvod proizvod;

int main(){
    int n;
    float vkupno=0;
    scanf("%d",&n);
    proizvod p[20];
    for(int i=0;i<n;i++){
       scanf("%s %f %f",&p[i].Ime,&p[i].cena,&p[i].kolicina);
       vkupno=vkupno+p[i].cena*p[i].kolicina;
       printf("%d. %s\t%.2f x %.1f = %.2f\n",i+1,p[i].Ime,p[i].cena,p[i].kolicina,p[i].cena*p[i].kolicina);
    }
    printf("Total: %.2f",vkupno);
return 0;
}
