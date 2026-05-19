#include <stdio.h>
#include "station.h"
#include "hash.h"
#include "edge.h"
#include "tri.h" 
#include "dijkstra.h"
#include "menu.h"

int main(int argc, char** argv) {   
    if (argc != 2) {                                                //un unique argument est demandé : le nom du fichier
        printf("Tu as oublié de mettre le fichier\n");
        return -1;
    }
    FILE * fp = fopen(argv[1],"r");                                 //ouvre le fichier mis en argument dans le mode "r" (lecture)
    if (!fp) {                                                      //si le fichier n'est pas trouvé
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }

    /*Compter*/
    int ids[130];
    int nb_stations = stocke_id(fp,ids);                            //compte le nombre de stations
    fclose(fp);

    /*Allocation*/
    station *stations = malloc(nb_stations * sizeof(station));
    if (!stations) {                                                //erreur en cas de manque de mémoire
        printf("Erreur allocation mémoire\n");
        return -1;
    }

    /*Chargement*/
    char names[130][NAME];
    fp = fopen(argv[1],"r");
    stocke_id_et_noms(fp,ids,names);                                //stockage des noms de chaque station
    fclose(fp);
    for (int i = 0; i < nb_stations; i++) {
        stations[i].id = ids[i];                                    //chargement des id depuis le tableau fait plus haut
        strcpy(stations[i].nom, names[i]);                          //idem pour les noms
        stations[i].adj = NULL;                                     //initialisation de la liste d'adjacence pour chaque station
    }

    /*Remplissage de la liste d'adjacence*/
    charger_edges(argv[1], stations, nb_stations);

    /*Initialisation de la hash table*/
    HashTable ht_nom;
    hash_init(&ht_nom);

    /*Remplissage de la hash table*/
    for (int i = 0; i < nb_stations; i++) {
        hash_insert(&ht_nom, stations[i].nom, i);
    }

    /*Menu*/
    menu(stations,nb_stations,&ht_nom);
    hash_free(&ht_nom);                                             
    free(stations);                                                 //libération de mémoire du tableau stations
}