## Usage
A cross-compiler is needed to build to the i686 architecture. Follow the instructions at OSDevWiki to [build a cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler) or try getting the script in `cross/` to work -- YMMV.

Build:
```bash
./build.sh
```
Test on qemu:
```bash
./qemu.sh
```

Expected behavior is a screen displaying a reversed array and then a sorted array
