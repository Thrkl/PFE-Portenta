# Face Recognition - By: tahar - raphael - dim. janv. 23 2022
#
# Ce script s'utilise avec un modèle TensorFlow Lite entraîné "trained.tflite" stocké dans le système de fichier pour faire de la reconnaissance faciale

import sensor, image, time, tf

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()

net = tf.load("trained.tflite", load_to_fb=True)
labels = [l.rstrip('\n') for l in open("labels.txt")]

while(True):
    clock.tick()

    # Take a picture and brighten things up for the frontal face detector.
    img = sensor.snapshot().gamma_corr(contrast=1.5)

    # Returns a list of rects (x, y, w, h) where faces are.
    faces = img.find_features(image.HaarCascade("frontalface"))

    for f in faces:

        # Classify a face and get the class scores list
        test = net.classify(img, roi=f)[0]
        scores = net.classify(img, roi=f)[0].output()

        # Find the highest class score and lookup the label for that
        label = labels[scores.index(max(scores))]

        # Draw a box around the face
        img.draw_rectangle(f)

        # Draw the label above the face
        img.draw_string(f[0]+3, f[1]-1, label, mono_space=False)
        print(scores)

    #print(clock.fps())
