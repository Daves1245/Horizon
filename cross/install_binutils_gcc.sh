#!/bin/bash

# Configuration
BINUTILS_SITE="https://ftp.gnu.org/gnu/binutils/"
GCC_SITE="https://ftp.gnu.org/gnu/gcc/"
export TARGET=i686-elf
NUM_CORES=14
INSTALL_DIRECTORY="$(pwd)"

# Function to download, parse, and extract a tar.gz file for binutils
download_and_extract_binutils() {
    local site=$1
    local output_file=$2

    curl -s $site --output index.html
    sed -e '
       /\n/{P;d;}
       s/binutils-[^\"|^\<]*/\n&\n/;D
    ' < index.html | awk '/\.tar\.gz$/ {sub(/\.tar\.gz$/, ""); print}' > $output_file

    readarray -t options < $output_file

    # Generate menu
    source bmenu -t "Available binutils versions" -s "[select one]" -o "$(cat $output_file)" -a #Delete the # before "-a" to display the alternative menu.

    option=${options[$selected - 1]}

    echo "Selected: ${option}"

    url="$site$option.tar.gz"
    echo "selected $url"

    wget --output-document binutils.tar.gz $url

    # Extract the tar.gz file
    tar xvf binutils.tar.gz
}

# Function to download, parse, and extract a tar.gz file for gcc
download_and_extract_gcc() {
    local site=$1
    local output_file=$2

    curl -s $site --output index.html
    sed -e '
       /\n/{P;d;}
       s/gcc-[^\"|^\<]*/\n&\n/;D
    ' < index.html | tee all_gcc_options.txt > $output_file

    readarray -t options < $output_file

    # Generate menu
    source bmenu -t "Available gcc versions" -s "[select one]" -o "$(cat $output_file)" -a #Delete the # before "-a" to display the alternative menu.

    option=${options[$selected - 1]}

    option="${option:0:${#option} - 1}"
    echo "Selected: ${option}"

    url="$site$option/$option.tar.gz"
    echo "selected $url"

    wget --output-document gcc.tar.gz $url

    # Extract the tar.gz file
    tar xvf gcc.tar.gz
}

# Function to install binutils
install_binutils() {
    download_and_extract_binutils $BINUTILS_SITE binutils_options.txt

    mkdir -p build-binutils
    cd build-binutils

    ../binutils-*/configure --target=$TARGET --prefix="$INSTALL_DIRECTORY" --with-sysroot --disable-nls --disable-werror
    make
    make install
    cd ..
}

# Function to install gcc
install_gcc() {
    download_and_extract_gcc $GCC_SITE gcc_options.txt

    which -- $TARGET-as || echo $TARGET-as is not in the PATH

    mkdir -p build-gcc
    cd build-gcc

    ../gcc-*/configure --target=$TARGET --prefix="$INSTALL_DIRECTORY" --disable-nls --enable-languages=c,c++ --without-headers

    make -j $NUM_CORES all-gcc
    make -j $NUM_CORES all-target-libgcc
    make install-gcc
    make install-target-libgcc
    cd ..
}

# Main script execution
install_binutils
read -n 1 -s -r -p "Installed binutils. Press any key to continue"
install_gcc
echo "Installed gcc"
echo "Done. Cross compiler can be found at $INSTALL_DIRECTORY/bin/$TARGET-gcc"
