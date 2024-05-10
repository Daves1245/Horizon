### Dependencies
makeinfo for installing binutils (texinfo package)
GMP 4.2+, MPFR 3.1.0+ and MPC 0.8.0+ for gcc 14.0
(libgmp3-dev, libmpc-dev, libmpfr-dev respectively)

## install_binutils_gcc
Convenience script to install a version of binutils and gcc, and build the cross compiler for a specific target. Can be customized, defaults to i686-elf and extracting a .tar.gz of each tool. Does not check gpg signatures, likely breaks. Has a prerequestite (TheBashMenu) that needs to be included (TODO) or installed separately.
