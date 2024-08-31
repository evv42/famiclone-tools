# famiclone-tools: a set of tools to help with replacing roms in onebus famiclones

This repository contains some hastily-written single-file programs to help with hacking famiclones devices to include better games in them.  

Some other tools recommanded are the [ReadNES](https://gitlab.com/aaronbottegal/ReadNES3) splitter program, and the [NintendulatorNRS](https://www.unlicensed.games/libg/static.php?page=NintendulatorNRS) emulator.

## Build

```
$ make <program>

or

$ cc -o <program> <program.c>

(there's probably a thousand other ways)
```

## Usage

Running each program with no or invalid arguments will prompt a small message explaining how to use them.  

## Contents  

vt2math.c: a program to compute the offset of a prg and chr rom for a particular game from the VT02+ mapper values  
shoverom.c: a program to replace a rom in the onebus rom with a given offset  

## Disclaimer

This software is provided 'AS-IS', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.  

