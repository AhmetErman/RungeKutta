#include <stdio.h>
#include <math.h>

#define MaxTerimSayisi 20

typedef struct Polinom{
    int terim;
    double katsayi[MaxTerimSayisi];
    int us1[MaxTerimSayisi];
    int us2[MaxTerimSayisi];
}poly;

void fonksiyonIn(poly *poly);
double fonksiyonOut(poly *poly, double x, double y);
void fonksiyonPrint(poly *poly);
double rk(poly *fxy, double x, double y, double h);




int main(){

    poly fxy;
    double x, y, z, h, sum;
    int i,n;

    //inputlar
    printf("      Inputlar:");
    printf("\n-------------------------------------------\n");

    fonksiyonIn(&fxy);
    printf("Girdiginiz fonksiyon su sekildedir: ");
    fonksiyonPrint(&fxy);

    printf("\n-------------------------------------------\n");

    printf("\nx0 degerini giriniz:\n");
    scanf(" %lf", &x);
//    x = 0;
    printf("y0 degerini giriniz:\n");
    scanf(" %lf", &y);
//    y = 1;
    printf("y(x) fonksiyonu icin hangi x degerine gittigimizi giriniz: \n");
    scanf(" %lf", &z);
//    z = 0.2;
    printf("h degerini giriniz:\n");
    scanf(" %lf", &h);
//    h = 0.1;


    printf("\n-------------------------------------------\n");
    printf("      Iterasyonlar\n");
    n = (z-x)/h;
    for (i = 0; i < n; i++) {
        y = rk(&fxy,x,y,h);
        x += h;

        printf("%d. Iteration : y(%.4lf) = %lf\n",i+1, x, y);
    }

    printf("\n-------------------------------------------\n");
    printf("\nYaklasik sonuc = %lf", y);


    return 0;
}

void fonksiyonIn(poly *poly){

    int temp,i;
    double kat;
    char xy[2];

    printf("Lutfen fonksiyonun terim sayisini giriniz: ");
    scanf(" %d",&temp);

    poly->terim = temp;
    printf("TerimSayisi = %d \n",poly->terim);

    //katsayılar
    for(i=0; i<poly->terim; i++){

        printf("Lutfen fonksiyonun %d. teriminin katsayisini giriniz: \n",i+1);

        scanf(" %lf",&kat);
        poly->katsayi[i] = kat;
    }

    //üsler
    for(i=0; i<poly->terim; i++){

        printf("Bu terim hangi formatta (secenekler: \"x\", \"y\", \"xy\")\n");
        scanf(" %s",xy);

        if(xy[0] == 'x'){
            poly->us2[i] = 0;

            printf("Lutfen fonksiyonun %d. teriminin x degiskeninin ussunu giriniz: \n",i+1);
            scanf(" %d",&temp);

            poly->us1[i] = temp;

            if(xy[1] == 'y'){
                printf("Lutfen fonksiyonun %d. teriminin y degiskeninin ussunu giriniz: \n",i+1);
                scanf(" %d",&temp);

                poly->us2[i] = temp;
            }

        }
        else if(xy[0] == 'y'){
            poly->us1[i] = 0;

            printf("Lutfen fonksiyonun %d. teriminin y degiskeninin ussunu giriniz: \n",i+1);
            scanf(" %d",&temp);

            poly->us2[i] = temp;

        }
    }

//  deneme fonksiyonu:
//
//    poly->terim = 1;
//    poly->katsayi[0] = 1;
//    poly->us[0] = 2;

    //yazdır
}

void fonksiyonPrint(poly *poly){
    int i;

    for(i=0; i<poly->terim; i++){

        //üslerine göre yazdır
        if(poly->katsayi[i] > 0){
            // +

            if(i == 0){
                if(poly->us1[i] !=0 && poly->us2[i] !=0)
                    printf("%.2lf*x^%d*y^%d ", poly->katsayi[i] ,poly->us1[i] ,poly->us2[i]);
                else if(poly->us1[i] !=0)
                    printf("%.2lf*x^%d ",poly->katsayi[i],poly->us1[i]);
                else if(poly->us2[i] !=0)
                    printf("%.2lf*y^%d ",poly->katsayi[i],poly->us2[i]);
                else
                    printf("%.2lf ",poly->katsayi[i]);
            }
            else{
                // ayrı ayrı x, y, xy şeklinde yazdırma
                if(poly->us1[i] !=0 && poly->us2[i] !=0)
                    printf("+%.2lf*x^%d*y^%d ", poly->katsayi[i] ,poly->us1[i] ,poly->us2[i]);
                else if(poly->us1[i] !=0)
                    printf("+%.2lf*x^%d ",poly->katsayi[i],poly->us1[i]);
                else if(poly->us2[i] !=0)
                    printf("+%.2lf*y^%d ",poly->katsayi[i],poly->us2[i]);
                else
                    printf("%.2lf ",poly->katsayi[i]);

            }
        }
        else if(poly->katsayi[i] < 0){
            // -

            if(poly->us1[i] !=0 && poly->us2[i] !=0)
                printf("%.2lf*x^%d*y^%d ", poly->katsayi[i], poly->us1[i], poly->us2[i]);
            else if (poly->us1[i] != 0)
                printf("%.2lf*x^%d ", poly->katsayi[i], poly->us1[i]);
            else if (poly->us2[i] != 0)
                printf("%.2lf*y^%d ", poly->katsayi[i], poly->us2[i]);
            else
                printf("%.2lf ",poly->katsayi[i]);

        }
    }
    printf("\n");
}

double fonksiyonOut(poly *poly,double x,double y){
    int i;
    double deger=0.0;

    for(i=0; i<poly->terim; i++){

        if(poly->us1[i] !=0 && poly->us2[i] !=0)
            deger += pow(x,poly->us1[i]) * pow(y,poly->us2[i]) * poly->katsayi[i];
        else if(poly->us1[i] !=0)
            deger += pow(x,poly->us1[i]) * poly->katsayi[i];
        else if(poly->us2[i] !=0)
            deger += pow(y,poly->us2[i]) * poly->katsayi[i];
        else
            deger += poly->katsayi[i];

        //deger += pow(x,(double)(poly.us[i]))*poly.katsayi[i];
    }
    return deger;
}

double rk(poly *fxy, double x, double y, double h){
    double k1, k2, k3, k4;

    /*k1 = hf(x0, y0)

    k2 = hf[x0 + (½)h, y0 + (½)k1]

    k3 = hf[x0 + (½)h, y0 + (½)k2]

    k4 = hf(x0 + h, y0 + k3)*/

    k1 = h * fonksiyonOut(fxy,x,y);
    k2 = h * fonksiyonOut(fxy,x+ h/2,y + k1/2); //(fonksiyonOut(px,x + h/2)  + fonksiyonOut(py,y + k1/2))
    k3 = h * fonksiyonOut(fxy,x+ h/2,y + k2/2); //(fonksiyonOut(px,x + h/2) + fonksiyonOut(py,y + k2/2));
    k4 = h * fonksiyonOut(fxy,x+ h,y + k3); //(fonksiyonOut(px,x + h) + fonksiyonOut(py,y + k3));

    return y + (k1 + 2*k2 + 2*k3 + k4)/6;
}

