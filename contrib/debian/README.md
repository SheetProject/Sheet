
Debian
====================
This directory contains files used to package sheetd/sheet-qt
for Debian-based Linux systems. If you compile sheetd/sheet-qt yourself, there are some useful files here.

## sheet: URI support ##


sheet-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install sheet-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sheet-qt binary to `/usr/bin`
and the `../../share/pixmaps/sheet128.png` to `/usr/share/pixmaps`

sheet-qt.protocol (KDE)

