#include <stdio.h>
#include <limits.h>                                                         //INT_MAX (+infini)
#include "dijkstra.h"

int min_distance(int* dist, int* visite, int n) {
    int min = INT_MAX;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (!visite[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void afficher_chemin(int* precedent, int src, int dest, station* stations) {
    if (dest == src) {
        printf("%s", stations[src].nom);
        return;
    }
    if (precedent[dest] == -1 && dest != src) {                             //si dest et src ne sont pas connectées ( 1->2 et 3->4 par exemple)
    printf("Chemin impossible\n");
    return;
    }
    afficher_chemin(precedent, src, precedent[dest], stations);
    printf(" -> %s", stations[dest].nom);
}


void dijkstra(station* stations, int nb_stations, int src, int dest) {
    int dist[nb_stations];
    int visite[nb_stations];
    int precedent[nb_stations];
    for (int i=0;i<nb_stations;i++) {
        dist[i] = INT_MAX;                                                  //+infini
        visite[i] = 0;
        precedent[i] = -1;

    }
    dist[src] = 0;
    for (int j=0;j<nb_stations;j++) {
        int u = min_distance(dist,visite,nb_stations);
        if (u == -1) {break;}
        visite[u] = 1;
        arc* a = stations[u].adj;
        while (a != NULL) {
            int v = a->destination;
            if (!visite[v] && dist[u] != INT_MAX && dist[u] + a->poids < dist[v]) {
                dist[v] = dist[u] + a->poids;
                precedent[v] = u;
            }
        a = a->suivant;
        }
    }
    if (dist[dest] == INT_MAX) {
    printf("Aucun chemin trouvé\n");
    return;
    }
    printf("Distance minimale : %d minutes\n", dist[dest]);
    printf("Chemin : ");
    afficher_chemin(precedent, src, dest, stations);
    printf("\n");
    return;
}

void trouver_chemin(station* stations, int nb_stations,HashTable* ht_nom) {
    char buf[32];                                                               //buffer dans lequel sera stocké le nom
    int choix;
    printf("Rechercher par :\n");
    printf("1 - Id\n");
    printf("2 - Nom\n");
    fgets(buf, sizeof(buf), stdin);                                             //le buffer est rempli au clavier avec stdin et fgets le lit
    choix = atoi(buf); 
    switch (choix) {
        case 1: {
            char buffer1[32];
            char buffer2[32];
            printf("Id station de départ : ");
            fgets(buffer1,sizeof(buffer1),stdin);
            int src = atoi(buffer1);
            printf("Id station d'arrivée : ");
            fgets(buffer2,sizeof(buffer2),stdin);
            int dest = atoi(buffer2);
            dijkstra(stations, nb_stations, src, dest);
            break;
        }
        case 2: {
            char nom_src[NAME];
            char nom_dest[NAME];
            printf("Nom station de départ : ");
            fgets(nom_src, NAME, stdin);
            nom_src[strcspn(nom_src, "\n")] = '\0';
            printf("Nom station d'arrivée : ");
            fgets(nom_dest, NAME, stdin);
            nom_dest[strcspn(nom_dest, "\n")] = '\0';
            int src = hash_find(ht_nom, nom_src);
            int dest = hash_find(ht_nom, nom_dest);
            if (src == -1 || dest == -1) {
                printf("Station inconnue\n");
                return;
            }
            dijkstra(stations, nb_stations, src, dest);
            break;
        }
        default:
            printf("Choix invalide\n");
            break;
    }
    return;
}
    


