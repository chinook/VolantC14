# 🟨 VolantC14 (2026-2027)

Code du **volant** (tableau de bord du pilote) du véhicule éolien **Chinook C14** — nouveaux écrans / UI.
Le volant affiche la télémétrie en temps réel sur un écran tactile et lit les 10 boutons physiques pour envoyer leur état au reste du véhicule par CAN.

> Base de départ : le code du VolantC12, réorganisé pour le C14 (2026-2027).

---

## 🧩 Matériel

- **MCU :** STM32U5A9 (Cortex-M33, 4 Mo de flash interne)
- **Écran :** Riverdi 5" tactile capacitif (LTDC + GPU2D intégrés)
- **OS :** FreeRTOS (multitâche)
- **Interface graphique :** TouchGFX 4.23.2
- **Bus :** CAN (FDCAN1, 125 kbit/s) vers Mario et le reste des PCBs

## 🛠️ Prérequis

- **STM32CubeIDE** (compilation, flash, debug)
- **TouchGFX Designer 4.23.2** (conception des écrans)
- **STM32CubeProgrammer** (flash / effacement, optionnel)

## 📁 Structure du repo

```
VolantC14/
├─ Core/           # Code C principal (main, GPIO, CAN, interruptions) — généré CubeMX + USER CODE
├─ Drivers/        # HAL + CMSIS (ST) — ne pas modifier
├─ Middlewares/    # FreeRTOS + moteur TouchGFX — ne pas modifier
├─ STM32CubeIDE/   # Projet IDE "Riverdi_50STM32U5A9" + code applicatif (screen_tasks.c, ui.h)
└─ TouchGFX/       # Interface graphique
   ├─ gui/         #   Notre code C++ (View / Presenter / Model)
   ├─ generated/   #   Code auto-généré par TouchGFX Designer — ne pas modifier à la main
   └─ assets/      #   Images, polices
assets/            # Ressources diverses du repo
```

## ▶️ Compiler et flasher la carte

1. Ouvrir le projet **`Riverdi_50STM32U5A9`** dans STM32CubeIDE
   (`File → Import → Existing Projects`, pointer sur `VolantC14/STM32CubeIDE/`).
2. **Build** (🔨).
3. **Run / Debug** via ST-LINK (SWD) pour flasher.

## 🖥️ Lancer le simulateur PC (sans carte)

Dans **TouchGFX Designer** : ouvrir `VolantC14/TouchGFX/*.touchgfx`, puis **Run Simulator** (F5).

En ligne de commande (Git Bash), avec le toolchain embarqué de TouchGFX :

```bash
cd VolantC14/TouchGFX
export PATH="/c/TouchGFX/4.23.2/env/MinGW/bin:/c/TouchGFX/4.23.2/env/MinGW/msys/1.0/bin:/c/TouchGFX/4.23.2/env/MinGW/msys/1.0/Ruby30-x64/bin:$PATH"
mingw32-make.exe -f simulator/gcc/Makefile && ./build/bin/simulator.exe
```

> ⚠️ Le chemin du projet ne doit **pas contenir d'espaces** (requis par le build TouchGFX).

## ⚠️ Ajouter des images : utiliser la flash INTERNE

Par défaut, TouchGFX range les images en **flash QSPI externe** (`ExtFlashSection`), dont la
programmation échoue sur cette carte → le flash plante (`Error: failed to erase memory`).

**Toujours mettre les images en `IntFlashSection`** (flash interne, 4 Mo dispo) :
TouchGFX Designer → **Images** → colonne **Section** → `IntFlashSection` (jamais `(Default)`).
Vérifie aussi les polices/textes. Au flash, le log doit montrer **uniquement** `Erasing internal memory`.

## 📡 Communication CAN (résumé)

- **Volant → Mario (`0x30`) :** état des 10 boutons encodés en bits.
- **Mario → Volant (`0x40`–`0x4F`) :** 16 valeurs de télémétrie (float).

## 📝 Convention

- Ne jamais modifier : `Drivers/`, `Middlewares/`, `TouchGFX/generated/`.
- Code custom STM32 : toujours entre `/* USER CODE BEGIN */` et `/* USER CODE END */`.
- Les produits de compilation (`Debug/`, `Release/`, `TouchGFX/build/`) sont ignorés par git.

## 📄 Licence

Apache License 2.0 — voir [LICENSE](LICENSE).

---

*Club Chinook — ÉTS*
