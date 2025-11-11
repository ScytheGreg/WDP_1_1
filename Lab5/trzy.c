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
                /*ind_pierwszego*/ poczatek_grupy,
                /*ind_ostatniego*/ i
            };
            assert(0 <= poczatek_grupy && poczatek_grupy < n);
            assert(0 <= i && i < n);
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

int maks_z_min(grupa_moteli a, grupa_moteli b, grupa_moteli c, motel motele[]){

    int lewy = motele[a.ind_pierwszego].odl_od_pocz;
    int prawy = motele[c.ind_ostatniego].odl_od_pocz;

    int Maks = 0;

    for(int i = b.ind_pierwszego ; i <= b.ind_ostatniego ; ++i){
        assert(&motele[i] != NULL);
        int srodek = motele[i].odl_od_pocz;
        Maks = max(Maks, min(srodek - lewy, prawy - srodek));
    }
    return Maks;
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

int znajdz_3_rozna_siec(grupa_moteli grupy[], int ilosc_grup, int zmiana, int pierwszy){
    int siec_1 = grupy[pierwszy].nr_sieci;
    int siec_2 = grupy[pierwszy + zmiana].nr_sieci;
    int siec_3 = 0;
    int ind_siec_3 = pierwszy + zmiana;
    while(siec_3 == 0){
        ind_siec_3 += zmiana;
        assert(0 <= ind_siec_3 && ind_siec_3 < ilosc_grup);
        nowa_siec(&siec_1, &siec_2, &siec_3, grupy[ind_siec_3].nr_sieci);
    }
    return ind_siec_3;
}

int poszukaj_pomiedzy(const int ind_pocz, const int ind_kon, motel motele[], grupa_moteli grupy[]){

    //printf("Szukamy pomiędzy: %d, %d\n", ind_pocz, ind_kon);

    grupa_moteli a = grupy[ind_pocz];
    grupa_moteli c = grupy[ind_kon];

    if(a.nr_sieci == c.nr_sieci)
        return 0;

    int wynik = 0;

    for(int i = ind_pocz + 1 ; i < ind_kon ; ++i){
        grupa_moteli b = grupy[i];
        if(a.nr_sieci != b.nr_sieci && c.nr_sieci != b.nr_sieci){
            //int _ = max(wynik, maks_z_min(a, b, c, motele));
            //printf("To wyszło dla indeksu grupy %d: %d\n", i, _);
            wynik = max(wynik, maks_z_min(a, b, c, motele));
        }
    }
    return wynik;
}

int najdalsza(motel motele[], grupa_moteli grupy[], int ilosc_grup){

    assert(ilosc_grup >= 3);

    int ind_3_pocz = znajdz_3_rozna_siec(grupy, ilosc_grup, 1, 0);
    int ind_3_kon = znajdz_3_rozna_siec(grupy, ilosc_grup, -1, ilosc_grup - 1);

    const int pocz_ind[3] = {0, 1, ind_3_pocz};
    const int kon_ind[3] = {ilosc_grup - 1, ilosc_grup - 2, ind_3_kon};

    // printf("ind_3_pocz: %d\n", ind_3_pocz);
    // printf("ind_3_kon: %d \n", ind_3_kon);

    int wynik = 0;

    for(int i = 0 ; i < 9 ; i++){
        wynik = max(wynik, poszukaj_pomiedzy(pocz_ind[i % 3], kon_ind[i / 3], motele, grupy));
        //printf("Wynik po %d: %d\n", i, wynik);
    }

    return wynik;
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

    printf("%d %d\n", najblizsa(motele, grupy, ilosc_grup), najdalsza(motele, grupy, ilosc_grup));
    return 0;
}