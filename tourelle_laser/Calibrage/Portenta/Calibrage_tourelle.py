# Calibrage_tourelle.py - By: tahar - raphael - sam. janv. 22 2022

import sensor, image, time

#Paramètres supportés par le vision shield
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QVGA)

#La détection de tag n'est pas disponible pour des images >64K pixels
#On adapte la résolution
sensor.set_windowing((250,250))  #250*250 = 62500
sensor.skip_frames(time = 2000)

#Paramètres de capture de la caméra pour améliorer la détection (à ajuster en fonction de l'environnement)
sensor.set_auto_gain(False)

#Pour compter les images par secondes
clock = time.clock()

#La calibration demande plusieurs étapes
#   A chaque étape, une croix sera affichée sur le retour caméra,
#   il s'agira de placer le laser grâce au joystick sur cette croix et relever le couple (coordonnées de la croix, angles des servos)
#   Les données de calibration seront donc traitées par un script python externe
étape = 0   # 0 => Calibration horizontale; 1 => Calibration verticale
croix = 0   # numéro du point à viser

nbcroix = 12 # nombre de points à viser pour chaque type de calibration

#Placement des croix pour phase de calibration
r = 0
g = 0
b = 0
if (étape == 0):
    y = 125
    x = int(croix * (250/(nbcroix-1)))
else:
    x = 125
    y = int(croix * (250/(nbcroix-1)))

#Print les coordonnées visées
print_args = (x, y)
print("Point calibration x=%i   tag y =%i"%print_args)

while(True):
    clock.tick()
    img = sensor.snapshot() #On récupère l'image
    img.draw_cross(x, y, color = (r, g, b), size = 10, thickness = 1)   #On dessine la croix sur l'image
