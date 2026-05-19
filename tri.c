#include <stdio.h>
#include <stdlib.h>
#include "tri.h"

static long long nb_comparaisons = 0;
static long long nb_permutations = 0;
static long long nb_deplacements = 0;

void reset_comparaisons() {
    nb_comparaisons = 0;
}

long long get_comparaisons() {
    return nb_comparaisons;
}

void reset_permutations() {
    nb_permutations = 0;
}

long long get_permutations() {
    return nb_permutations;
}

void reset_deplacements() {
    nb_deplacements = 0;
}

long long get_deplacements() {
    return nb_deplacements;
}

void afficher_ordre(station* stations, int* ordre, int n) {
    for (int i = 0; i < n; i++) {
        station* s = &stations[ordre[i]];
        printf("%s (id=%d, degré=%d)\n", s->nom, s->id, degre_station(s));
    }
}

void tri_selection(station* stations, int* ordre, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++) {
            if (++nb_comparaisons && degre_station(&stations[ordre[j]]) > degre_station(&stations[ordre[max]])) {
                max = j;
            }
        }
        if (max != i) {
            int tmp = ordre[i];
            ordre[i] = ordre[max];
            ordre[max] = tmp;
            nb_permutations++;
        }
    }
}

void tri_insertion(station* stations, int* ordre, int n) {
    for (int i = 1; i < n; i++) {
        int key = ordre[i];
        int j = i - 1;
        while (j >= 0 && (++nb_comparaisons && degre_station(&stations[ordre[j]]) < degre_station(&stations[key]))) {
            ordre[j + 1] = ordre[j];
            nb_deplacements++;
            j--;
        }
        ordre[j + 1] = key;
        nb_deplacements++;
    }
}

int partition(station* stations, int* ordre, int low, int high) {
    int pivot = ordre[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (++nb_comparaisons && degre_station(&stations[ordre[j]]) > degre_station(&stations[pivot])) {
            i++;
            int tmp = ordre[i];
            ordre[i] = ordre[j];
            ordre[j] = tmp;
            nb_permutations++;
        }
    }
    int tmp = ordre[i + 1];
    ordre[i + 1] = ordre[high];
    ordre[high] = tmp;
    return i + 1;
    nb_permutations++;
}

void quicksort_simple(station* stations, int* ordre, int n) {               //quick sort avec une stack 
    int stack[n];                                                           //pile pour éviter la récursion
    int top = -1;
    stack[++top] = 0;
    stack[++top] = n - 1;
    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];
        int p = partition(stations, ordre, low, high);
        if (p - 1 > low) {
            stack[++top] = low;
            stack[++top] = p - 1;
        }
        if (p + 1 < high) {
            stack[++top] = p + 1;
            stack[++top] = high;
        }
    }
}

void quicksort_rec(station* stations, int* ordre, int low, int high) {      //"vrai" quicksort 
    if (low < high) {
        int p = partition(stations, ordre, low, high);
        quicksort_rec(stations, ordre, low, p - 1);
        quicksort_rec(stations, ordre, p + 1, high);
    }
}

void afficher_stations_triees(station* stations, int nb_stations, int choix) {
    int* ordre = malloc(nb_stations * sizeof(int));                             //allocation du tableau dans lequel sera stocké l'ordre des stations
    if (!ordre) {return;}                                                       //gestion de l'erreur
    for (int i = 0; i < nb_stations; i++) {
        ordre[i] = i;
    }
    switch (choix) {
        case 1:
            printf("=== Résultat du tri ===\n");
            reset_comparaisons();
            reset_permutations();
            reset_deplacements();
            printf("Algorithme utilisé: Tri par sélection\n");
            tri_selection(stations, ordre, nb_stations);
            break;
        case 2:
            printf("=== Résultat du tri ===\n");
            reset_comparaisons();
            reset_permutations();
            reset_deplacements();
            printf("Algorithme utilisé: Tri par insertion\n");
            tri_insertion(stations, ordre, nb_stations);
            break;
        case 3:
            printf("=== Résultat du tri ===\n");
            reset_comparaisons();
            reset_permutations();
            reset_deplacements();
            printf("Algorithme utilisé: Quick sort récursif\n");
            quicksort_rec(stations, ordre, 0, nb_stations - 1);
            break;
        case 4:
            printf("=== Résultat du tri ===\n");
            reset_comparaisons();
            reset_permutations();
            reset_deplacements();
            printf("Algorithme utilisé: Quick sort itératif\n");
            quicksort_simple(stations, ordre, nb_stations);
            break;
        default:
            printf("Choix invalide\n");
            free(ordre);
            return;
    }
    afficher_ordre(stations, ordre, nb_stations);
    printf("Comparaisons : %lld\n", get_comparaisons());
    printf("Permutations : %lld\n", get_permutations());
    printf("Déplacements : %lld\n", get_deplacements());
    free(ordre);                                                        //libération de la mémoire puisque l'on n'a plus besoin de ordre
}

void afficher_tri(station* stations, int nb_stations) {                 //fonction pour le main
    char buf2[32];
    printf("Choisir l'algorithme de tri :\n");
    printf("1 - Sélection\n");
    printf("2 - Insertion\n");
    printf("3 - Quick sort récursif\n");
    printf("4 - Quick sort itératif\n");
    fgets(buf2, sizeof(buf2), stdin);
    int algo = atoi(buf2);
    afficher_stations_triees(stations, nb_stations, algo);              //fonction précédente
    return;
}