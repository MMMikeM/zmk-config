# Sofle Choc — ZMK config (SuperMini nRF52840 + dongle)

Port of the QMK `sofle_choc:default` keymap to ZMK, built as a three-piece
wireless set: both halves are BLE peripherals, a third controller acts as a USB
dongle / split central.

## Hardware

| Piece  | Board target    | Notes |
|--------|-----------------|-------|
| Left   | `nice_nano//zmk` | SuperMini nRF52840, encoder on F5/F4 |
| Right  | `nice_nano//zmk` | SuperMini nRF52840, encoder on F5/F4 |
| Dongle | `nice_nano//zmk` | SuperMini nRF52840, no matrix, USB powered |

The SuperMini nRF52840 is pin-compatible with the nice!nano v2, so the nice!nano
board target is the right one. Since ZMK moved to Zephyr 4.1 that target is
spelled `nice_nano//zmk` (revision + ZMK variant); the old `nice_nano_v2` name
no longer resolves. Two differences to be aware of:

* No external QSPI flash chip — harmless, ZMK stores settings in internal flash.
* Battery divider/LED wiring is not identical, so battery percentage may read
  slightly off and the status LED may not behave like a nice!nano.

Bootloader: double-tap RST (short RST to GND twice within ~0.5s), then drop the
`.uf2` on the mass-storage device.

## Building

Push to GitHub and the Actions workflow builds all four firmwares, or locally:

```
west build -s zmk/app -b nice_nano//zmk -- -DSHIELD=sofle_choc_left -DZMK_CONFIG=$PWD/config
```

## Flashing order

1. Flash `settings_reset` to **all three** boards first, to clear stale bonds.
2. Flash `sofle_choc_dongle`, `sofle_choc_left`, `sofle_choc_right`.
3. Plug the dongle in; the halves pair to it automatically.

## Layers

`0 colemak-dh`, `1 qwerty`, `2 symbols`, `3 brackets`, `4 arrows` — same content
as the QMK keymap.

* `ESC` thumb → hold for symbols, `TAB` thumb → hold for brackets.
* `O` (colemak) / `;` (qwerty) and `Z` (colemak) → hold for arrows.
* Top-right key toggles colemak ⇄ qwerty (`&to`).
* Both shifts together → caps word (combo, positions 36 + 49).
* Left encoder: volume. Right encoder: mouse scroll.

## QMK → ZMK mapping notes

| QMK | ZMK |
|-----|-----|
| `TAPPING_TERM 300` | `tapping-term-ms = <300>` on the custom `&lt` |
| `FLOW_TAP_TERM 150` | `require-prior-idle-ms = <150>` |
| `DEBOUNCE 8` | `debounce-press-ms`/`debounce-release-ms = <8>` on kscan |
| `BOTH_SHIFTS_TURNS_ON_CAPS_WORD` | combo → `&caps_word` |
| `LT(layer, kc)` | `&lt layer kc` (hold-tap, `tap-preferred` flavor) |
| `TO(layer)` | `&to layer` |
| `KC_MPLY` | `&kp C_PP` |
| `KC_MS_WH_UP/DOWN` | `&enc_scroll SCRL_DOWN SCRL_UP` (needs `CONFIG_ZMK_POINTING=y`) |

Added because wireless needs them (no QMK counterpart): `&bt` / `&out` on the
symbols top row, `&bootloader` / `&sys_reset` on the arrows top row.

**Dropped:** the QMK `process_detected_host_os_user` hook that swapped
Ctrl/GUI on Windows. ZMK has no OS detection; if you need it, the usual
workaround is a dedicated "Windows" layer with the two mods swapped, toggled
manually.

## Layout differences vs. the stock ZMK `sofle` shield

Sofle Choc has 4 thumb keys per half (58 keys); Sofle v2 has 5 (60 keys), and the
right-half column order differs. Hence the custom `sofle_choc` shield in
`config/boards/shields/` rather than reusing the in-tree `sofle` shield.

The original QMK source is kept under `extracted/sofle_choc/` for reference.
