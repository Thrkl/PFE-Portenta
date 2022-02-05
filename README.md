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

## Machine Learning

### Description
Ce dossier contient les fichiers d'une application de Machine Learning que l'on a developpé en utilisant Edge Impulse et OpenMV.
C'est une application de reconnaissance faciale que l'on a entraîné avec nos visages (Tahar et Raphaël, les deux membres du groupe), cette application était donc destinée à nous distinguer.
Nous avons directement récolté les données de nos visages grâce à un script de détection de visage (disponible dans les exemples OpenMV) afin de ne capturer que nos visages pour entraîner notre modèle.
Puis, nous avons conçu et entraîné notre modèle avec ces données en utilisant la plateforme Edge Impulse.
Enfin, avec le fichier contenant le modèle entraîné "trained.tflite" nos pouvons utiliser une script OpenMV qui fera l'inférence.

### Utilisation
Pour exécuter cette application, il faut, d'abord, pouvoir utiliser la board avec l'IDE OpenMV. Ainsi, si ce n'est pas déjà fait, ou si un autre firmware est flashé sur la board, il faut flasher le firmware OpenMV.
Pour ce faire, il faut repasser la board en mode bootloader (double-click sur le bouton reset) et sous le logiciel OpenMV, lorsque la Portenta est en mode bootloader et connecté en USB à l'ordinateur, il faut cliquer sur l'icône de connection en bas à gauche, ce qui proposera automatiquement de flasher le firmware.

Une fois que le firmware OpenMV est flashé sur la carte, il faut déplacer les fichiers "labels.txt"(fichier contenant les labels possibles à savoir "raph" et "tahar") et "trained.tflite" (fichier contenant le modèle entraîné dans le système de fichier hebergé par la Portenta.
Enfin, il faut exécuter le script fourni "Face_recognition.py" avec OpenMV sur la Portenta.

Ce programme ne sait que distinguer les personnes entre les deux membres de notre groupe, il est donc pas forcément très pertinent de l'exécuter sans notre présence. Cependant, c'est un exemple d'exécution d'application de Deep Learning sur la Portenta et la reconnaissance de visage était un des exemples les plus //TOO
