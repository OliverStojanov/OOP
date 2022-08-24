#include <stdio.h>
#include <string.h>

typedef struct Laptop{
    char firma[100];
    float size;
    int hasTouch, price;
}laptop;
typedef struct ITStore{
    char storeName[100],location[100];
    laptop arr[100];
    int num;
}its;

void print(its *a, int n)
{
    for(int i=0; i<n; i++){
        printf("%s %s\n",a[i].storeName, a[i].location);
        for(int j=0; j<a[i].num; j++){
            if(a[i].arr[j].size == (int)a[i].arr[j].size){
                printf("%s %d %d\n",a[i].arr[j].firma, (int)a[i].arr[j].size, a[i].arr[j].price);
            }else {
                printf("%s %.1f %d\n",a[i].arr[j].firma, a[i].arr[j].size, a[i].arr[j].price);
            }
        }
    }
}
void cheapest_store(its *a, int n)
{
    int min=0,pos=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<a[i].num; j++){
            if(a[i].arr[j].hasTouch == 1 && (min>a[i].arr[j].price || min == 0)){
                min = a[i].arr[j].price;
                pos = i;
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\nNajniskata cena iznesuva: %d",a[pos].storeName, a[pos].location,min);
}

int main()
{
    int n;
    scanf("%d", &n);
    its s[100];

    for(int i=0; i<n; i++){
        scanf("%s %s %d",s[i].storeName, s[i].location, &s[i].num);
        for(int j=0; j<s[i].num; j++){
            scanf("%s %f %d %d",s[i].arr[j].firma, &s[i].arr[j].size, &s[i].arr[j].hasTouch, &s[i].arr[j].price);
        }
    }
    print(s, n);
    cheapest_store(s, n);
    return 0;
}
