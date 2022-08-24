#include<stdio.h>

typedef struct Pacient{
    char ime[100];
    int zdrastveno,
    pregledi;
}P;
typedef struct MaticenDoktor{
    char ime[100];
    int br_pac;
    P niza[200];
    float cena;
}doktor;

void najuspesen_doktor(doktor *d, int num){
    float maxCena = 0; int maxPregledi = 0,pos =0;
    for(int i=0;i<num;i++){
        int imaZdrastveno = 0, nemaZdrastveno = 0;
        for(int j=0;j<d[i].br_pac;j++){
            d[i].niza[j].zdrastveno?
            (imaZdrastveno+=d[i].niza[j].pregledi):(nemaZdrastveno+=d[i].niza[j].pregledi); }
            (maxCena <= (float)nemaZdrastveno * d[i].cena) && (maxPregledi < (imaZdrastveno + nemaZdrastveno))
            ?maxCena = (float) nemaZdrastveno * d[i].cena, maxPregledi = imaZdrastveno + nemaZdrastveno,pos = i:0;
    }
    printf("%s %.2f %d",d[pos].ime,maxCena,maxPregledi);
}

int main()
{
	int n, broj;
	doktor md[200];
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
	    scanf("%s %d %f", &md[i].ime, &md[i].br_pac, &md[i].cena);
		for (int j = 0; j < md[i].br_pac; j++){
		    scanf("%s %d %d", &md[i].niza[j].ime, &md[i].niza[j].zdrastveno, &md[i].niza[j].pregledi); } }
	najuspesen_doktor(md, n);
	return 0;
}
