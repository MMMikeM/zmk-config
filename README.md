# Sofle Choc — ZMK config (SuperMini nRF52840 + dongle)

Port of the QMK `sofle_choc:default` keymap to ZMK as a three-piece wireless
set: both halves are BLE peripherals, a third controller is the USB dongle /
split central.

## Hardware

All three pieces are SuperMini nRF52840 boards, pin-compatible with the
nice!nano v2 and built as `nice_nano//zmk` — the Zephyr 4.1 spelling of the
target; the old `nice_nano_v2` name no longer resolves. SuperMini caveats vs.
a real nice!nano: no QSPI flash (harmless — settings live in internal flash),
and different battery divider/LED wiring, so battery percentage may read
slightly off.

Bootloader: double-tap RST, then drop the `.uf2` on the mass-storage device.

## Building & flashing

Push to GitHub for the Actions build of all four firmwares, or locally:

```
west build -s zmk/app -b nice_nano//zmk -- -DSHIELD=sofle_choc_left -DZMK_CONFIG=$PWD/config
```

1. Flash `settings_reset` to **all three** boards first to clear stale bonds.
2. Flash `sofle_choc_dongle`, `sofle_choc_left`, `sofle_choc_right`.
3. Plug the dongle in; the halves pair to it automatically.

## Layers

`0 colemak-dh`, `1 qwerty` (gaming — plain keycodes only), `2 symbols`,
`3 brackets`, `4 arrows`. Diagrams live in `config/sofle_choc.keymap`;
`python3 render.py [name]` regenerates them from the bindings.

* Thumb holds: `SYM` (left), `BKT` (right).
* `A`/`O` (colemak home-row pinkies): hold for arrows.
* Both shifts together: caps word (mod-morph, no timing window).
* `F`+`P` within 40ms: `Esc` (colemak only).
* Top-right key switches colemak ⇄ qwerty.
* Arrows layer also carries PgUp/PgDn/Home/End on the left hand and PrtScn
  under `G` (opens Snipping Tool on Windows; remapped host-side on macOS).
* Encoders: volume (left), mouse scroll (right).

## Notes vs. QMK

* `FLOW_TAP_TERM` → `require-prior-idle-ms`, `LT(layer, kc)` → the custom
  `&lt_arw` hold-tap, `BOTH_SHIFTS_TURNS_ON_CAPS_WORD` → mod-morph shifts,
  `DEBOUNCE 8` → `debounce-*-ms` on the kscan.
* Dropped: QMK's host-OS detection (swapped Ctrl/GUI on Windows) — ZMK has no
  equivalent; a manually-toggled layer is the usual workaround if ever needed.
* Sofle Choc has 4 thumb keys per half (58 keys) vs. Sofle v2's 5 (60), and a
  different right-half column order, hence the custom shield in
  `config/boards/shields/` instead of the in-tree `sofle` shield.
