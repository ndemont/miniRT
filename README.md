# miniRT

## subject

This project is an introduction to the beautiful world of Raytracing.
Once completed you will be able to render simple Computer-Generated-Images and you
will never be afraid of implementing mathematical formulas again.

The goal of your program is to generate images
using the Raytracing protocol. Those computer
generated images will each represent a scene, as
seen from a specific angle and position, defined
by simple geometric objects, and each with its own
lighting system.

## binary

- `push_swap [-cvs] [--dst] [file ...] [arguments ...]`

Receives a list of integer arguments as a pile and generates the instructions used to sort that pile.


- `checker [-cvs] [--src] [file ...] [arguments ...]`

Checks if the list of instructions you’ll generate with the program push_swap is actually sorting the stack properly.

## objects

**sphere** `sp 0.0,0.0,20.6 12.6 10,0,255`

· identifier: sp

· x,y,z coordinates of the sphere center: 0.0,0.0,20.6

· the sphere diameter: 12.6

· R,G,B colors in range [0-255]: 10, 0, 255

**plan** `0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`

· identifier: pl

· x,y,z coordinates: 0.0,0.0,-10.0

· 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0

· R,G,B colors in range [0-255]: 0, 0, 255

**triangle** `tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255`

· identifier: tr

· x,y,z coordinates of the first point: 10.0,20.0,10.0

· x,y,z coordinates of the second point: 10.0,10.0,20.0

· x,y,z coordinates of the third point: 20.0,10.0,10.0

· R,G,B colors in range [0,255]: 0, 255, 255

**square** `sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255`

· identifier: sq

· x,y,z coordinates of the square center: 0.0,0.0,20.6

· 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 1.0,0.0,0.0

· side size: 12.6

· R,G,B colors in range [0-255]: 255, 0, 255

**cylinder** `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`

· identifier: cy

· x,y,z coordinates: 50.0,0.0,20.6

· 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0

· the cylinder diameter: 14.2

· the cylinder height: 21.42

· R,G,B colors in range [0,255]: 10, 0, 255

## bonus

**command**
- `ruby -e "puts (a..b).to_a.shuffle.join(' ')"` - generates a set of integers between a and b in a random order.

**flags**
- `-v` visual - displays the piles at each state. (can only be used with --dst for push_swap)
- `-c` color - displays in colors.
- `-s` sticks - displays the piles with sticks. (can only be used with `-v`)
- `--dst file` destination - saves the instructions in the precised file. (option for push_swap)
- `--src file` source - reads the instructions from the precised file. (option for checker) 

**tester**
- `tester.sh` - tests the number of operations and displays an error according to the limits of your choice.

## allowed functions

- `open`
- `close`
- `read`
- `write`
- `printf`
- `malloc`
- `free`
- `perror`
- `strerror`
- `exit`
- `math.h`
- `minilibx.h`
