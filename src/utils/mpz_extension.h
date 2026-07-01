/*!
 * \copyright   This file is part of the public version of the AREPO code.
 * \copyright   Copyright (C) 2009-2019, Max-Planck Institute for Astrophysics
 * \copyright   Developed by Volker Springel (vspringel@MPA-Garching.MPG.DE) and
 *              contributing authors.
 * \copyright   Arepo is free software: you can redistribute it and/or modify
 *              it under the terms of the GNU General Public License as published by
 *              the Free Software Foundation, either version 3 of the License, or
 *              (at your option) any later version.
 *
 *              Arepo is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *              GNU General Public License for more details.
 *
 *              A copy of the GNU General Public License is available under
 *              LICENSE as part of this program.  See also
 *              <https://www.gnu.org/licenses/>.
 *
 * \file        src/utils/mpz_extension.h
 * \date        05/2018
 * \brief       Header for mpz functions; **if included, must be included after voronoi.h**
 * \details     Integer arithmetic used by Voronoi mesh construction.
 *
 *
 * \par Major modifications and contributions:
 *
 * - DD.MM.YYYY Description
 * - 29.05.2018 Prepared file for public release -- Rainer Weinberger
 */

#ifndef MPZ_EXTENSION_H
#define MPZ_EXTENSION_H

#include <gmp.h>

#if USEDBITS > 31 /* defined in voronoi.h */
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
