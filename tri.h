#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "station.h"

#ifndef TRI_H
#define TRI_H

void reset_comparaisons();
long long get_comparaisons();

void reset_permutations();
long long get_permutations();

void reset_deplacements();
long long get_deplacements();

void tri_selection(station* stations, int* ordre, int n);
void tri_insertion(station* stations, int* ordre, int n);
void quicksort_rec(station* stations, int* ordre, int low, int high);
void quicksort_simple(station* stations, int* ordre, int n);
void afficher_ordre(station* stations, int* ordre, int n);
int partition(station* stations, int* ordre, int low, int high);
void afficher_stations_triees(station* stations, int nb_stations, int choix);
void afficher_tri(station* stations, int nb_stations);

#endif