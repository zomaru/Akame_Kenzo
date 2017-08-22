#!/bin/sh
# Auto clone & auto compiling kernel script
# Ini untuk Xiaomi Redmi Note 3 Pro, tinggal disesuaikan sendiri untuk device lain
# Author : Renaldy P <zomaru@github.com>
# Indonesia #72
#
# This software is licensed under the terms of the GNU General Public
# License version 2, as published by the Free Software Foundation, and
# may be copied, distributed, and modified under those terms.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# Please maintain this if you use this script or any part of it
#

# sesuaikan dengan link repo yang mau di-clone
git clone https://github.com/zomaru/Akame_Kenzo

# ganti Akame_Kenzo dengan nama direktori dari source code kernel yang sudah selesai di-clone
cd Akame_Kenzo

# sesuaikan dengan device
export ARCH=arm64

# sesuaikan dengan path compiler kalian
export CROSS_COMPILE=/path/menuju/compiler

# contoh
# export CROSS_COMPILE=/home/toolchain/bin/aarch64-linux-android-
# perhatikan penulisan prefix untuk toolchain, akhiri dengan - seperti contoh diatas

# sesuaikan dengan defconfig device kalian
make kenzo_defconfig
make savedefconfig
make
make dtbs
make modules

# gunakan make clean jika kalian ingin compile ulang, jika tidak hapus saja.
make clean
