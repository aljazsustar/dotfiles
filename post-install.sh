#!/bin/bash

sudo pacman -Syu

sudo pacman -S git vim code base-devel nautilus nitrogen awesome xorg networkmanager npm python jdk-openjdk gcc ghc emacs xorg-init
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si

yay -S zoom teams discord  qutebrowser polybar dbeaver intellij-idea-ultimate-edition webstorm datagrip pycharm clion mailspring kmix network-manager-applet flameshot mariadb alacritty

sudo systemctl enable mariadb
sudo systemctl enable NetworkManager


