#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
const unsigned eps = 7; // Margines rozmiaru tablicy motele[]

typedef struct motel{
    int nr_sieci;
    int odl_od_pocz;
} motel;

typedef struct grupa_moteli{
    int nr_sieci;
    int rozmiar;
    int ind_pierwszego;
    int ind_ostatniego;
} grupa_moteli;


void wczytaj_dane(int* n, motel* motele[] ){
    if(scanf("%d", &(*n)) == 0)
        printf("Nie wczytano n\n");

    *motele = (motel*) malloc (((unsigned)(*n)  + eps)* sizeof(motel));
    for(int i = 0 ; i < *n ; ++i){
        motel wczytaj;
        if(scanf("%d %d", &wczytaj.nr_sieci, &wczytaj.odl_od_pocz) == 0)
            printf("Nie wczytano motelu nr %d\n", i);
        (*motele)[i] = wczytaj;
    }
}

void nowa_siec(int* a, int* b, int* c, int nr_sieci){
    if(*a == 0)
        *a = nr_sieci;
    else if(*a != nr_sieci && *b == 0)
        *b = nr_sieci;
    else if(*a != nr_sieci && *b != nr_sieci && *c == 0)
        *c = nr_sieci;
}

bool pogrupuj_motele(int n, motel motele[], grupa_moteli* pogrupowane_motele[], int* ilosc_grup){

    assert(n > 0);

    *pogrupowane_motele = (grupa_moteli*) malloc ((unsigned) n * sizeof(grupa_moteli));
    *ilosc_grup = 0;

    int siec_1 = 0, siec_2 = 0, siec_3 = 0;

    int poczatek_grupy = 0;
    motel zero = {0, 0};
    motele[n] = zero; // Motel za ostatnim z innej grupy

    for(int i = 0 ; i < n  ; ++i){
        nowa_siec(&siec_1, &siec_2, &siec_3, motele[i].nr_sieci);

        if(motele[i].nr_sieci != motele[i + 1].nr_sieci){
            grupa_moteli grupa = {
                /*nr_sieci*/ motele[i].nr_sieci,
                /*rozmiar*/ i - poczatek_grupy + 1,
                /*ind_pierwszego*/ poczatek_grupy,
                /*ind_ostatniego*/ i
            };
            assert(*ilosc_grup < n);
            (*pogrupowane_motele)[*ilosc_grup] = grupa;
            (*ilosc_grup)++;
            poczatek_grupy = i + 1;
        }
    }
    //Czyścimy pamięć
    grupa_moteli* tmp = (grupa_moteli*) realloc(*pogrupowane_motele, (unsigned) *ilosc_grup * sizeof(grupa_moteli));
    if(tmp != NULL)
        *pogrupowane_motele = tmp;

    return siec_3 != 0;
}

int min(int a, int b){
    if( a > b)
        return b;
    return a;
}

int max(int a, int b){
    if(a >= b)
        return a;
    return b;
}

int min_z_maks(grupa_moteli a, grupa_moteli b, grupa_moteli c, motel motele[]){

    if(a.nr_sieci == c.nr_sieci)
        return INT_MAX;
    
    int lewy = motele[a.ind_ostatniego].odl_od_pocz;
    int prawy = motele[c.ind_pierwszego].odl_od_pocz;

    int Min = INT_MAX;

    for(int i = b.ind_pierwszego ; i <= b.ind_ostatniego ; ++i){
        int srodek = motele[i].odl_od_pocz;
        Min = min(Min, max(srodek - lewy, prawy - srodek));
        //printf("i: %d, Min: %d\n", i, Min);
    }
    return Min;
}

int najblizsa(motel motele[], grupa_moteli grupy[], int ilosc_grup){

    int wynik = INT_MAX;
    //Przeszukaj_po_trzy_grupy
    // Jeżeli istnieją trzy grupy o parami różnych sieciach, to będą istiały trzy kolejne grupy o parami różnych sieciach
    // ,wśród których jest miniumum.
    for(int i = 0 ; i + 2 < ilosc_grup ; ++i){
        wynik = min(wynik, min_z_maks(grupy[i], grupy[i + 1], grupy[i + 2], motele));
    }

    return wynik;
}

int najdalsza(int n, motel motele[], grupa_moteli grupy[], int ilosc_grup){
    return motele[n - 1].odl_od_pocz + motele[grupy[ilosc_grup - 1].ind_pierwszego].odl_od_pocz;
}

int main(){
    int n;
    motel* motele;
    wczytaj_dane(&n, &motele);

    grupa_moteli* grupy;
    int ilosc_grup;
    if(pogrupuj_motele(n, motele , &grupy, &ilosc_grup) == false){
        printf("0 0\n");
        return 0;
    }

    //printf("Ilosc grup: %d\n", ilosc_grup);


    printf("%d %d\n", najblizsa(motele, grupy, ilosc_grup), najdalsza(n, motele, grupy, ilosc_grup));
    return 0;
}