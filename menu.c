#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "tri.h"
#include "dijkstra.h"

void menu(station* stations, int nb_stations, HashTable* ht_nom) {
    char buf[32];

    while (1) {
        printf("=== MENU RÉSEAU DE TRANSPORT ===\n");
        printf("1 - Afficher les informations d'une station\n");
        printf("2 - Lister les voisins d'une station\n");
        printf("3 - Calculer un chemin minimal\n");
        printf("4 - Afficher les stations triées par degré\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");

        fgets(buf, sizeof(buf), stdin);
        int choix = atoi(buf);

        switch (choix) {
            case 0: 
                return;

            case 1:
                afficher_station(stations, nb_stations, ht_nom);
                break;

            case 2:
                afficher_voisins(stations, nb_stations, ht_nom);
                break;

            case 3: {
                trouver_chemin(stations,nb_stations,ht_nom);
                break;
            }

            case 4:
                afficher_tri(stations, nb_stations);
                break;

            default:
                printf("Choix invalide\n");
        }

        printf("\n");
    }
}
