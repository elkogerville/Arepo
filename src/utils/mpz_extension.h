#ifndef MPZ_EXTENSION_H
#define MPZ_EXTENSION_H

#include <gmp.h>

#if USEDBITS > 31
typedef signed long long int IntegerMapType;
void MY_mpz_set_si(mpz_t dest, signed long long int val);
void MY_mpz_mul_si(mpz_t prod, mpz_t mult, signed long long int val);
void MY_mpz_sub_ui(mpz_t prod, mpz_t mult, unsigned long long int val);
#else /* #if USEDBITS > 31 */
typedef signed long int IntegerMapType;
#define MY_mpz_set_si mpz_set_si
#define MY_mpz_mul_si mpz_mul_si
#define MY_mpz_sub_ui mpz_sub_ui
#endif /* #if USEDBITS > 31 #else */

#endif
