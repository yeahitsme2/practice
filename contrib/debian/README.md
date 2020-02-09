
Debian
====================
This directory contains files used to package growthd/growth-qt
for Debian-based Linux systems. If you compile growthd/growth-qt yourself, there are some useful files here.

## growth: URI support ##


growth-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install growth-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your growth-qt binary to `/usr/bin`
and the `../../share/pixmaps/growth128.png` to `/usr/share/pixmaps`

growth-qt.protocol (KDE)

