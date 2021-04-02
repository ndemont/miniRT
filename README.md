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

**sphere**: swap a - swap the first 2 elements at the top of stack a. Do nothing if there
is only one or no elements).

**plan**: swap b - swap the first 2 elements at the top of stack b. Do nothing if there
is only one or no elements).

**triangle**: sa and sb at the same time.

**square**: push a - take the first element at the top of b and put it at the top of a. Do
nothing if b is empty.

**cylinder**: push b - take the first element at the top of a and put it at the top of b. Do
nothing if a is empty.

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
