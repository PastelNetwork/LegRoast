# LegRoast
Post-Quantum signatures based on the Legendre PRF

Parameters can be found and changed in parameters.h

# Linux emcc build

Compile openssl with emcc. Configure and build openssl using emconfigure and emmake.
Set path to CC, AR and RNALIB for make to emcc tools.

```
git clone --branch OpenSSL_1_1_1-stable https://github.com/openssl/openssl.git
cd openssl
emconfigure ./config \
  no-asm \
  no-threads \
  no-engine \
  no-hw \
  no-weak-ssl-ciphers \
  no-dtls \
  no-shared \
  no-dso \
  --prefix=$EMSCRIPTEN/system

emmake make CC="{path_to_emscripten}/emcc" AR="{path_to_emscripten}/emar" RANLIB="{path_to_emscripten}/emranlib"
```
Build LegRoast with emmake.

```
emmake make -f Makefile-emcc
```
To compile liblegroast.a to WASM module with exported functions:

```
export TOTAL_MEMORY=16777216
export EXPORTED_FUNCTIONS="[ \
    '_keygen', \
    '_verify', \
    '_sign', \
    '_memcpy'
]"

export LIBRARY_FUNCTIONS="[ \
    'memcpy', \
    'memset', \
    'malloc', \
    'free'
]"

echo "Running Emscripten..."
emcc liblegroast.a \
    -s TOTAL_MEMORY=${TOTAL_MEMORY} \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s ASSERTIONS=0 \
    -s DISABLE_EXCEPTION_CATCHING=1 \
    -s EXPORTED_FUNCTIONS="${EXPORTED_FUNCTIONS}" \
    -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE="${LIBRARY_FUNCTIONS}" \
    -s WASM=1 -s EXIT_RUNTIME=0 -s INVOKE_RUN=0 \
    -s MODULARIZE=1 \
    -s EXPORT_NAME=Legroast \
    -O2 \
    --memory-init-file 0 \
    -o legroast.js
```
