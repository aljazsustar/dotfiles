#!/bin/bash

sudo pacman -Syu

sudo pacman -S git vim code base-devel nautilus nitrogen awesome xorg networkmanager npm python jdk-openjdk gcc ghc emacs xorg-init picom htop vlc neofetch pulseaudio pulseaudio-alsa pulseaudio-bluetooth
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si

yay -S zoom teams discord  qutebrowser polybar dbeaver intellij-idea-ultimate-edition webstorm datagrip pycharm clion mailspring kmix network-manager-applet flameshot mariadb alacritty ncspot

git clone --depth 1 https://github.com/hlissner/doom-emacs ~/.emacs.d
~/.emacs.d/bin/doom install

sudo systemctl enable mariadb
sudo systemctl enable NetworkManager


