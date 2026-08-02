"""Render an ASCII sofle_choc layout from the bindings in the keymap."""
import re, sys
from pathlib import Path

KM = Path("config/sofle_choc.keymap")

KC = {
    "TAB": "Tab", "LGUI": "GUI", "LCTRL": "Ctrl", "LALT": "Alt", "SPACE": "Space",
    "RET": "Ent", "BSPC": "Bspc", "DEL": "Del", "ESC": "Esc", "BSLH": "\\",
    "SQT": "'", "SEMI": ";", "COMMA": ",", "DOT": ".", "FSLH": "/",
    "C_MUTE": "Mute", "C_PP": "Play", "LSHFT": "Shift", "RSHFT": "Shift",
    "EXCL": "!", "AT": "@", "HASH": "#", "DLLR": "$", "PRCNT": "%", "CARET": "^",
    "AMPS": "&", "ASTRK": "*", "LPAR": "(", "RPAR": ")", "LBKT": "[", "RBKT": "]",
    "LBRC": "{", "RBRC": "}", "MINUS": "-", "UNDER": "_", "PLUS": "+",
    "EQUAL": "=", "GRAVE": "`", "PG_UP": "PgUp", "PG_DN": "PgDn", "HOME": "Home",
    "END": "End", "UP": "Up", "DOWN": "Down", "LEFT": "Left", "RIGHT": "Rght",
    "PSCRN": "PrSc",
}
KC.update({f"N{i}": str(i) for i in range(10)})


def label(b):
    t = b.split()
    if t[0] == "&none":
        return ""
    if t[0] == "&trans":
        return "~"
    if t[0] in ("&caps_lsft", "&caps_rsft"):
        return "Shift"
    if t[0] == "&kp":
        return KC.get(t[1], t[1])
    if t[0] == "&mo":
        return t[1]
    if t[0] == "&to":
        return ">" + t[1]
    if t[0] == "&lt_arw":
        return f"{label('&kp ' + t[2])}/{t[1]}"
    return t[0].lstrip("&")


def parse():
    src = KM.read_text()
    clean = "\n".join(re.sub(r"//.*$", "", l) for l in src.splitlines())
    out = []
    for m in re.finditer(
        r'display-name = "([^"]*)";\s*bindings = <(.*?)>;', clean, re.S
    ):
        toks, cur = [], None
        for w in m.group(2).split():
            if w.startswith("&"):
                if cur:
                    toks.append(" ".join(cur))
                cur = [w]
            else:
                cur.append(w)
        if cur:
            toks.append(" ".join(cur))
        assert len(toks) == 58, (m.group(1), len(toks))
        out.append((m.group(1), toks))
    return out


W = 5


def cell(s):
    return s.center(W)[:W]


def row(cells):
    return "|" + "|".join(cell(c) for c in cells) + "|"


def sep(n, l, m, r):
    return l + m.join("-" * W for _ in range(n)) + r


def render(name, k):
    L, R = 0, 52          # left/right block start columns
    lines = []

    def two(left, right):
        lines.append(("".ljust(L) + left).ljust(R) + right)

    two(sep(6, ".", ".", "."), sep(6, ".", ".", "."))
    for r0, r1 in ((0, 6), (12, 18), (24, 30)):
        two(row(map(label, k[r0:r0 + 6])), row(map(label, k[r1:r1 + 6])))
        two(sep(6, ":", "+", ":"), sep(6, ":", "+", ":"))
    # bottom row carries the encoder push-buttons on the inner edge, so it is
    # one cell wider than the rows above it and reaches into the gap
    lines.pop()  # replace the plain separator with one that opens the encoder cell
    two(sep(6, ":", "+", ":") + "-" * W + ".", "." + "-" * W + sep(6, ":", "+", ":"))
    lines[-1] = lines[-1][:R - W - 1] + lines[-1][R:]  # pull right half inward
    ed = row(map(label, k[36:42] + [k[42]]))
    er = row(map(label, [k[43]] + k[44:50]))
    lines.append(ed.ljust(R - W - 1) + er)
    lines.append(sep(7, "'", "+", "'").ljust(R - W - 1) + sep(7, "'", "+", "'"))
    # thumbs hang off the inner edge, flush with the encoder cell above them
    ti = L + 3 * (W + 1)      # was L + 2 * (W + 1)
    tr = R - (W + 1)          # was R
    lines.append(("".ljust(ti) + row(map(label, k[50:54]))).ljust(tr)
                 + row(map(label, k[54:58])))
    lines.append(("".ljust(ti) + sep(4, "'", "'", "'")).ljust(tr)
                 + sep(4, "'", "'", "'"))
    return [l.rstrip() for l in lines]


if __name__ == "__main__":
    want = sys.argv[1] if len(sys.argv) > 1 else None
    for name, k in parse():
        if want and want != name:
            continue
        print(f"=== {name} ===")
        for l in render(name, k):
            print("// " + l if l else "//")
        print()
