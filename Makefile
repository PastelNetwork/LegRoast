export OpenSSLPath=./OpenSSL-amd64

CC=gcc
CFLAGS=-I XKCP/bin/generic64/ -I "${OpenSSLPath}/include/"
LFLAGS=-s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -static -L XKCP/bin/generic64/ -lkeccak -L "${OpenSSLPath}/lib/" -lcrypto -lws2_32 -lcrypt32

IMPLEMENTATION_SOURCE = test.c
IMPLEMENTATION_HEADERS= sign.h keccaklib zkproof.h parameters.h merkletree.h


test: $(IMPLEMENTATION_SOURCE) $(IMPLEMENTATION_HEADERS) static
	$(CC) -o test $(IMPLEMENTATION_SOURCE) $(CFLAGS) -L ./ -llegroast $(LFLAGS)  -std=c11 -O3 -g -march=native 

static: create-mri
	$(CC) -c sign.c zkproof.c merkletree.c $(CFLAGS) $(LFLAGS) -std=c11 -O3 -g -march=native
	ar -rcs liblegroastobj.a sign.o zkproof.o merkletree.o
	ar -M <liblegroast.mri

create-mri:
	rm -f liblegroast.mri
	@echo "  create liblegroast.a\n  addlib liblegroastobj.a\n  addlib XKCP/bin/generic64/libkeccak.a\n  addlib $(OpenSSLPath)/lib/libcrypto.a\n  addlib /usr/x86_64-w64-mingw32/lib/libws2_32.a\n  addlib /usr/x86_64-w64-mingw32/lib/libcrypt32.a\n  save\n  end" > liblegroast.mri

keccaklib: 
	(cd XKCP; make generic64/libkeccak.a)

.PHONY: clean
clean:
	rm -f PQCgenKAT_sign test debug test_offline intermediateValues.txt *.req *.rsp >/dev/null
