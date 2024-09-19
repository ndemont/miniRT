# Raytracing

<img src="/images/all.bmp" alt="Image"/>

## subject

This project is an introduction to the beautiful world of Raytracing.
It allows to render simple Computer-Generated-Images.

The goal of your the program is to generate images
using the Raytracing protocol. Those computer
generated images will each represent a scene, as
seen from a specific angle and position, defined
by simple geometric objects, and each with its own
lighting system.

## binary

- `minirt [file] [--save]`

Receives a file containing the informations relative to a specific scenes.

The program displays the scene in a window or saves it in a bmp file with the --save flag.

## objects

**resolution** `R 1920 1080`

- identifier: R

- x render size

- y render size

**ambient lightning** `A 0.2 255,255,255`

- identifier: A

- ambient lighting ratio in range [0.0,1.0]: 0.2

- R,G,B colors in range [0-255]: 255, 255, 255

**camera** `c -50.0,0,20 0,0,1 70`

- identifier: c

- x,y,z coordinates of the view point: 0.0,0.0,20.6

- 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0

- FOV : Horizontal field of view in degrees in range [0,180]

**light** `l -40.0,50.0,0.0 0.6 10,0,255`

- identifier: l

- x,y,z coordinates of the light point: 0.0,0.0,20.6

- the light brightness ratio in range [0.0,1.0]: 0.6

- R,G,B colors in range [0-255]: 10, 0, 255

**sphere** `sp 0.0,0.0,20.6 12.6 10,0,255`

- identifier: sp

- x,y,z coordinates of the sphere center: 0.0,0.0,20.6

- the sphere diameter: 12.6

- R,G,B colors in range [0-255]: 10, 0, 255

**plan** `tr 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`

- identifier: pl

- x,y,z coordinates: 0.0,0.0,-10.0

- 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0

- R,G,B colors in range [0-255]: 0, 0, 255

**triangle** `tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255`

- identifier: tr

- x,y,z coordinates of the first point: 10.0,20.0,10.0

- x,y,z coordinates of the second point: 10.0,10.0,20.0

- x,y,z coordinates of the third point: 20.0,10.0,10.0

- R,G,B colors in range [0,255]: 0, 255, 255

**square** `sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255`

- identifier: sq

- x,y,z coordinates of the square center: 0.0,0.0,20.6

- 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 1.0,0.0,0.0

- side size: 12.6

- R,G,B colors in range [0-255]: 255, 0, 255

**cylinder** `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`

- identifier: cy

- x,y,z coordinates: 50.0,0.0,20.6

- 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0

- the cylinder diameter: 14.2

- the cylinder height: 21.42

- R,G,B colors in range [0,255]: 10, 0, 255


## bonus

**filters** `f`

- red
- green
- blue
- black and white
- negative

**camera position** `arrows`

- x
- y
- z

**camera direction** `wasd`
- x
- y 
- z
