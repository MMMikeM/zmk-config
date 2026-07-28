/* Copyright 2023 Mike Murray
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

// Enabling this option changes the startup behavior to listen for an
// active USB communication to delegate which part is master and which
// is slave. With this option enabled and theres's USB communication,
// then that half assumes it is the master, otherwise it assumes it
// is the slave.
//
// I've found this helps with some ProMicros where the slave does not boot
#define SPLIT_USB_DETECT

// Remove RGB matrix settings as we're not using LEDs
// #define RGB_MATRIX_SLEEP
// #define SPLIT_TRANSPORT_MIRROR
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100

// Tap dance configuration
// #define PERMISSIVE_HOLD        // Makes tap-hold keys work better for fast typists

// Additional optimization settings
// Removing deprecated options
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION


