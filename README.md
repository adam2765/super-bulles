# super-bulles
## Structure du projet

main.c                      → point d'entrée, init Allegro, menu
jeu.c / jeu.h               → boucle de jeu, logique globale, niveaux
entites.c / entites.h       → joueur, bulles, projectiles
collision.c / collision.h   → détection des collisions
affichage.c / affichage.h   → rendu graphique Allegro 4
input.c / input.h           → clavier, actions du joueur
sauvegarde.c / sauvegarde.h → lecture/écriture fichier

## 📋 Workflow pour l'équipe

### Avant de commencer à coder
```bash
git pull
```

### Pendant que tu codes
```bash
git add .
git commit -m "ce que t'as fait"
```
Exemples de messages :
- "ajout mouvement joueur"
- "correction bug collision bulle"
- "menu principal fait"

### À la fin de ta session
```bash
git push
```

### ⚠️ Règles importantes
1. Toujours `git pull` avant de commencer
2. Toujours `git push` avant de fermer l'ordi
3. Ne pas toucher au fichier d'un coéquipier sans le prévenir
4. Si y'a un bug après un push → prévenir le groupe sur le chat
