#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "station.h"
#include "tri.h"
#include "edge.h"
#include "hash.h"

int min_distance(int* dist, int* visite, int n);                                    //trouver le minimum parmi un tableau
void afficher_chemin(int* precedent, int src, int dest, station* stations);         //affichage pur
void dijkstra(station* stations, int nb_stations, int src, int dest);               //algo dijkstra
void trouver_chemin(station* stations, int nb_stations,HashTable* ht_nom);

#endif