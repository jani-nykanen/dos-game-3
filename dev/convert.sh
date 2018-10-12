#!/bin/sh
cd "$(dirname "$0")"

../tools/png2bin bitmaps/parrot.png ../ASSETS/BITMAPS/PARROT.BIN -dither
../tools/png2bin bitmaps/font.png ../ASSETS/BITMAPS/FONT.BIN
../tools/png2bin bitmaps/goat.png ../ASSETS/BITMAPS/GOAT.BIN
