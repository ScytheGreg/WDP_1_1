#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

void pogrupuj_motele(int n, motel motele[], grupa_moteli* pogrupowane_motele[], int* ilosc_grup){

    assert(n > 0);

    *pogrupowane_motele = (grupa_moteli*) malloc ((unsigned) n * sizeof(grupa_moteli));
    *ilosc_grup = 1;

    int poczatek_grupy = 0;
    motel zero = {0, 0};
    motele[n] = zero; // Motel za ostatnim z innej grupy

    for(int i = 0 ; i < n  ; ++i){
        if(motele[i].nr_sieci != motele[i + 1].nr_sieci){
            grupa_moteli grupa = {
                /*nr_sieci*/ motele[i].nr_sieci,
                /*rozmiar*/ i - poczatek_grupy + 1,
                /*ind_pierwszego*/ poczatek_grupy,
                /*ind_ostatniego*/ i
            };
            *pogrupowane_motele[*ilosc_grup - 1] = grupa;
            (*ilosc_grup)++;
            poczatek_grupy = i + 1;
        }
    }
    //Czyścimy pamięć
    grupa_moteli* tmp = (grupa_moteli*) realloc(*pogrupowane_motele, (unsigned) *ilosc_grup * sizeof(grupa_moteli));
    if(tmp != NULL)
        *pogrupowane_motele = tmp;
}

int najblizsa(int n, motel motele[]){

    grupa_moteli* pogrupowane_motele;
    int ilosc_grup;
    pogrupuj_motele(n, motele , &pogrupowane_motele, &ilosc_grup);
    return 0;
}

int najdalsza(int n, motel t[]){
    return t[n - 1].odl_od_pocz;
}

int main(){
    int n;
    motel* motele;
    wczytaj_dane(&n, &motele);

    printf("%d %d", najblizsa(n, motele), najdalsza(n, motele));
    return 0;
}