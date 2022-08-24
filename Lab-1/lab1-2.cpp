#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tocka{
    float x, y;
} tocka;

typedef struct otsecka{
    tocka tocka1;
    tocka tocka2;
} otsecka;

int se_secat (otsecka o1, otsecka o2){
    double kPravec1 = (o1.tocka1.y-o1.tocka2.y)/(o1.tocka1.x-o1.tocka2.x), kPravec2= (o2.tocka1.y-o2.tocka1.y)/(o2.tocka1.x-o2.tocka2.x);
    if(kPravec1 == kPravec2)
    {
        return 0;
    }
    else if(o2.tocka1.x > o1.tocka1.x && o2.tocka2.x > o1.tocka1.x && o2.tocka2.x > o1.tocka1.x && o2.tocka2.x > o1.tocka2.x)
    {
        return 0;
    }
    else if(o1.tocka1.x > o2.tocka1.x && o1.tocka2.x > o2.tocka1.x && o1.tocka2.x > o2.tocka1.x && o1.tocka2.x > o2.tocka2.x)
    {
        return 0;
    }
    else if(o2.tocka1.y > o1.tocka1.y && o2.tocka2.y > o1.tocka1.y && o2.tocka2.y > o1.tocka1.y && o2.tocka2.y > o1.tocka2.y)
    {
        return 0;
    }
    else if(o1.tocka1.y > o2.tocka1.y && o1.tocka2.y > o2.tocka1.y && o1.tocka2.y > o2.tocka1.y && o1.tocka2.y > o2.tocka2.y)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    float x1, y1, x2, y2;
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t1 = { x1, y1 };
    tocka t2 = { x2, y2 };
    otsecka o1 = { t1, t2 };
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t3 = { x1, y1 };
    tocka t4 = { x2, y2 };
    otsecka o2 = { t3, t4 };
    printf("%d\n", se_secat(o1, o2));
    return 0;
}
