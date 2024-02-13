#!/usr/bin/env bash

yes | doas pacman -R l61
makepkg -f
yes | doas pacman -U ./l61-*-1-x86_64.pkg.tar.zst
