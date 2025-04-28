#!/bin/bash

meson compile -C build/ && gdb ./build/src/eng

