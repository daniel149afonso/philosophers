# 🧠 Philosophers

## 🧾 Description du projet

Ce projet est une implémentation du **problème des philosophes** (Dining Philosophers Problem), un classique de la programmation concurrente. Il met en jeu :

- Des **threads** (un par philosophe)
- Des **mutex** (un par fourchette)
- De la **synchronisation** pour éviter les blocages ou famine
- Un **moniteur** qui surveille si un philosophe meurt

L’objectif est de faire manger, penser et dormir des philosophes **sans qu’aucun ne meure de faim** et **sans deadlock**.

---

## 🗃️ Fichiers

- `sources/` : tous les fichiers `.c` organisés
- `Makefile` : pour compiler automatiquement le projet
- `philo` : l’exécutable généré

---

## ⚙️ Compilation

#### ▶️ Pour compiler le projet :

```bash
make
```
#### ▶️ Pour recompiler le projet :

```bash
make re
```
####  🧹Pour nettoyer les .o uniquement :

```bash
make clean
```
####  🧹Pour nettoyer les .o et l'exécutable :

```bash
make fclean
```
####  🚀 Utilisation :

```bash
./philo.a [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

```
###  🧩 Paramètres :
Argument |	Description
number_of_philosophers:	Nombre de philosophes (et fourchettes)
time_to_die:	Temps max sans manger avant la mort (en ms)
time_to_eat:	Temps pour manger (en ms)
time_to_sleep:	Temps pour dormir (en ms)
number_of_times_each_philosopher_must_eat (optionnel):	Si fourni, la simulation se termine quand chaque philosophe a mangé ce nombre de fois

