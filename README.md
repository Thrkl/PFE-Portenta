# PFE-Portenta
Dépôt rassemblant les programmes conçu pour notre projet de fin d'études sur l'Arduino Portenta H7

Auteurs :
 - COSTE Raphaël
 - KALEM Tahar

## Comment utiliser le dépôt

Ce dépôt contient des programmes utilisé lors de notre projet. Il est est réparti en 3 parties :
 - Tests Arduino
 - Machine Learning
 - Tourelle Laser

## Tests Arduino
### Description
Ce dossier contient un projet Arduino de test d'éxecution simultanée des deux coeurs présent dans le SoC de la Portenta. Ce programme permet de flasher deux programmes distincts dans chacun des coeurs grâce à l'IDE Arduino.
En exécution, il boot les deux coeurs et programme le M7 pour faire clignoter la LED bleue à une certaine fréquence et programme le M4 pour faire clignoter la LED rouge à une autre fréquence. C'est un exemple d'illustration des capacités double-coeur que possède la Portenta.

Nous avons pu tester quelques autres fonctionnalités sur la Portenta, comme la communication inter-coeur en utilisant la procédure RPC implémentée par Arduino. Le code de ce projet peut être uploadé si besoin.

### Utilisation
Pour utiliser ce projet, il suffit de l'ouvrir sous l'IDE Arduino tout en possèdant le BSP de la Portenta pour pouvoir la programmer. Ensuite, si c'est la première fois que la Portenta doit être flashée par l'IDE Arduino (ou si elle n'est pas reconnue par l'IDE), il faut flasher son firmware. Pour cela, il faut la mettre en mode bootloader en double-cliquant sur son bouton reset. En mode bootloader, la board devrait être reconnu et flasher son M7 devrait automatiquement installer le firmware Arduino nécessaire pour plus tard la programmer avec des programmes Arduino.

Ensuite, lorsque la Portenta possède le firware Arduino, elle automatiquement reconnue par l'IDE, ainsi, pour flasher les programmes, il faut utiliser le même fichier et flasher le M7 et le M4 (on peut choisir chacun coeur dans "outils/Type de carte").
