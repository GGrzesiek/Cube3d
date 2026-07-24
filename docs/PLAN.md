# cub3D — Project Understanding & Build Plan

## Context

This repository targets **cub3D v12.0** — a Wolfenstein-3D-style raycaster in C using MiniLibX. The
subject is `cube3d.pdf` at the repo root. At the time of writing, no source code exists yet; the
repo holds the subject, an empty `.gitignore`, and this document.

The goal is a **perfect mandatory part** (no bonuses), built by **two people in parallel** along a
parser/renderer seam, with **@ggrzesiek learning by writing the code** — I explain the theory and
structure of each module, you write it, I review. This working style is not optional polish: the
subject's Chapter IV states that code you cannot justify at defense fails the project, and both
teammates receive the same grade and can be asked about any part.

Because the split is "clean parser / renderer", the accepted risk is that each person only writes
half. The plan mitigates this with a mandatory cross-teach gate before defense and a PR review step
where the *reviewer* must be able to explain the code before it merges.

---

## Part 1 — What the project actually is

Given a `.cub` scene file, render a real-time first-person view inside a maze.

**Scene file format** (all 6 elements required, exactly once, any order, map always last):

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111111
1000000001
10000N0001
1111111111
```

Map chars: `0` floor, `1` wall, `N/S/E/W` player start + facing, and spaces (valid, and yours to
handle). Map must be closed by walls. Any malformed input → print `Error\n` + your own explicit
message, exit cleanly.

**Rendering:** for each of the 800 screen columns, cast a ray, walk the grid with DDA until it hits
a `1`, convert distance to a wall-slice height, and draw that slice textured — with a *different*
texture per wall face (N/S/E/W). Floor and ceiling are flat colors.

**Controls:** `W A S D` move, `←` `→` rotate, `ESC` and the window's red X both quit cleanly.

**Hard constraints:**
- 42 Norm. Bonus files count too; a norm error is a **0**.
- No segfault / bus error / double free, ever. Any crash = **0**.
- Zero memory leaks.
- Makefile with `all clean fclean re bonus`, flags `-Wall -Wextra -Werror`, no relinking.
- Allowed externals only: `open close read write printf malloc free perror strerror exit
  gettimeofday`, all of `-lm`, all of MiniLibX. **`printf` itself is allowed — ft_printf is not
  needed.**
- README.md in 42 format, in English, including an AI-usage section.

**Where the grade actually dies:** not the raycaster. It's the parser — evaluators throw a pile of
malformed `.cub` files at you and check for leaks. Modules 3, 5 and 6 below carry the most risk.

---

## Part 2 — Environment (verified on this machine)

| Thing | Status |
|---|---|
| MiniLibX | `Projects/fractol/mlx_linux/` — already built. `libmlx_Linux.a` exports `mlx_xpm_file_to_image`, `mlx_loop_hook`, `mlx_hook`, `mlx_destroy_display`, `mlx_mouse_*`. **Copy this directory in.** |
| Link line | `-Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz` — proven working via your fract-ol Makefile |
| System libs | `libX11.so` and `libXext.so` present. `libXpm` dev headers are **absent but not needed** — this MiniLibX has its own XPM parser (`mlx_int_parse_xpm`) |
| libft | `Projects/Libft/` is the complete one (has the `ft_lst*` `bonus` rule). `Projects/libft/` lacks it — **copy `Libft`** |
| get_next_line | `Projects/getnextline/` — but it redefines `ft_strjoin`, `ft_strchr`, `ft_strlen`, which **collide at link time** with libft. Must be resolved on day 1 (see below) |
| norminette | Installed at `~/.local/bin/norminette` |
| Textures | No `.xpm` assets, no ImageMagick. Python 3.12 + PIL 10.2 available → generate textures with a throwaway script |
| X11 constants | `ESC=65307`, `←=65361`, `→=65363`, `KeyPress=2`, `KeyRelease=3`, `DestroyNotify=17`, `KeyPressMask=1`, `KeyReleaseMask=2`, `StructureNotifyMask=(1L<<17)` |

---

## Part 3 — Day 1, together (do not split before this is done)

Both people at one keyboard. Nothing parallel starts until `cub3d.h` is committed.

### 3.1 Repo + skeleton

```
Cube3d/
├── Makefile
├── README.md
├── .gitignore              # *.o, cub3D, valgrind out
├── includes/cub3d.h        # THE CONTRACT — frozen day 1
├── libft/                  # copied from Projects/Libft (+ gnl merged)
├── mlx_linux/              # copied from Projects/fractol/mlx_linux
├── srcs/
│   ├── main.c
│   ├── parse/              # Person A
│   ├── render/             # Person B
│   ├── engine/             # Person B
│   └── utils/              # error.c + cleanup.c: shared, edit with care
├── textures/*.xpm
├── maps/valid/  maps/invalid/
└── tools/gen_textures.py   run_tests.sh
```

**get_next_line merge (do this first, it blocks the Makefile):** delete `ft_strjoin`, `ft_strchr`,
`ft_strlen` from `get_next_line_utils.c`, keep only `ft_read_to_stash`, `ft_get_line`,
`ft_update_stash`, `cleanup`, and let it use libft's versions. Note libft's `ft_strjoin` frees
neither argument while gnl's version frees `s1` — **the gnl code must be adjusted for that
difference**, not just recompiled. Add `get_next_line.c` + utils to `libft/Makefile`'s `SRCS`.

### 3.2 The contract — `includes/cub3d.h`

This is the only file both people touch. Freeze it, then treat changes as a joint decision.

```c
# define WIN_W 1280
# define WIN_H 720
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

typedef struct s_img {
    void  *ptr;  char *addr;
    int   bpp;   int  line_len;  int endian;
    int   width; int  height;
} t_img;

typedef struct s_map {
    char  **grid;      /* space-padded rectangle */
    int   width;
    int   height;
} t_map;

typedef struct s_scene {          /* <-- Person A fills this, Person B consumes it */
    char      *tex_path[4];       /* indexed by TEX_NO..TEX_EA */
    int       floor;              /* 0x00RRGGBB, -1 = unset */
    int       ceiling;
    t_map     map;
    double    start_x;            /* cell centre: (col + 0.5) */
    double    start_y;
    char      start_dir;          /* 'N' 'S' 'E' 'W' */
} t_scene;
```

**The entire seam is two functions:**

```c
int   parse_scene(const char *path, t_scene *scene);  /* 0 = ok, 1 = error */
void  free_scene(t_scene *scene);                     /* idempotent, partial-state safe */
int   run_game(t_scene *scene);
```

`main.c` in full:

```c
int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
        return (error_msg("usage: ./cub3D <scene.cub>"));
    if (parse_scene(argv[1], &scene))
        return (1);
    return (run_game(&scene));
}
```

Person B writes a throwaway `stub_scene.c` that fills a `t_scene` by hand and works against it until
A's parser merges. **Neither person's code is ever blocked on the other's.**

### 3.3 Norm-driven design decision — the ray struct

The Norm's 25-line function limit makes a textbook DDA loop impossible with loose locals. Bundle
ray state in a struct from the start; retrofitting this later is painful:

```c
typedef struct s_ray {
    double dir_x;    double dir_y;
    double side_x;   double side_y;    /* running sideDist */
    double delta_x;  double delta_y;
    double perp_dist;
    int    map_x;    int    map_y;
    int    step_x;   int    step_y;
    int    side;                       /* 0 = x-side hit, 1 = y-side hit */
    int    line_h;   int draw_start;   int draw_end;
    int    tex_id;
} t_ray;
```

(One declaration per line in the real file — the above is compressed for readability.)

Same reasoning for `t_game`, which holds `mlx`, `win`, `frame`, `tex[4]`, the `t_scene`, player
`pos/dir/plane` doubles, and a `keys[6]` held-key array.

### 3.4 Day-1 spike: prove XPM loading works (30 min, do not skip)

MiniLibX's XPM parser accepts only a subset of the format and fails **silently** by returning NULL.
Discovering this on day 10 costs a day. Write `tools/gen_textures.py` (PIL → hand-written XPM3
output, 64×64, `c #RRGGBB` colors), generate four visually distinct textures, and confirm
`mlx_xpm_file_to_image` returns non-NULL for all four before writing anything else.

64×64 matters: a power-of-two height lets `texY & 63` replace a modulo and keeps the step math
clean.

### 3.5 Makefile

- Build `libft/libft.a` by recursing into its own Makefile (subject requirement).
- Objects depend on `includes/cub3d.h` so editing the contract rebuilds everything, but nothing
  relinks when nothing changed.
- Include a `bonus:` rule — the subject's table requires it. `bonus: all` is fine for mandatory-only.
- Compile with `-Imlx_linux -Iincludes -Ilibft -O2`.

---

## Part 4 — Person A: the parser track

Files under `srcs/parse/` and `srcs/utils/`. Owns modules 2, 3, 4, 5, 6, 13.

### A1 — `parse_scene.c` (module 2)
Validate the argument ends in `.cub` (and is longer than 4 chars), `open()` it, read every line with
`get_next_line`. **Gotcha:** on Linux `open()` on a *directory* succeeds and `read()` then fails with
`EISDIR` — handle it or you crash on `./cub3D maps/`.

### A2 — `parse_elements.c` + `parse_color.c` (module 3) — highest risk
Dispatch on the 1–2 char identifier. Rules straight from the subject: any order, one or more blank
lines between elements, one or more spaces between an element's fields, each element exactly once
(**duplicates are an error**).

Colors: `F 220,100,0` → pack to `0x00RRGGBB`. Must reject `256`, `-1`, `1,2`, `1,2,3,4`, `1,,2`,
`abc`, and empty components. `F 220, 100, 0` (spaces after commas) is genuinely ambiguous in the
subject — **pick a behaviour, write it in the README, and be ready to defend it.**

Texture paths: store the path here; opening and loading is Person B's job. But verify the file is
*openable* during parsing so errors surface before the window opens.

### A3 — `map_extract.c` (module 4)
Collect map lines after the last element. Rows are ragged — pad every row with spaces to
`map.width` so the renderer can index `grid[y][x]` without bounds gymnastics. Preserve interior
spaces exactly; they are meaningful.

Decision to make and document: the subject says non-map elements may be separated by blank lines,
which implies a blank line inside the map is invalid. Treat a blank line after the map starts as
end-of-map and any content after it as an error.

### A4 — `map_validate.c` (module 5)
- Only `0 1 N S E W ' '` present.
- Exactly one player start; record `start_x = col + 0.5`, `start_y = row + 0.5` (centring the player
  in the cell — off-by-half here causes the player to spawn inside a wall).
- **Closure check:** for every walkable cell (`0` or the player char), all four neighbours must be
  in-bounds and not a space. This is equivalent to closure on this grid model, needs no recursion,
  and fits the Norm easily. Know the recursive flood-fill alternative well enough to discuss it at
  defense — evaluators often ask.

### A5 — `error.c` + `cleanup.c` (module 6)
Design rule that makes leak-freedom nearly automatic: **zero the `t_scene` at the very start**, make
`free_scene()` idempotent and safe on partial state, and have every single failure path call it.
No ad-hoc cleanup per error site.

`error_msg()` writes `Error\n` followed by an explicit message and returns 1.

### A6 — `maps/` test suite (module 13)
Around 20 deliberately broken files, one failure mode each: missing element, duplicate element,
bad RGB range, malformed RGB, unknown identifier, nonexistent texture path, no player, two players,
invalid map char, open map (side / top / interior), empty file, only-comments file, map before
elements, wrong extension, directory-as-argument, unreadable file. Plus `tools/run_tests.sh` that
runs each and asserts output starts with `Error` and exit code is non-zero.

---

## Part 5 — Person B: the renderer track

Files under `srcs/render/` and `srcs/engine/`. Owns modules 7, 8, 9, 10, 11, 12.

### B1 — `mlx_setup.c` + `hooks.c` (module 7)
`mlx_init` → `mlx_new_window` → `mlx_new_image(WIN_W, WIN_H)` → `mlx_get_data_addr`. Draw into the
image buffer and blit once per frame — never `mlx_pixel_put` per pixel.

Register **three** hooks:
- `mlx_hook(win, KeyPress(2),      KeyPressMask(1),          on_key_down, game)`
- `mlx_hook(win, KeyRelease(3),    KeyReleaseMask(2),        on_key_up,   game)`
- `mlx_hook(win, DestroyNotify(17),StructureNotifyMask(1<<17), on_close,  game)`

The press/release pair sets flags in `game->keys[]`; `mlx_loop_hook` reads the flags and moves. This
is what makes movement smooth and diagonal movement possible — `mlx_key_hook` alone stutters on
autorepeat and the subject explicitly requires smooth window management.

### B2 — `player_move.c` + `player_rotate.c` (module 8)
Initial camera from `start_dir`, with FOV 66° ⇒ `|plane| = 0.66` when `|dir| = 1`, y increasing
downward:

| dir | `dir_x, dir_y` | `plane_x, plane_y` |
|---|---|---|
| N | `0, -1` | `0.66, 0` |
| S | `0, 1` | `-0.66, 0` |
| E | `1, 0` | `0, 0.66` |
| W | `-1, 0` | `0, -0.66` |

Rotation is a 2×2 rotation matrix applied to **both** `dir` and `plane`. Movement is
`pos += dir * speed` (W/S) and `pos += plane_normalised * speed` (A/D). Scale both by frame time
from `gettimeofday` so speed is framerate-independent.

**Wall collisions are listed as a bonus** — but walking off the map reads out of bounds and
segfaults, which is an automatic 0. Add a minimal guard that refuses to step into a `1` or
out-of-bounds cell, and at defense present it as a **safety guard, not the bonus feature**.

### B3 — `ray_init.c` + `raycast.c` (module 9) — the core
Per column `x` in `0..WIN_W-1`:

```
camera_x   = 2.0 * x / WIN_W - 1.0
dir        = dir + plane * camera_x
map        = (int)pos
delta      = fabs(1.0 / ray_dir)              /* guard ray_dir == 0 with a huge value */
step/side_dist  from the sign of ray_dir
DDA: advance whichever of side_x / side_y is smaller, set side, until grid == '1'
perp_dist  = (side == 0) ? side_x - delta_x : side_y - delta_y
```

`perp_dist` — the **perpendicular** distance, not the euclidean one — is what removes fisheye
distortion. Expect to be asked exactly this at defense.

### B4 — `draw_column.c` + `render.c` (module 10)
```
line_h     = (int)(WIN_H / perp_dist)
draw_start = -line_h / 2 + WIN_H / 2      clamped to >= 0
draw_end   =  line_h / 2 + WIN_H / 2      clamped to <= WIN_H - 1
```
Fill ceiling color above `draw_start`, floor color below `draw_end`.

### B5 — `texture_load.c` + `texture_map.c` (module 11)
Load all four XPMs into `t_img tex[4]` at startup via `mlx_xpm_file_to_image` + `mlx_get_data_addr`.
**Check for NULL** — a bad path must be a clean error, not a crash.

Face selection (y-down convention, must match A4's grid orientation):

| Hit | Ray direction | Wall face seen | Texture |
|---|---|---|---|
| `side == 0` | `ray_dir_x > 0` | West face | `TEX_WE` |
| `side == 0` | `ray_dir_x < 0` | East face | `TEX_EA` |
| `side == 1` | `ray_dir_y > 0` | North face | `TEX_NO` |
| `side == 1` | `ray_dir_y < 0` | South face | `TEX_SO` |

Then the column sampling:
```
wall_x = (side == 0) ? pos_y + perp_dist * ray_dir_y : pos_x + perp_dist * ray_dir_x
wall_x -= floor(wall_x)
tex_x  = (int)(wall_x * tex_w)
flip tex_x when (side == 0 && ray_dir_x > 0) or (side == 1 && ray_dir_y < 0)
step   = tex_h / (double)line_h
tex_pos = (draw_start - WIN_H / 2 + line_h / 2) * step
per pixel: tex_y = (int)tex_pos & (tex_h - 1); tex_pos += step
```

Give the four textures obviously different colors during development so a mis-mapped face is
visible instantly rather than subtly wrong.

### B6 — `cleanup.c` renderer half (module 12)
On exit: destroy the four texture images, the frame image, the window, then `mlx_destroy_display`,
then `free(mlx)`. Missing `mlx_destroy_display` + `free(mlx)` is the single most common source of
"but valgrind is clean on my machine" arguments at cub3D defenses.

---

## Part 6 — Git workflow

`Cube3d/` **is now a git repository** — branch `master`, one commit (`eef2e0e init`). Two earlier
Ultraplan handoffs failed on this (first "requires a git repository", then "no commits"); both
blockers are now cleared. `cube3d.pdf` is still untracked and no 42 remote is configured.

### Step 0 — first action on approval

```bash
cd /home/ggrzesiek/Projects/Cube3d
# write .gitignore (*.o, cub3D, libft/*.a, mlx_linux/*.o, valgrind out)
git add .gitignore cube3d.pdf && git commit -m "Add subject and gitignore"
git remote add origin <42-assigned-repo-url>
```

Add the 42 remote once you have the assigned repository URL — the subject grades only what is in
that repository. Everything in Part 7 follows from there.

```
main                      always compiles, always passes norminette
├── feat/parser-*         Person A
└── feat/render-*         Person B
```

One branch per module, PR to `main`. **The PR review is the cross-teaching gate**: the reviewer does
not approve until they can explain the code back to the author. Concretely — A must be able to
explain fisheye correction before approving B's raycast PR; B must be able to explain the closure
check before approving A's validation PR. This is the entire mitigation for the split you chose.

`.gitignore`: `*.o`, `cub3D`, `libft/*.a`, `mlx_linux/*.o`. Commit `mlx_linux/` sources — the subject
requires MiniLibX to be included when built from sources.

---

## Part 7 — Session sequence

Each module runs: **I explain the theory and structure → you write it → I review against the Norm
and the subject.**

| # | Session | Who | Gate to pass |
|---|---|---|---|
| 0 | Repo, libft+gnl merge, `cub3d.h`, Makefile, XPM spike | Both | `make` produces a binary; four XPMs load non-NULL |
| 1 | File intake + element parsing | A | All texture/color elements parse; duplicates rejected |
| 2 | MLX window, image buffer, hooks, clean exit | B | Window opens, ESC and red X both exit, valgrind clean |
| 3 | Map extraction + validation | A | Every `maps/invalid/*.cub` prints `Error\n` + a message |
| 4 | Player state, movement, rotation | B | Camera moves smoothly on a stub scene, no OOB reads |
| 5 | DDA raycasting + untextured columns | B | Recognisable 3D maze, no fisheye |
| 6 | Error paths + full free audit | A | Valgrind clean on every invalid map |
| 7 | Textures + per-face selection | B | Four faces visibly distinct and correctly oriented |
| 8 | **Integration**: swap the stub for the real parser | Both | Real `.cub` files render |
| 9 | Norm pass, leak pass, README | Both | `norminette` silent, valgrind clean |
| 10 | **Cross-teach**: A presents the renderer, B presents the parser | Both | Each can defend the other's half unaided |

---

## Part 8 — Verification

**Build and norm**
```bash
make re                          # then run again — must print "nothing to be done", no relink
norminette srcs includes libft   # must be silent
```

**Functional**
```bash
./cub3D maps/valid/basic.cub     # walk with WASD, rotate with arrows, ESC to quit
./cub3D                          # Error + usage
./cub3D maps/valid/basic.cub extra
./cub3D maps/                    # directory-as-argument must not crash
./cub3D maps/valid/basic.txt     # wrong extension
bash tools/run_tests.sh          # every maps/invalid/*.cub → "Error\n" + message, exit != 0
```

**Leaks**
```bash
valgrind --leak-check=full --show-leak-kinds=definite,indirect ./cub3D maps/valid/basic.cub
```
X11 leaves "still reachable" blocks that are not yours; `definite` and `indirect` must be zero.
Also run valgrind over every invalid map — error paths leak far more often than the happy path.

**Manual window checks** (explicitly required by the subject): minimise and restore, switch to
another window and back, resize — the render must stay smooth and must not crash.

**Defense rehearsal.** Take turns asking each other:
- Why `perp_dist` and not euclidean distance?
- Why does `plane` have length 0.66?
- How does the closure check prove the map is closed? What would flood fill do differently?
- Where exactly is memory freed if the third texture path is invalid?
- Why press/release flags instead of `mlx_key_hook`?

---

## Open items to settle at kickoff

- **Teammate's 42 login** — needed for the README first line and the 42 header banner in every file.
- **Who takes track A vs track B.** Parsing is more tedious and carries more of the grade; rendering
  is more fun and more mathematical. Split by which half each of you most wants to *learn*, since
  the PR gate forces you to learn both anyway.
