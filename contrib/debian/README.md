
Debian
====================
This directory contains files used to package hashsharecoind/hashsharecoin-qt
for Debian-based Linux systems. If you compile hashsharecoind/hashsharecoin-qt yourself, there are some useful files here.

## hashsharecoin: URI support ##


hashsharecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install hashsharecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your hashsharecoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/hashsharecoin128.png` to `/usr/share/pixmaps`

hashsharecoin-qt.protocol (KDE)

