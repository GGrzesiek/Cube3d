#!/usr/bin/env python3
"""Writes the four wall textures as 64x64 XPM3 files.

mlx has its own xpm parser and returns NULL without a message on
anything it does not accept, so these are built by hand instead of
exported. Patterns are asymmetric left to right so a mirrored column
is obvious.

    python3 tools/gen_textures.py
"""

SIZE = 64
KEYS = "abcdefghijklmnopqrstuvwxyz0123456789"


def shade(rgb, factor):
    return tuple(max(0, min(255, int(c * factor))) for c in rgb)


def bricks(base, mortar, course=16, length=32):
    px = [[base] * SIZE for _ in range(SIZE)]
    for y in range(SIZE):
        row = y // course
        xoff = (length // 2) if row % 2 else 0
        for x in range(SIZE):
            sx = (x + xoff) % length
            if y % course < 2 or sx < 2:
                px[y][x] = mortar
            elif y % course == 2:
                px[y][x] = shade(base, 1.25)
            else:
                jitter = ((x + xoff) // length * 7 + row * 13) % 3
                px[y][x] = shade(base, 1.0 + 0.06 * (jitter - 1))
    return px


def planks(base, gap, width=16):
    px = [[base] * SIZE for _ in range(SIZE)]
    for y in range(SIZE):
        for x in range(SIZE):
            if x % width < 2:
                px[y][x] = gap
            else:
                grain = ((x * 5 + y * 3) // 7) % 4
                px[y][x] = shade(base, 1.0 + 0.05 * (grain - 1.5))
    for y in range(20, 28):
        for x in range(21, 29):
            if (x - 25) ** 2 + (y - 24) ** 2 <= 12:
                px[y][x] = shade(base, 0.55)
    return px


def panels(base, edge):
    px = [[base] * SIZE for _ in range(SIZE)]
    for y in range(SIZE):
        for x in range(SIZE):
            d = min(x, y, SIZE - 1 - x, SIZE - 1 - y)
            if d < 3:
                px[y][x] = edge
            elif d < 6:
                if x < SIZE // 2:
                    px[y][x] = shade(base, 1.3)
                else:
                    px[y][x] = shade(base, 0.7)
            else:
                px[y][x] = shade(base, 1.0 + 0.04 * (((x + y) // 8) % 3 - 1))
    return px


def to_xpm(px, name):
    palette = []
    for row in px:
        for c in row:
            if c not in palette:
                palette.append(c)
    if len(palette) > len(KEYS):
        raise SystemExit("%s: %d colours, palette is too big" % (name, len(palette)))
    key = {c: KEYS[i] for i, c in enumerate(palette)}
    out = ["/* XPM */", "static char *%s[] = {" % name,
           '"%d %d %d 1",' % (SIZE, SIZE, len(palette))]
    for c in palette:
        out.append('"%s c #%02X%02X%02X",' % (key[c], c[0], c[1], c[2]))
    for i, row in enumerate(px):
        line = "".join(key[c] for c in row)
        out.append('"%s"%s' % (line, "," if i < SIZE - 1 else ""))
    out.append("};")
    return "\n".join(out) + "\n"


TEXTURES = {
    "north_texture": ("north", bricks((58, 92, 150), (30, 44, 70))),
    "south_texture": ("south", bricks((150, 62, 52), (72, 30, 26))),
    "west_texture": ("west", planks((92, 132, 74), (44, 62, 36))),
    "east_texture": ("east", panels((176, 132, 54), (86, 62, 24))),
}

if __name__ == "__main__":
    for fname, (name, px) in TEXTURES.items():
        path = "textures/%s.xpm" % fname
        with open(path, "w") as fp:
            fp.write(to_xpm(px, name))
        print("wrote %s" % path)
