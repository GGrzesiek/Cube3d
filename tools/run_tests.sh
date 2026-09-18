#!/bin/bash
# cub3D test runner.
#
#   ./tools/run_tests.sh              invalid maps only (no X display needed)
#   ./tools/run_tests.sh --display    also open each valid map in a window
#   ./tools/run_tests.sh --valgrind   also assert zero leaks on every error path
#   ./tools/run_tests.sh --all        everything
#
# Always rebuilds with `make re`: the root Makefile's $(LIBFT) rule has no
# prerequisites, so a plain `make` will not pick up edits to libft/.

set -u

cd "$(dirname "$0")/.." || exit 1

BIN=./cub3D
PASS=0
FAIL=0
FAILED=()

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
YELLOW=$'\033[0;33m'
NC=$'\033[0m'

DO_DISPLAY=0
DO_VALGRIND=0
for arg in "$@"; do
	case "$arg" in
		--display) DO_DISPLAY=1 ;;
		--valgrind) DO_VALGRIND=1 ;;
		--all) DO_DISPLAY=1; DO_VALGRIND=1 ;;
		*) echo "unknown option: $arg" >&2; exit 2 ;;
	esac
done

ok()   { PASS=$((PASS + 1)); printf '  %sok%s   %s\n' "$GREEN" "$NC" "$1"; }
bad()  { FAIL=$((FAIL + 1)); FAILED+=("$1"); printf '  %sFAIL%s %s\n	   %s\n' "$RED" "$NC" "$1" "$2"; }
skip() { printf '  %sskip%s %s (%s)\n' "$YELLOW" "$NC" "$1" "$2"; }

echo "== building =="
if ! make re >/dev/null 2>&1; then
	echo "${RED}build failed${NC}" >&2
	make re 2>&1 | tail -20 >&2
	exit 1
fi

# ---------------------------------------------------------------------------
# 1. invalid scenes: must print "Error" on stderr line 1, the expected reason
#    on line 2, and exit non-zero. Pinning the reason is what catches a map
#    rejected for the wrong cause.
# ---------------------------------------------------------------------------
echo "== invalid scenes =="

check_invalid() {
	local file="$1" want="$2" out rc line1 line2

	out=$(timeout 5 "$BIN" "$file" 2>&1 >/dev/null)
	rc=$?
	line1=$(printf '%s\n' "$out" | sed -n 1p)
	line2=$(printf '%s\n' "$out" | sed -n 2p)
	if [ "$rc" -eq 0 ]; then
		bad "$file" "exited 0, expected non-zero"
	elif [ "$line1" != "Error" ]; then
		bad "$file" "stderr line 1 was '$line1', expected exactly 'Error'"
	elif [ "${line2#*"$want"}" = "$line2" ]; then
		bad "$file" "reason was '$line2', expected to contain '$want'"
	else
		ok "$file"
	fi
}

while IFS='|' read -r file want; do
	[ -z "$file" ] && continue
	check_invalid "maps/invalid/$file" "$want"
done <<'CASES'
missing_no.cub|Unexpected line before all elements set
duplicate_no.cub|Duplicate texture identifier
duplicate_f.cub|Duplicate color identifier
unknown_id.cub|Invalid map character
missing_texture_file.cub|Cannot open texture file
color_range.cub|Color value out of range
color_negative.cub|Color value is not a number
color_few.cub|Wrong amount of color values
color_many.cub|Wrong amount of color values
color_trailing.cub|Wrong amount of color values
color_empty.cub|Wrong amount of color values
color_text.cub|Color value is not a number
invalid_char.cub|Invalid map character
no_player.cub|Invalid amount of direction characters
two_players.cub|Invalid amount of direction characters
open_side.cub|not enclosed
open_top.cub|not enclosed
open_interior.cub|not enclosed
open_bottom_wide.cub|not enclosed
blank_in_map.cub|Empty line inside map
map_first.cub|Unexpected line before all elements set
too_small.cub|Map is too small
empty.cub|Lack of some scene information
wrong_ext.map|File must have .cub extension
adir.cub|Lack of some scene information
CASES

# argv handling
out=$(timeout 5 "$BIN" 2>&1 >/dev/null); rc=$?
if [ "$rc" -ne 0 ] && [ "$(printf '%s\n' "$out" | sed -n 1p)" = "Error" ]; then
	ok "no argument"
else
	bad "no argument" "rc=$rc out='$out'"
fi
out=$(timeout 5 "$BIN" maps/valid/basic.cub extra 2>&1 >/dev/null); rc=$?
if [ "$rc" -ne 0 ] && [ "$(printf '%s\n' "$out" | sed -n 1p)" = "Error" ]; then
	ok "two arguments"
else
	bad "two arguments" "rc=$rc out='$out'"
fi

# chmod 000 cannot be committed (git stores only the execute bit), and it is
# not a meaningful test as root, so generate it here instead.
if [ "$(id -u)" -ne 0 ]; then
	tmp=$(mktemp /tmp/cub3d_unreadable_XXXXXX.cub)
	cp maps/valid/basic.cub "$tmp" && chmod 000 "$tmp"
	check_invalid "$tmp" "Cannot open a file"
	rm -f "$tmp"
else
	skip "unreadable.cub" "running as root"
fi

# ---------------------------------------------------------------------------
# 2. valid scenes: need an X display. Exit 124 means the window opened and
#    mlx_loop was still running when timeout fired, which is the success case.
# ---------------------------------------------------------------------------
if [ "$DO_DISPLAY" -eq 1 ]; then
	echo "== valid scenes =="
	if [ -z "${DISPLAY:-}" ]; then
		skip "all valid maps" "DISPLAY is unset"
	else
		for file in maps/valid/basic.cub maps/valid/ragged.cub maps/map.cub; do
			err=$(timeout 3 "$BIN" "$file" 2>&1 >/dev/null)
			rc=$?
			if [ "$rc" -ne 124 ]; then
				bad "$file" "exited $rc, expected 124 (window still open)"
			elif [ -n "$err" ]; then
				bad "$file" "wrote to stderr: $err"
			else
				ok "$file"
			fi
		done
	fi
fi

# ---------------------------------------------------------------------------
# 3. leaks: only the invalid scenes, which return before MLX is ever touched.
#    That keeps the numbers deterministic and free of X11's own allocations.
# ---------------------------------------------------------------------------
if [ "$DO_VALGRIND" -eq 1 ]; then
	echo "== leaks (error paths) =="
	if ! command -v valgrind >/dev/null 2>&1; then
		skip "leak checks" "valgrind not installed"
	else
		for file in maps/invalid/*.cub; do
			[ -d "$file" ] && continue
			out=$(timeout 30 valgrind --leak-check=full --show-leak-kinds=all \
				--errors-for-leak-kinds=all --error-exitcode=42 \
				"$BIN" "$file" 2>&1 >/dev/null)
			rc=$?
			if [ "$rc" -eq 42 ]; then
				bad "$file" "$(printf '%s\n' "$out" | grep -E 'lost:|ERROR SUMMARY' | head -4)"
			else
				ok "$file (no leaks)"
			fi
		done
	fi
fi

echo
TOTAL=$((PASS + FAIL))
if [ "$FAIL" -eq 0 ]; then
	printf '%sPASS %d/%d%s\n' "$GREEN" "$PASS" "$TOTAL" "$NC"
	exit 0
fi
printf '%sFAIL %d/%d%s\n' "$RED" "$FAIL" "$TOTAL" "$NC"
for f in "${FAILED[@]}"; do
	printf '  %s\n' "$f"
done
exit 1
