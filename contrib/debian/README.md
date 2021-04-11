
Debian
====================
This directory contains files used to package bioa3d/bioa3-qt
for Debian-based Linux systems. If you compile bioa3d/bioa3-qt yourself, there are some useful files here.

## bioa3: URI support ##


bioa3-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bioa3-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bioa3-qt binary to `/usr/bin`
and the `../../share/pixmaps/bioa3128.png` to `/usr/share/pixmaps`

bioa3-qt.protocol (KDE)

