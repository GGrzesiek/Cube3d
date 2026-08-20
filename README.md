# cub3D

A Wolfenstein-3D-style raycaster in C using MiniLibX. 42 School project, cub3D v12.0.

Given a `.cub` scene file describing four wall textures, a floor and ceiling colour, and a grid map,
the program renders a real-time first-person view inside the maze.

Built by two people along a parser/renderer seam:

- **parser** (`src/parsing/`) — reading and validating the `.cub` file
- **renderer** (`src/engine/`, `src/render/`) — window, input, movement, raycasting, textures

## Build

```
make            # builds libft.a, then ./cub3D
make re         # full rebuild
make clean      # remove obj/
make fclean     # also remove the binary
```

MiniLibX is expected in `./mlx_linux` and is not committed. The Makefile reaches it through a single
`MLX_PATH` variable, so pointing the build at a system install is a one-line change.

## Run

```
./cub3D maps/valid/basic.cub
```

| Key | Action |
|---|---|
| `W` `S` | walk forward / back |
| `A` `D` | strafe left / right |
| `←` `→` | turn |
| `ESC` | quit |

The window's close button also exits cleanly.

## How it renders

For each of the 1024 screen columns the renderer casts one ray, walks the grid with a DDA loop until
it meets a wall, converts the perpendicular distance to a wall-slice height, and draws that slice
sampled from the texture of the wall face it hit. Floor and ceiling are flat colours.

The camera is stored as two vectors rather than an angle: `dir` (where you look) and `plane`
(perpendicular to it, its length setting the 66° field of view). A screen column maps to
`dir + plane * camera_x` with `camera_x` running from -1 to +1.

Using the *perpendicular* distance to the camera plane, rather than the euclidean distance to the
camera point, is what keeps flat walls flat instead of curving them away at the edges.

Key presses and releases set flags in a `keys[]` array which the frame loop polls, so held keys give
smooth movement and two keys at once give diagonals. All movement and rotation is multiplied by the
measured frame time, so speed does not depend on the frame rate.

## Layout

```
include/cube.h      shared contract: t_scene, t_ray, t_game, constants
src/main.c          argument check, parse, run
src/parsing/        .cub file reading and validation
src/engine/         run_game, hooks, player state, movement, rotation
src/render/         frame loop, ray setup, DDA, column drawing, textures
src/utils/          error reporting, cleanup
tools/              png_to_xpm.py, converts the wall textures to xpm
maps/               scene files
```

## Current state

The renderer is complete and runs against a hand-filled scene while map parsing is being finished:
`src/render/stub_scene.c` supplies the grid, colours and start position, and the parser supplies the
texture paths. That file and its call in `main.c` are deleted once `parse_map` lands.

## Use of AI

<!-- TODO: describe here how AI tools were or were not used on this project. -->
