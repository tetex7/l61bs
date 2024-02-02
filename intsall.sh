#!/usr/bin/env bash


doas pacman -R l61
makepkg -f
doas pacman -U ./l61-2.0.0-1-x86_64.pkg.tar.zst