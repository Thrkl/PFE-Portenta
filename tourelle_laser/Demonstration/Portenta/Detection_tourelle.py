# Detection_tourelle - By: tahar - raphael - dim. janv. 23 2022

import sensor, image, time, math, pyb
from pyb import UART

#Led pour debug
led = pyb.LED(3)

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

#Initialisation du module UART pour transmettre les coordonnées
uart = UART(1, 9600, timeout_char=100)
uart.init(9600, bits=8, parity=None, stop=1, timeout_char=1000)

#Il y a plusieurs types d'AprilTags
#   On choisit de détecter les TAG16 qui sont plus faciles à détecter de loin (4x4)
tag_families = 0
tag_families |= image.TAG16H5
#tag_families |= image.TAG25H7 # Non détecté
#tag_families |= image.TAG25H9 # Non détecté
#tag_families |= image.TAG36H10 # Non détecté
#tag_families |= image.TAG36H11 # Non détecté
#tag_families |= image.ARTOOLKIT # Non détecté

while(True):
    clock.tick()
    img = sensor.snapshot()
    for tag in img.find_apriltags(families=tag_families):
        led.on()
        # Lorsque un tag est détecté on dessine une cible sur l'image pour le repérer
        img.draw_rectangle(tag.rect(), color = (255, 0, 0))
        img.draw_cross(tag.cx(), tag.cy(), color = (0, 255, 0))

        #On affiche des coordonnées
        print_args = (tag.cx(), tag.cy())

        print("tag x=%i   tag y =%i"%print_args)

        #On envoie ses coordonnées en UART (1 octet par coordonnée)
        uart.writechar(tag.cx())
        uart.writechar(tag.cy())
        led.off()
