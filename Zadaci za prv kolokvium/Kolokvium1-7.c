#include <stdio.h>
#include <string.h>

struct Vozenje{
char ime[100];
int traenje;
float cena;
int daliPopust;
};

typedef struct Vozenje Vozenje;

struct ZabavenPark{
char ime[100];
char lokacija[100];
Vozenje niza[100];
int n;
};

typedef struct ZabavenPark ZabavenPark;

void pecati(ZabavenPark * niza, int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
    printf("%s %s\n",niza[i].ime,niza[i].lokacija);
    for(j=0;j<niza[i].n;j++)
    {

    printf("%s %d %.2f\n",niza[i].niza[j].ime,niza[i].niza[j].traenje,niza[i].niza[j].cena);
    }
    }
}

void najdobar_park(ZabavenPark * niza, int n)
{
    int i,j, maxI=0, maxV=0,maxVremetraenje= 0;

    for(i=0;i<n;i++)
    {
        int count=0;
        int vreme=0;
        for(j=0;j<niza[i].n;j++)
        {
            if(niza[i].niza[j].daliPopust==1)
                count++;
            vreme+= niza[i].niza[j].traenje;
        }
        if(count>maxV)
        {
            maxV = count;
            maxI = i;
            maxVremetraenje = vreme;
        }
        else if(count==maxV&&vreme>maxVremetraenje)
        {
            maxI = i;
            maxVremetraenje = vreme;
        }
    }
    printf("Najdobar park: %s %s\n",niza[maxI].ime,niza[maxI].lokacija);
}

int main()
{
	int i, j, n, broj;
	//kreiraj niza od maksimum 100 zabavni parkovi
	ZabavenPark ff[100];
	scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
		//ime na festivalot
		scanf("%s", ff[i].ime);
        //mesto
		scanf("%s", ff[i].lokacija);
		//broj na filmovi
		scanf("%d", &ff[i].n);

		for (j = 0; j < ff[i].n; j++){
			scanf("%s", ff[i].niza[j].ime);  			/* Ime na filmot */
			scanf("%d", &ff[i].niza[j].traenje); 		/* Vremetraenje   */
			scanf("%f", &ff[i].niza[j].cena); 	/* Cena */
            scanf("%d", &ff[i].niza[j].daliPopust);	/* Popust */

		}


			}
    pecati(ff,n);
    najdobar_park(ff,n);

	return 0;
}
