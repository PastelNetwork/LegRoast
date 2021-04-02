# LegRoast
Post-Quantum signatures based on the Legendre PRF

Parameters can be found and changed in parameters.h

# Cross-compilation on linux to windows

Install cross-compiler toolchain and cross-compile OpenSSL dependency first:

```
apt-get install build-essential checkinstall zlib1g-dev git mingw-w64 -y
cd ~
git clone --branch OpenSSL_1_1_1-stable https://github.com/openssl/openssl.git
cd openssl
./Configure --static -static --cross-compile-prefix=x86_64-w64-mingw32- mingw64
make -j4
main install
````

Cross-compile LegRoast from its root directory:
```
make CC="x86_64-w64-mingw32-gcc" LDLIBS=-lmingw32 OpenSSLPath=/OPENSSL/INSTALL/PATH test
```

# MacOS build
OpenSSL building configuration params:
```
./Configure --prefix=/FULL-PATH-TO/openssl/installdir --openssldir=/FULL-PATH-TO/openssl/installdir darwin64-x86_64-cc
```

To compile liblegroast.a:
```
make OpenSSLPath=/FULL-PATH-TO/openssl/installdir CC=clang -f Makefile-osx test
```


# Linux build
To build and run natively:

```
make OpenSSLPath=/usr/local -f Makefile-gcc test
./test
````

Enjoy
