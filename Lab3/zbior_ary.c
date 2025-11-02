// Rozwiązanie zadania "Zbiory Arymetyczne" z Labów nr 3.
// Autorem rozwiazania jest Grzegorz Kaczmarek. mail: g.kaczmarek2@student.uw.edu.pl
// Z rozwiązania można korzystać w dowolny sposób, pod warunkiem zacytowania autora.
// W przypadku chęci użycia komercyjnego należy zapytać autora o zgodę.

#include "zbior_ary.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


//Zmienna globalna (bez niej nie da się zrobić zadania)
// Różnica ciągów arytmetycznych
Q_struct Q = {0, false};

// Zwraca nieujemne modulo liczby 
int modulo(int a){
    if(a % Q.wartosc < 0)
        return a % Q.wartosc + Q.wartosc;

    return a % Q.wartosc;
}

// Funkcja daje w wyniku zbior reprezentujacy ciag arytmetyczny
// o elemencie poczatkowym a, końcowym b i roznicy q>0, tj. {a,a+q,...,b}.
// Mozesz zalozyc, ze we wszystkich zapytaniach w danym tescie wartosc q bedzie taka sama.
// Mozesz zalozyc, ze ta funkcja zostanie wywolana jako pierwsza.

zbior_ary ciag_arytmetyczny(int a, int q, int b){

    if(Q.czy_ustawione == false){
        Q.wartosc = q;
        Q.czy_ustawione = true;
    } // Przypisujemy wartość q dla całego zadania (ta funkcja zostaje wywołana na samym początku)
    assert(q == Q.wartosc);
    assert(modulo(a) == modulo(b));// Sprawdzamy czy dane spełniają warunki zadania.

    // Najpierw tworzymy najmniejszą jednostkę - ciąg arytmetyczny
    ciag_ary pewien_ciag ={ 
        .poczatek = a,
        .koniec = b
     };

     ciag_ary* t_ciag = (ciag_ary*) malloc (sizeof(ciag_ary)); // Tablica zawierająca ten ciąg.
     t_ciag[0] = pewien_ciag;

     // Ten ciąg jest  również częścią klasy abstrakcji ciągów o tej samej reszcie z dzielenia przez q.
     sumowalne_ciagi pewien_sumowalny_ciag ={
        .reszta = modulo(a),
        .t_ciag = t_ciag,
        .rozmiar = 1
     };

     sumowalne_ciagi* t_sum = (sumowalne_ciagi*) malloc (sizeof(sumowalne_ciagi)); // Tablica zawierająca tę klasę abstrakcji
     t_sum[0] = pewien_sumowalny_ciag;

     //Ostatecznie tworzymy zbiór klas abstrakcji.
    zbior_ary pewien_zbior = {
        .t_sum = t_sum,
        .rozmiar = 1,
    };
    return pewien_zbior;
}

// Daje w wyniku zbior zlozony z samego elementu a, tj. {a}.
zbior_ary singleton(int a){
    return ciag_arytmetyczny(a, Q.wartosc, a);
}

// Zwraca pusty (o rozmiarze 0) zbiór zajmujący O('pamiec') jednostek pamięci.
zbior_ary zbior_pusty(unsigned pamiec){
    sumowalne_ciagi* t_sum = (sumowalne_ciagi*) malloc (pamiec * sizeof(sumowalne_ciagi));
    zbior_ary pusty={
        .t_sum = t_sum,
        .rozmiar = 0,
    };
    return pusty;
}

// Zwraca pusty (o rozmiarze 0) zbiór zajmujący O('pamiec') jednostek pamięci.
// O reszcie z dzielenia przez Q 'reszta'
sumowalne_ciagi pusty_sumowalny(unsigned pamiec, int reszta){
    ciag_ary* t_ciag = (ciag_ary*) malloc (pamiec * sizeof(ciag_ary));
    sumowalne_ciagi pusty ={
        .reszta = reszta,
        .t_ciag = t_ciag,
        .rozmiar = 0
    };
    return pusty;
}

<<<<<<< HEAD
=======
// Kolejne funkcje wypisują odpiwiednie struktury na wyjście standardowe
void wypisz_ciag(ciag_ary pewien_ciag){
    printf("C: ");
    for(int a = pewien_ciag.poczatek ; a <= pewien_ciag.koniec ; a += Q.wartosc){
        printf("%d ", a);
    }
}

void wypisz_sumowalny_ciag(sumowalne_ciagi sum_ciagi){
    for(unsigned i = 0 ; i < sum_ciagi.rozmiar ; ++i){
        ciag_ary pewien_ciag = sum_ciagi.t_ciag[i];
        wypisz_ciag(pewien_ciag);
        printf(" ");
    }
}

void wypisz_zbior(zbior_ary A){
    for(unsigned i = 0 ; i < A.rozmiar ; ++i){
        sumowalne_ciagi pewien_sumowalny_ciag = A.t_sum[i];
        wypisz_sumowalny_ciag(pewien_sumowalny_ciag);
        printf("\n");
    }
    printf("\n");
}

>>>>>>> Peer_review
// Zwiększa 'rozmiar' pewnego sumowalnego ciągu o 1 i wpisuje tam pewien ciąg arytmetyczny
void przypisz_ciag(ciag_ary a, sumowalne_ciagi* A){
    A -> rozmiar ++;
    unsigned ost_elem = A -> rozmiar - 1; // Wskaźnik na ostatni element w wyniku (ten, który teraz zapisujemy
    A -> t_ciag[ost_elem] = a;
}

// Struktura, która przechowuje początki lub końce przedziałów.
typedef struct punkt{
    int wartosc; // Miejsce na osi liczbowej
    bool czy_A; // Rozróżnia dwa zbiory: A i B
    bool poczatek; // Rozróżnia, czy jest to początek ciągu, czy koniec
} punkt;

// Definiuje a > b
bool punkt_a_wiekszy_niz_b(punkt a, punkt b){
    if(a.wartosc == b.wartosc){      // Gdy wartości są równe
        if(a.poczatek && b.poczatek) // Najpierw początek B, a potem początek A -> Istotne przy różnicy
            return a.czy_A > b.czy_A;
        return a.poczatek < b.poczatek; // Preferujemy początek przed końcem -> Istotne przy sumie
    }
    return a.wartosc > b.wartosc; // Sortujemy po wartościach.
}

// Przepisuje wszyskie punkty z A do 'punkt'ów 
void przepisz_punkt(sumowalne_ciagi A, punkt** tab_A, bool czy_A){

    for(unsigned i = 0 ; i < A.rozmiar ; ++i){
        punkt poczatek = {A.t_ciag[i].poczatek, czy_A, true};
        (*tab_A)[2 * i] = poczatek;
<<<<<<< HEAD

        punkt koniec = {A.t_ciag[i].last + Q.wartosc, czy_A, false};
=======
        //wypisz_punkt(poczatek);
        punkt koniec = {(int64_t) A.t_ciag[i].koniec + (int64_t) Q.wartosc, czy_A, false};
>>>>>>> Peer_review
        (*tab_A)[2 * i + 1] = koniec;
    }
}

// Do pewnej tablicy punktów 'tab' dopisuję na końcu punkt, przesuwam wskaźnik
void dodaj_punkt(punkt** tab, unsigned* ind, int* wsk_A, punkt wartosc){
    (*tab)[*ind] = wartosc;
    (*wsk_A)++;
    (*ind)++;
}

#define DODAJ_PUNKT_Z_A dodaj_punkt(&(*tab), &ind_tab, &wsk_A, tab_A[wsk_A + 1])
#define DODAJ_PUNKT_Z_B dodaj_punkt(&(*tab), &ind_tab, &wsk_B, tab_B[wsk_B + 1])

// Sortuje rosnąco punkty z A i B i zapisuje w tablicy
void posortuj(sumowalne_ciagi A, sumowalne_ciagi B, punkt** tab){

    unsigned ind_tab = 0; // Indeks tablicy

    //Przepisujemy A i B do tablic punktów
    punkt* tab_A = (punkt*) malloc (A.rozmiar * 2 * sizeof(punkt));//Działa
    przepisz_punkt(A, &tab_A, /*Czy_A*/ true);

    punkt* tab_B = (punkt*) malloc (B.rozmiar * 2 * sizeof(punkt));
    przepisz_punkt(B, &tab_B, /*Czy_A*/ false);
    
    int wsk_A = -1;
    int wsk_B = -1;

    // Idziemy po kolei. Ta, która jest mniejsza następna będzie wpisana do tablicy.
    while(wsk_A  < (int) A.rozmiar * 2 - 1 || wsk_B  < (int) B.rozmiar * 2 - 1){

        if(wsk_A + 1 >= (int) A.rozmiar * 2) // Gdy skończyliśmy tablicę A idziemy po B
            DODAJ_PUNKT_Z_B;
        
        else if(wsk_B + 1 >= (int) B.rozmiar * 2) // Gdy skończyliśmy tablicę B idziemy po A
            DODAJ_PUNKT_Z_A;
        
        else if(punkt_a_wiekszy_niz_b(tab_A[wsk_A + 1], tab_B[wsk_B + 1])) // Jeśli A jest większy niż B, to idziemy po B
            DODAJ_PUNKT_Z_B;
        else                                        // Jeśli B jest większy niż A to idziemy po A
            DODAJ_PUNKT_Z_A;
    }
    free(tab_A);
    free(tab_B);
}

// Ta funkcja dodaje do wyniku jeden sumowalny ciąg
void przypisz_sumowalne(sumowalne_ciagi A, zbior_ary* wynik){
    wynik->rozmiar ++;
    unsigned ost_elem = wynik->rozmiar - 1; // Wskaźnik na ostatni element w wyniku (ten, który teraz zapisujemy)
    wynik->t_sum[ost_elem] = A;
}

// Zwraca 1 lub -1. 
int zmiana_stanu(punkt p, bool czy_minus_B){
    if(czy_minus_B && !p.czy_A){
        return p.poczatek ? -1 : 1; // Jeśli odejmujemy B to dla B zamieniamy - początek to -1 i koniec to 1.
    }
    return p.poczatek ? 1 : -1; // Z reguły początek to 1, a koniec to -1.
}

// Idzie po kolejnych posortowanych punktach i dodaje znalezione ciągi do wyniku
void znajdz_ciagi_po_punktach(
    punkt* sort_punkt, unsigned n,// 'n' - maksymalny indeks
     sumowalne_ciagi* wynik,
<<<<<<< HEAD
    int poczatkowy_stan, bool czy_minus_B) // Parametry
{
    int stan = poczatkowy_stan; // Dla sumy i różnicy 0, dla iloczynu -1.
    int first; // Początkowy wyraz ciągu
    bool first_ustalone = false; // Sprawdzamy, czy ustaliliśmy pierwszy wyraz ciągu przed ostatnim.
=======
      int poczatkowy_stan, bool czy_minus_B
){
    int stan = poczatkowy_stan; // Dla sumy i różnicy 0, dla iloczynu -1.
    int64_t poczatek; // Początkowy wyraz ciągu
    bool poczatek_ustalony = false; // Sprawdzamy, czy ustaliliśmy pierwszy wyraz ciągu przed ostatnim.
>>>>>>> Peer_review

    // Aktualizujemy 'stan'. Jeśli nie czy_minus_B i jesteśmy na początku A lub B, to stan zwiększamy o 1.
    // W przeciwnym przypadku  zmniejszamy o 1. Jeśli stan zmieniea się z 0 na 1, to jest to początek ciągu dodania.
    // Gdy stan zmienia się z 1 na 0, to znaleźliśmy koniec ciągu, który należy dodać do wyniku.
    for(unsigned i = 0 ; i < n ; ++i){
        punkt p = sort_punkt[i];

        int poprzedni_stan = stan;
        stan += zmiana_stanu(p, czy_minus_B);

        if(poprzedni_stan == 0 && stan == 1){
            poczatek = p.wartosc; // W tym momencie znaleźliśmy początek ciągu
            poczatek_ustalony = true;
        }
        else if(poprzedni_stan == 1 && stan == 0){
<<<<<<< HEAD
            assert(first_ustalone); // Sprawdzamy, czy wcześniej ustalilismy początek
            if(first <= p.wartosc - Q.wartosc){ // Jeśli ciąg jest prawidłowy - ważne przy iloczynie
                ciag_ary ciag = {first, p.wartosc - Q.wartosc}; // Każdy koniec jest przedłużony o Q.wartosc, więc teraz trzeba to odjąć.
=======
            assert(poczatek_ustalony); // Sprawdzamy, czy wcześniej ustalilismy początek
            if(poczatek <= p.wartosc - Q.wartosc){ // Jeśli ciąg jest prawidłowy - ważne przy iloczynie
                ciag_ary ciag = {(int) poczatek, (int) (p.wartosc - (int64_t) Q.wartosc)}; // Każdy koniec jest przedłużony o Q.wartosc, więc teraz trzeba to odjąć.
>>>>>>> Peer_review
                przypisz_ciag(ciag, &(*wynik));
            }
            poczatek_ustalony = false;
        }
    }
}

// Ta funkcja łączy dwa sumowalne ciągi teoriomnogościowo.
sumowalne_ciagi polocz_sumowalne(sumowalne_ciagi A, sumowalne_ciagi B, int poczatkowy_stan, bool czy_minus_B){    
    // Tworzymy tablicę z od razu zaalokowaną pamięcią. Na koniec zwolnimy nieużywaną pamięć.
    sumowalne_ciagi wynik  = pusty_sumowalny(A.rozmiar + B.rozmiar + 7, A.reszta); 

    // Tablica, która będzie przechowywała posortowane początki i końce A i B
    punkt* sort_punkt = (punkt*) malloc (2 * (A.rozmiar + B.rozmiar) * sizeof(punkt));
    posortuj(A, B, &sort_punkt); // O(Ary_q(A) + Ary_q(B)

    znajdz_ciagi_po_punktach(
        sort_punkt,
         2 * (A.rozmiar + B.rozmiar),
        &wynik,
        poczatkowy_stan,
        czy_minus_B
    );

    free(sort_punkt);

    ciag_ary* tmp = (ciag_ary*) realloc(wynik.t_ciag, wynik.rozmiar * sizeof (sumowalne_ciagi)); // Zwalniamy niepotrzebną pamięć
    if(tmp != NULL)
        wynik.t_ciag = tmp;

    return wynik;
}

// Typ zmiennej - nazwa tej zmiennej to 'A_ROZNE_B'. Zmienna będzie funkcją void, która przyjmuje zadane parametry.
typedef void (*A_ROZNE_B) (unsigned*, sumowalne_ciagi, zbior_ary*);

// Ta funkcja jest częścią przeszukiwania reszt zbioru. Wykonuje operację na dwóch sumowalnych ciagach
//  w najtrudniejszym przypadku, czyli kiedy reszty są równe. Przesuwa wskaźniki dalej.
void rowne_reszty
    (unsigned* wsk_A, unsigned* wsk_B,
    sumowalne_ciagi A, sumowalne_ciagi B,
    zbior_ary* wynik,
    int pocz_stan, bool czy_minus_B   
){
    sumowalne_ciagi poloczne_ciagi = polocz_sumowalne(A, B, pocz_stan, czy_minus_B);
    przypisz_sumowalne(poloczne_ciagi, &(*wynik));
    (*wsk_A)++;
    (*wsk_B)++;
}

// Idzie po wszystkich resztach z dzielenia przez Q zbiorów A i B.
// W zależności od operacji dodaje lub nie 'samotne' reszty z A i B.
// W przypadku równych reszt łączy oba sumowalne ciągi funkcją
// 'połacz_sumowalne' z zadanymi parametrami 'pocz_stan' i 'czy_minus_b'
// Zwraca końcowy zbiór po operacjach.
zbior_ary przeszukaj_reszty(
    zbior_ary A, zbior_ary B,
    int pocz_stan, bool czy_minus_B, // Parametry łączenia
    A_ROZNE_B A_wieksze_B, // Czy dodajemy samotne reszty z B?
    A_ROZNE_B A_mniejsze_B // Czy dodajemy samotne reszty z A?
){
    // Tworzymy pusty zbior o odpowiedniej wielkości.
    zbior_ary wynik = zbior_pusty(A.rozmiar + B.rozmiar + 7); 

    unsigned wsk_A = 0; // Wskaźnik po zbiorze A.
    unsigned wsk_B = 0; // Wskaźnik po zbiorze B.

    // Zakładamy, że reszty w zbiorach A i B są posortowane. Idziemy wskaźnikami po kolei, zwiększając mniejszą resztę.
    while(wsk_A < A.rozmiar && wsk_B < B.rozmiar){

        int reszta_A = A.t_sum[wsk_A].reszta;
        int reszta_B = B.t_sum[wsk_B].reszta;

        if(reszta_A == reszta_B)
            rowne_reszty(&wsk_A, &wsk_B, A.t_sum[wsk_A], B.t_sum[wsk_B], &wynik, pocz_stan, czy_minus_B);

        else if(reszta_A < reszta_B)
            A_mniejsze_B(&wsk_A, A.t_sum[wsk_A], &wynik);

        else if(reszta_A > reszta_B)
            A_wieksze_B(&wsk_B, B.t_sum[wsk_B], &wynik);
    }

    // Gdy jakieś reszty zostaną w jednym ze zbiorów, to chcemy odpowiedznie wartości dopisać do ostatecznego wyniku.
    while(wsk_A < A.rozmiar)
        A_mniejsze_B(&wsk_A, A.t_sum[wsk_A], &wynik);

    while(wsk_B < B.rozmiar)
         A_wieksze_B(&wsk_B, B.t_sum[wsk_B], &wynik);

    // Zwalniamy pamięć
    sumowalne_ciagi* tmp = (sumowalne_ciagi*) realloc(wynik.t_sum, wynik.rozmiar * sizeof(sumowalne_ciagi));
    if(tmp != NULL)
        wynik.t_sum = tmp;

    return wynik;
}

// Ta funkcja jest częscią przeszukiwania. Dodaje do wyniku sumowalny ciąg ze zbioru i przesuwa wskaźnik.
void A_rozne_B_przypisz(unsigned* wsk_B, sumowalne_ciagi B, zbior_ary* wynik){
    przypisz_sumowalne(B, &(*wynik));
    (*wsk_B)++;
}

// Ta funkcja jest częscią przeszukiwania. NIE dodaje do wyniku sumowalnego ciągu ze zbioru i przesuwa wskaźnik.
void A_rozne_B_NIE_przypisz(unsigned* wsk_B, sumowalne_ciagi B, zbior_ary* wynik){
    (*wsk_B)++;
    B = (*wynik).t_sum[0]; // To nic nie robi. Dla kompilatora
    assert((int) B.rozmiar > -1); // To nic nie robi. Dla kompilatora
}

// Daje w wyniku zbior reprezentujacy teoriomnogosciowa sume zbiorow A i B.
zbior_ary suma(zbior_ary A, zbior_ary B){

    return przeszukaj_reszty
    (
        A, B, // Zbiory, które dodajemy
        /*stan_pocz*/ 0, /*czy_minus_B*/ false, // Parametry funkcji "polacz sumowalne"
        A_rozne_B_przypisz, // Uwzgleniamy "samotne" reszty z B
        A_rozne_B_przypisz  // Uwzgleniamy "samotne" reszty z A
    );
}

// Daje w wyniku zbior A \ B.
zbior_ary roznica(zbior_ary A, zbior_ary B){
    return przeszukaj_reszty(
        A, B,
        /*stan_pocz*/ 0, /*czy_minus_B*/ true, // Parametry funkcji "polacz sumowalne"
        A_rozne_B_NIE_przypisz, // "Samotnych" reszt z B nie uwzględniamy
        A_rozne_B_przypisz      // Uwzgleniamy "samotne" reszty z A
    );
}

// Daje w wyniku zbior reprezentujacy czesc wspolna zbiorow A i B.
zbior_ary iloczyn(zbior_ary A, zbior_ary B){
    return przeszukaj_reszty(
        A, B,
        /*stan_pocz*/ -1, /*czy_minus_B*/ false, // Parametry funkcji "polacz sumowalne"
        A_rozne_B_NIE_przypisz, // "Samotnych" reszt z B nie uwzględniamy
        A_rozne_B_NIE_przypisz  // "Samotnych" reszt z A nie uwzględniamy
    );
}

// Daje w wyniku sumowalne_ciagi o tej samej reszcie z dzielenia przez Q co b, albo puste w czasie O(log(A.rozmiar))
sumowalne_ciagi binsearch_reszt(zbior_ary A, int b){

    if(A.rozmiar == 0)
        return pusty_sumowalny(0, modulo(b));

    int pocz = -1;
    int kon = (int) A.rozmiar; // Definiujemy wskaźniki

    while(kon - pocz > 1){
        int srod = (pocz + kon) / 2;
        assert(srod != pocz && srod != kon); // Zapobiega zapętleniu w nieskończoność.
        if(A.t_sum[srod].reszta < modulo(b))
            pocz = srod; // Początek zawsze mniejszy
        else 
            kon = srod;
    }
    assert(kon - pocz == 1); 
    // 'pocz' to największy indeks mniejszy niż modulo(b)
    // 'kon' to najmniejszy indeks większy lub równy modulo(b)
    if(pocz == (int) A.rozmiar - 1) // Jeśli każda reszta mniejsza niż modulo(b), to takiej nie ma - zwracamy pusty ciąg.
        return pusty_sumowalny(0, modulo(b));

    else if(A.t_sum[pocz + 1].reszta == modulo(b))// Kolejny indeks powinien być równy (jeśli taki jest) albo większy (jeśli takiego nie ma)
        return A.t_sum[pocz + 1];

    return pusty_sumowalny(0, modulo(b));
}

// Sprawdza, czy b należy do któregoś z ciągów w 'sumowalne_ciagi A' w czasie O(log(A.rozmiar))
bool binsearch_ciagow(sumowalne_ciagi A, int b){

    if(A.rozmiar == 0)
        return false;

    int pocz = -1;
    int kon = (int) A.rozmiar; // Definiujemy wskaźniki

    while(kon - pocz > 1){
        int srod = (pocz + kon) / 2;
        assert(srod != pocz && srod != kon); // Zapobiega zapętleniu w nieskończoność.
        if(A.t_ciag[srod].koniec < b)
            pocz = srod; // pocz zawsze mniejszy
        else
            kon = srod;
    }
    // 'pocz' to największy indeks przedziału mniejszego niż b.
    // 'kon' to najmniejszy indeks przedziału zawierającego b lub większego niż b.
    if(pocz == (int) A.rozmiar - 1) // Jeśli każdy przedział jest mniejszy
        return false;

    if(A.t_ciag[pocz + 1].poczatek <= b && b <= A.t_ciag[pocz + 1].koniec) // Jeśli się zawiera w kolejnym przedziale
        return true;

    return false;
}
// Daje w wyniku true wtw. gdy liczba b nalezy do zbioru A.
bool nalezy(zbior_ary A, int b){
    sumowalne_ciagi B = binsearch_reszt(A, b);
    return binsearch_ciagow(B, b);
}

// Wynikiem funkcji jest liczba elementow w zbiorze A.
unsigned moc(zbior_ary A){
    
    unsigned moc = 0;
    for(unsigned i = 0 ; i < A.rozmiar ; ++i){
        sumowalne_ciagi S = A.t_sum[i];
        for(unsigned j = 0 ; j < S.rozmiar ; ++j){
            ciag_ary C = S.t_ciag[j];
<<<<<<< HEAD
            moc += (unsigned) ((C.last - C.first + Q.wartosc) / Q.wartosc); // Dodajemy moc każdego ciągu.
=======
            moc += (unsigned) (((int64_t) C.koniec - (int64_t) C.poczatek + Q.wartosc) / Q.wartosc); // Dodajemy moc każdego ciągu.
>>>>>>> Peer_review
        }
    }
    return moc;
}

// Wynikiem funkcji jest Ary_q(A), czyli minimalna liczba parami rozlacznych ciagow arytmetycznych o roznicy q, ktorych suma jest zbior A.
unsigned ary(zbior_ary A){
    unsigned ary_q = 0;
    for(unsigned i = 0 ; i < A.rozmiar ; ++i){
        sumowalne_ciagi S = A.t_sum[i];
        ary_q += S.rozmiar; // Dodajemy ilość ciągów dla każdych sumowalnych ciągów - o tej samej reszcie.
    }
    return ary_q;
}