# 🗺️ Réseau de Métro - Algorithme de Dijkstra

Implémentation de l'algorithme de Dijkstra sur un réseau de métro en C.

## 🛠️ Technologies
![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)

## 🎯 Fonctionnalités
- Chargement d'un réseau de métro depuis un fichier
- Recherche du plus court chemin entre deux stations
- Table de hachage pour accès rapide aux stations
- Algorithmes de tri sur les données du réseau
- Interface menu interactive

## ▶️ Compiler et lancer
```bash
make
./programme metro.txt
```

## 📐 Architecture
| Fichier | Rôle |
|--------|------|
| `main.c` | Point d'entrée |
| `dijkstra.c / .h` | Algorithme de Dijkstra |
| `station.c / .h` | Gestion des stations |
| `edge.c / .h` | Connexions entre stations |
| `hash.c / .h` | Table de hachage |
| `tri.c / .h` | Algorithmes de tri |
| `menu.c / .h` | Interface utilisateur |
| `metro.txt` | Données du réseau |# dijkstra-metro-c
