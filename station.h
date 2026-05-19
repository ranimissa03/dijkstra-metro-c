#ifndef STATION_H
#define STATION_H

#define TAILLE 100
#define NAME 50

typedef struct ARC {
    int destination;
    int poids;                                                      
    struct ARC* suivant;
}arc;

typedef struct STATION {
    int id;
    char nom[NAME];
    arc* adj;
}station;

typedef struct HashTable HashTable;

int stocke_id(FILE* fic, int* ids);
int stocke_id_et_noms(FILE* fic, int* ids, char names[][NAME]);
int trouver_station(station* stations, int nb_stations, int id);
int degre_station(station* s);
void afficher_par_id(station* stations, int nb_stations);
void afficher_station(station* stations, int nb_stations, HashTable* ht_nom);
void afficher_voisins_par_id(station* stations, int nb_stations);
void afficher_voisins(station* stations,int nb_stations,HashTable* ht_nom);


#endif