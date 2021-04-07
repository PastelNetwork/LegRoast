#include <emscripten/bind.h>

#include <string>
#include <iostream>

#include <sign.h>
#include <parameters.h>

using namespace emscripten;

void _keygen(uintptr_t pk, uintptr_t sk)
{
  keygen((unsigned char*)pk, (unsigned char*)sk);
}

void _sign(uintptr_t sk, uintptr_t pk, uintptr_t msg, int msg_len,  uintptr_t sig)
{
  uint64_t sig_len;
  sign((const unsigned char*)sk, (const unsigned char*)pk, (const unsigned char*)msg, msg_len, (unsigned char*)sig, &sig_len);
}

int _verify(uintptr_t pk, uintptr_t msg, int msg_len, uintptr_t sig)
{
  return verify((const unsigned char*)pk, (const unsigned char*)msg, msg_len, (const unsigned char*)sig);
}

void _test()
{
  std::cout << "PK_BYTES: " << PK_BYTES << std::endl;

  unsigned char* pk = (unsigned char*)malloc(PK_BYTES * sizeof(unsigned char));
  unsigned char* sk = (unsigned char*)malloc(SK_BYTES * sizeof(unsigned char));

  unsigned char msg[1];
  msg[0] = 42;

  unsigned char* sig = (unsigned char*)malloc(SIG_BYTES * sizeof(unsigned char));
  uint64_t sig_len;

  std::cout << PK_BYTES << " " << SK_BYTES << " " << SIG_BYTES << std::endl;

  keygen(pk, sk);
  std::cout << "key generated" << std::endl;
  sign(sk, pk, msg, 1, sig, &sig_len);
  std::cout << "key signed" << std::endl;

  int v = verify(pk, msg, 1, sig);
  std::cout << "verify: " << v << std::endl;

  free(pk);
  free(sk);
  free(sig);
}

EMSCRIPTEN_BINDINGS(Legroast)
{
constant("SK_BYTES", SK_BYTES);
constant("PK_BYTES", PK_BYTES);
constant("SIG_BYTES", SIG_BYTES);
constant("SEED_BYTES", SEED_BYTES);
function("keygen", &_keygen);
function("sign", &_sign);
function("verify", &_verify);
function("test", &_test);
}

