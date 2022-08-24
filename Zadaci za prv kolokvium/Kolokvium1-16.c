#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

struct RabotnaNedela{
    int casovi[5];
    int brNed;
};

typedef struct RabotnaNedela RN;

struct Rabotnik{
    char ime[50];
    RN nedeli[4];
};

typedef struct Rabotnik R;

int maxNedela(R *r){
    int max=0 , tmp=0;
    for(int i=0; i<4; i++){
        int sum=0;
        for(int j=0; j<5; j++){
            sum+=r->nedeli[i].casovi[j];
        }
        if(sum>max){
            max=sum;
            tmp=i+1;
        }
    }
    return tmp;
}
void table(R *r, int n){
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0; i<n; i++){
        int total=0;
        printf("%s\t",r[i].ime);
        for(int j=0; j<4; j++){
            int sum=0;
            for(int k=0; k<5; k++){
                sum+=r[i].nedeli[j].casovi[k];
            }
            printf("%d\t",sum);
            total+=sum;
        }
        printf("%d\n",total);
    }
}
int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
