#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "station.h"
#include "hash.h"


int stocke_id(FILE* fic, int* ids) {                                //le tableau ids est passé en argument pour pouvoir ensuite y stocker les id
    int index = 0;
    char txt[TAILLE];                                               //tableau de caractères nécessaire à la lecture du fichier
    int id;
    while (fgets(txt,TAILLE,fic)!=NULL) {                           //lecture par ligne
        int doublon=0;                                          
        if (sscanf(txt,"STATION;%d",&id) == 1) {                    //ignore automatiquement les lignes qui ne sont pas sous le format "STATION;id"
            for (int i=0;i<index;i++) {
                if (ids[i] == id) {                                 //vérification d'un éventuel doublon
                    doublon = 1;
                    break;                                          //s'il y en a bel et bien un on l'ignore
                }
            }
            if (doublon != 1 && index < 130) {                      //s'il n'y a pas de doublon et que l'on arrive pas à la limite du tableau :
                ids[index++] = id;                                  //remplissage habituel
            }
        }
    }
    return index;                                                   //retourne le nombre de stations
}

int stocke_id_et_noms(FILE* fic, int* ids, char names[][NAME]) {   //les tableaux ids et names sont passés en arguments pour pouvoir y stocker les informations                
    int index = 0;
    char txt[TAILLE];                                               //tableau de caractère nécessaire à la lecture du fichier   
    char name[NAME];                                                //tableau dans le quel on va récupérer chaque nom un par un
    int id;                                                         //idem pour l'id
    while (fgets(txt,TAILLE,fic)!=NULL) {                           //lecture ligne par ligne
        int doublon=0;                                              
        if (sscanf(txt,"STATION;%d;%49[^\n]",&id,name) == 2) {      //copie l'id et le nom jusqu'à la fin de la ligne (NAME = 49 + \0)           
            for (int i=0;i<index;i++) {
                if (ids[i] == id) {                                 //regarde s'il y a un doublon des les id déjà présents       
                    doublon = 1;
                    break;                                          //si oui on l'ignore
                }
            }
            if (doublon != 1 && index < 130) {                      //dans le cas contraire :
                ids[index] = id;                                    //on remplit le tableau des id
                strcpy(names[index],name);                          //idem pour les noms
                index++;                             
            }
        }
    }
    return index;                                                   //retourne le nombre total de stations
}                                         

int trouver_station(station* stations, int nb_stations, int id) {
    for (int i = 0; i < nb_stations; i++) {
        if (stations[i].id == id) {
            return i;                                               // index trouvé
        }
    }
    return -1;                                                      // pas trouvée
}

int degre_station(station* s) {                                     //calcule le degré d'une station (nombre de voisins)
    int deg = 0;
    arc* courant = s->adj;
    while (courant != NULL) {                                       //s'assure toujours que l'arc n'est pas nul
        deg++;
        courant = courant->suivant;                                 //regarde récursivement chaque voisin
    }
    return deg;
}

void afficher_par_id(station* stations, int nb_stations) {
    int id;
    char b[32];                                                             //buffer pour l'entrée au clavier
    printf("Entrez l'id de la station : ");
    fgets(b,sizeof(b),stdin);                                              //lit b remplit par le clavier
    id = atoi(b);
    int index = trouver_station(stations, nb_stations, id);
    if (index == -1) {                                                  //id incohérent
        printf("Station inexistante\n");
        return;
    }
    station* s = &stations[index];                                  //on récupère les informations de la station
    printf("=== Informations station ===\n");
    printf("Id    : %d\n", s->id);
    printf("Nom   : %s\n", s->nom);
    printf("Degré : %d\n", degre_station(s));
}

/*scanf() laisse un \n à la fin de la chaine de caractère bloquant le bon fonctionnement du code,
donc la méthode buffer > fgets > atoi() a été adoptée*/

void afficher_station(station* stations, int nb_stations, HashTable* ht_nom) {
    char buf[32];                                                               //buffer dans lequel sera stocké le nom
    int choix;
    printf("Rechercher par :\n");
    printf("1 - Id\n");
    printf("2 - Nom\n");
    fgets(buf, sizeof(buf), stdin);                                             //le buffer est rempli au clavier avec stdin et fgets le lit
    choix = atoi(buf);                                                          //prend 3 si "3sfjh" est rentré par exemple
    switch (choix) {
        default:                                                                //si on a autre chose que 1 ou 2 en entrée
            printf("Merci de bien choisir une des deux options\n");
            break;
        case 1:
            afficher_par_id(stations, nb_stations);
            break;
        case 2: {
            char name[NAME];
            printf("Entrez le nom de la station : ");
            fgets(name, NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            int index = hash_find(ht_nom, name);
            if (index == -1) {
                printf("Station inexistante\n");
                return;
            }
            station* s = &stations[index];
            printf("=== Informations station ===\n");
            printf("Id    : %d\n", s->id);
            printf("Nom   : %s\n", s->nom);
            printf("Degre : %d\n", degre_station(s));
        }    
    }
}

void afficher_voisins_par_id(station* stations, int nb_stations) {
    int id;
    char b[32];
    printf("Entrez l'id de la station : ");
    fgets(b,sizeof(b),stdin);
    id = atoi(b);
    int index = trouver_station(stations, nb_stations, id);
    if (index == -1) {
        printf("Station inexistante\n");
        return;
    }
    station* s = &stations[id];
    printf("=== Liste des voisins de %s (id = %d) ===\n",s->nom,s->id);
    arc* courant = s->adj;
    if (courant == NULL) {
        printf("Aucun voisin trouvé\n");
        return;
    }
    while (courant != NULL) {
        station* voisin = &stations[courant->destination];
        printf("%d - %s (%d minutes)\n", voisin->id, voisin->nom, courant->poids);
        courant = courant->suivant;
    }
}

void afficher_voisins(station* stations, int nb_stations, HashTable* ht_nom) {
    char buf[32];                                                               //buffer dans lequel sera stocké le nom
    int choix;
    printf("Rechercher par :\n");
    printf("1 - Id\n");
    printf("2 - Nom\n");
    fgets(buf, sizeof(buf), stdin);                                             //le buffer est rempli au clavier avec stdin et fgets le lit
    choix = atoi(buf);                                                          //prend 3 si "3sfjh" est rentré par exemple
    switch (choix) {
        default:                                                                //si on a autre chose que 1 ou 2 en entrée
            printf("Merci de bien choisir une des deux options\n");
            break;
        case 1:
            afficher_voisins_par_id(stations, nb_stations);
            break;
        case 2: {
            char name[NAME];
            printf("Entrez le nom de la station : ");
            fgets(name, NAME, stdin);                                           //lit le nom
            name[strcspn(name, "\n")] = '\0';                                   //enlève le \0
            int index = hash_find(ht_nom, name);                                //trouve l'index de la station dans la hash table
            if (index == -1) {
                printf("Stations inexistante\n");
                return;
            }
            station* s = &stations[index];
            printf("=== Liste des voisins de %s (id = %d) ===\n",s->nom,s->id);
            arc* courant = s->adj;
            if (courant == NULL) {
                printf("Aucun voisin trouvé\n");
                return;
            }
            while (courant != NULL) {
            station* voisin = &stations[courant->destination];
            printf("%d - %s (%d minutes)\n", voisin->id, voisin->nom, courant->poids);
            courant = courant->suivant;
            }
            break;
        }    
    }
    return;
}

