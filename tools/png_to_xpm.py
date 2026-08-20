#!/usr/bin/env python3
"""Converts the wall textures from png to the xpm3 subset mlx accepts.

mlx has its own xpm parser and returns NULL without a message on anything it
does not accept, so the output is written by hand rather than exported:
one character per pixel (cpp 1, the parser's fast path) and colours as
"<key> c #RRGGBB".

    python3 tools/png_to_xpm.py <dir-with-pngs>

Sources are the wolfenstein textures from lodev.org/cgtutor/raycasting.html
(files/wolftex.zip). They are copyright id Software and carry no licence, so
the pngs stay out of this repo - only the converted xpm are kept. See
docs/ZRODLA_LODEV.md.
"""

import os
import sys

from PIL import Image

KEYS = ("abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789")

FACES = {
    "north_texture": "bluestone.png",
    "south_texture": "redbrick.png",
    "west_texture": "greystone.png",
    "east_texture": "wood.png",
}


def to_xpm(im, name):
    px = list(im.getdata())
    w, h = im.size
    palette = []
    for c in px:
        if c not in palette:
            palette.append(c)
    if len(palette) > len(KEYS):
        raise SystemExit("%s: %d colours, too many for one char per pixel"
                         % (name, len(palette)))
    key = {c: KEYS[i] for i, c in enumerate(palette)}
    out = ["/* XPM */", "static char *%s[] = {" % name,
           '"%d %d %d 1",' % (w, h, len(palette))]
    for c in palette:
        out.append('"%s c #%02X%02X%02X",' % (key[c], c[0], c[1], c[2]))
    for y in range(h):
        row = "".join(key[px[y * w + x]] for x in range(w))
        out.append('"%s"%s' % (row, "," if y < h - 1 else ""))
    out.append("};")
    return "\n".join(out) + "\n"


if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise SystemExit("usage: python3 tools/png_to_xpm.py <dir-with-pngs>")
    src = sys.argv[1]
    for fname, png in FACES.items():
        path = os.path.join(src, png)
        if not os.path.exists(path):
            raise SystemExit("missing %s" % path)
        im = Image.open(path).convert("RGB")
        if im.size != (64, 64):
            raise SystemExit("%s is %dx%d, expected 64x64" % (png, im.width, im.height))
        out = "textures/%s.xpm" % fname
        with open(out, "w") as fp:
            fp.write(to_xpm(im, fname))
        print("wrote %s from %s (%d colours)" % (out, png, len(set(im.getdata()))))
