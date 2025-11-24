//Rozwiązanie zadania trzy_rozne
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct motel {
  int nr_sieci;
  int odl_od_pocz;
} motel;

// Grupa moteli to kolejne motele należące do tej samej sieci.
typedef struct grupa_moteli {
  int nr_sieci;
  int ind_pierwszego; // Przechowuje indeks z tabeli motele
  int ind_ostatniego; // Przechowuje indeks z tablei motele
} grupa_moteli;

// Funkjca wczytująca n i kolejne sieci i odległości moteli
void wczytaj_dane(int *n, motel *motele[]) {

  if (scanf("%d", &(*n)) != 1) {
    printf("Blad danych\n");
    exit(0);
  }

  *motele = (motel *)malloc(((unsigned)(*n) + 1) * sizeof(motel));
  assert(*motele != NULL);

  for (int i = 0; i < *n; ++i) { // Wczytaj kolejne motele
    motel wczytywany;
    if (scanf("%d %d", &wczytywany.nr_sieci, &wczytywany.odl_od_pocz) != 2) {
      printf("Blad danych\n");
      exit(0);
    }
    (*motele)[i] = wczytywany;
  }
}

// Sprawdza, czy 'nr_sieci' ma nowy numer. Jeśli tak, przypisuje go pierwszej
// wolnej (zerowej) zmiennej.
void nowa_siec(int *a, int *b, int *c, int nr_sieci) {
  // Na wejściu:
  // Jeśli Jeśli a == 0 (nie ma numeru), to b == 0.
  // Jeśli b == 0, to c == 0
  if (*a == 0)
    *a = nr_sieci;
  else if (*a != nr_sieci && *b == 0)
    *b = nr_sieci;
  else if (*a != nr_sieci && *b != nr_sieci && *c == 0)
    *c = nr_sieci;
}

// Tworzy grupy kolejnych moteli o tych samych nr sieci. Sprawdza, czy jest ich
// co najmniej 3.
bool pogrupuj_motele(int n, motel motele[], grupa_moteli *pogrupowane_motele[],
                     int *ilosc_grup) {

  assert(n > 0);

  *pogrupowane_motele = (grupa_moteli *)malloc(
      (unsigned)n * sizeof(grupa_moteli)); // Alokujemy pamięć
  assert(*pogrupowane_motele != NULL);

  *ilosc_grup = 0; // Inicjujemy 'ilosc_grup'

  int siec_1 = 0, siec_2 = 0,
      siec_3 = 0; // Do sprawdzenia czy grup sieci jest > 2.

  int poczatek_grupy = 0;
  motel zero = {0, 0};
  motele[n] = zero; // Motel za ostatnim z innej grupy

  for (int i = 0; i < n; ++i) {

    nowa_siec(&siec_1, &siec_2, &siec_3,
              motele[i].nr_sieci); // Do sprawdzenia czy grup sieci jest > 2.

    if (motele[i].nr_sieci !=
        motele[i + 1]
            .nr_sieci) { // Jeśli zmienia się nr sieci, to tworzymy nową grupę.
      grupa_moteli grupa = {/*nr_sieci*/ motele[i].nr_sieci,
                            /*ind_pierwszego*/ poczatek_grupy,
                            /*ind_ostatniego*/ i};
      (*pogrupowane_motele)[*ilosc_grup] = grupa;
      (*ilosc_grup)++;
      poczatek_grupy =
          i + 1; // Kolejna grupa będzie miała początek jeden indeks dalej
    }
  }

  // Czyścimy pamięć
  grupa_moteli *tmp = (grupa_moteli *)realloc(
      *pogrupowane_motele, (unsigned)*ilosc_grup * sizeof(grupa_moteli));
  if (tmp != NULL)
    *pogrupowane_motele = tmp;

  return siec_3 != 0; // Jeśli nie ma trzech różnych sieci, to zwracamy false
}

int min(int a, int b) {
  if (a > b)
    return b;
  return a;
}

int max(int a, int b) {
  if (a >= b)
    return a;
  return b;
}

// Zwraca miniumum dla grupy b z maksimów odległości moteli z grupy b do a i c
// odpowiednio. Wykorzystujemy w int najblizsza(). To dla s = -1. Dla s = 1
// odwrotnie i wykorzystujemy w najdalsza()
int maks_min(int fir_ix, grupa_moteli b, int las_ix, motel motele[],
             int the_worst, int s) {

  int lewy = motele[fir_ix].odl_od_pocz; // Optymalizujemy odległości do a i c
  int prawy = motele[las_ix].odl_od_pocz;

  int wynik = the_worst;
  for (int i = b.ind_pierwszego; i <= b.ind_ostatniego;
       ++i) { // Pętla po wszystkich z grupy b
    int srodek = motele[i].odl_od_pocz;
    wynik =
        s * max(s * wynik,
                min(s * (srodek - lewy),
                    s * (prawy - srodek))); // dla s = -1 to będzie min z maks
  }
  return wynik;
}

// Zwraca odległość najbliższej trójki
int najblizsza(motel motele[], grupa_moteli grupy[], int ilosc_grup) {

  int wynik = INT_MAX;
  // Przeszukaj po trzy kolejne grupy
  // Jeżeli istnieją trzy grupy o parami różnych sieciach, to będą istiały trzy
  // kolejne grupy o parami różnych sieciach ,wśród których jest miniumum.
  for (int i = 0; i + 2 < ilosc_grup; ++i) {
    if (grupy[i].nr_sieci != grupy[i + 2].nr_sieci) {
      wynik = min(wynik,
                  maks_min(grupy[i].ind_ostatniego, grupy[i + 1],
                           grupy[i + 2].ind_pierwszego, motele, INT_MAX, -1));
    }
  }
  return wynik;
}

// Znajduje indeks sieci, ktora ma trzeci różny numer od początku albo końca.
int znajdz_3_rozna_siec(grupa_moteli grupy[], int ilosc_grup, int zmiana,
                        int pierwszy) {

  int siec_1 = grupy[pierwszy].nr_sieci; // Pierwsze dwie sieci są zafiksowane
                                         // (po prostu pierwsze dwie)
  int siec_2 = grupy[pierwszy + zmiana].nr_sieci;
  int siec_3 = 0; // Tej sieci szukamy
  int ind_siec_3 = pierwszy + zmiana;
  while (siec_3 == 0) { // Dopóki nie znaleźliśmy
    ind_siec_3 += zmiana;
    assert(0 <= ind_siec_3 && ind_siec_3 < ilosc_grup);
    nowa_siec(&siec_1, &siec_2, &siec_3,
              grupy[ind_siec_3].nr_sieci); // Sprawdzamy, czy ta jest nowa.
  }
  return ind_siec_3;
}

// Przeszukuje wszystkie grupy pomiędzy zadanymi grupami. Wywołana dokładnie 9
// razy
int poszukaj_pomiedzy(const int ind_pocz, const int ind_kon, motel motele[],
                      grupa_moteli grupy[]) {

  grupa_moteli a = grupy[ind_pocz];
  grupa_moteli c = grupy[ind_kon];

  if (a.nr_sieci == c.nr_sieci) // Chcemy, aby grupy spełniały warunki zadania
    return 0;

  int wynik = 0;

  for (int i = ind_pocz + 1; i < ind_kon; ++i) { // Pętla po grupach pomiędzy
    grupa_moteli b = grupy[i];
    if (a.nr_sieci != b.nr_sieci &&
        c.nr_sieci !=
            b.nr_sieci) { // Sprawdzamy, czy grupa spełnia warunek zadania.
      wynik = max(wynik, maks_min(a.ind_pierwszego, b, c.ind_ostatniego, motele,
                                  0, 1)); // Aktualizujemy wynik (maks).
    }
  }
  return wynik;
}

int najdalsza(motel motele[], grupa_moteli grupy[], int ilosc_grup) {

  int ind_3_pocz = znajdz_3_rozna_siec(
      grupy, ilosc_grup, 1,
      0); // Potrzebujemy 3.ich indeksów sieci od początku i końca
  int ind_3_kon = znajdz_3_rozna_siec(grupy, ilosc_grup, -1, ilosc_grup - 1);

  const int pocz_ind[3] = {0, 1, ind_3_pocz}; // Tablice indeksów
  const int kon_ind[3] = {ilosc_grup - 1, ilosc_grup - 2, ind_3_kon};

  int wynik = 0;

  // Dla każdej możliwej pary 3 - 3 tych indeksów przeszukujemy wszystkie grupy.
  // Można udowodnić, że wśród nich jest szukane maksimum.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; ++j) {
      wynik =
          max(wynik, poszukaj_pomiedzy(pocz_ind[i], kon_ind[j], motele, grupy));
    }
  }

  return wynik;
}

int main() {
  // Inicjacja i wczytanie danych
  int n;
  motel *motele;
  wczytaj_dane(&n, &motele);

  // Preprocesujemy grupy moteli
  grupa_moteli *grupy;
  int ilosc_grup;
  if (pogrupuj_motele(n, motele, &grupy, &ilosc_grup) == false) {
    printf("0 0\n");
    return 0;
  }

  // Szukamy i zwracamy wynik w czasie O(n).
  printf("%d %d\n", najblizsza(motele, grupy, ilosc_grup),
         najdalsza(motele, grupy, ilosc_grup));

  free(motele);
  free(grupy);
  return 0;
}