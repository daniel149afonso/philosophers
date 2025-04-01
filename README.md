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
- `objs/` : dossier de compilation des `.o`
- `Makefile` : pour compiler automatiquement le projet
- `philo.a` : l’exécutable généré

---

## ⚙️ Compilation

### ▶️ Pour compiler le projet :

```bash
make
