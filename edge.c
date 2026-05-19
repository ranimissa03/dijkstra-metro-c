#include "edge.h"

void charger_edges(const char* fichier, station* stations, int nb_stations) {
    FILE* fp = fopen(fichier, "r");
    if (!fp) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    char txt[TAILLE];
    while (fgets(txt, TAILLE, fp) != NULL) {
        int src, dest, poids;                                                        //les valeurs dont on aura besoin
        if (sscanf(txt, "EDGE;%d;%d;%d", &src, &dest, &poids) == 3) {
            if (src < 0 || src >= nb_stations || 
                dest < 0 || dest >= nb_stations) {                                  //vérifie la cohérence des valeurs et ignore la ligne si c'est incohérent
                continue;
            }
            int doublon = 0;
            arc* courant = stations[src].adj;
            while (courant != NULL) {                                                //on s'assure que l'arc n'est pas vide
                if (courant->destination == dest) {                                  //on vérifie s'il y a des doublons
                    doublon = 1;
                    break;
                }
                courant = courant->suivant;
            }
            if (!doublon) {
                arc* a = malloc(sizeof(arc));                                       //on crée un nouvel arc qu'on viendra ajouter à celui de la station
                if (!a) {continue;}                                                 //traitement de l'erreur
                a->destination = dest;                                              //on lui assigne les valeurs qu'il doit prendre
                a->poids = poids;
                a->suivant = stations[src].adj;                                     //on le relie aux voisins déjà existants de la station
                stations[src].adj = a;                                              //puis on ajoute la station (qui contient déjà tous les autres voisins avec la dernière ligne)
            }
        }
    }
    fclose(fp);
    return;
}











