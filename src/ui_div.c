/* mpc_ui_div -- Divide an unsigned long int by a complex number.

Copyright (C) 2002 Andreas Enge, Paul Zimmermann

This file is part of the MPC Library.

The MPC Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPC Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPC Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include <limits.h>
#include "gmp.h"
#include "mpfr.h"
#include "mpc.h"
#include "mpc-impl.h"

int
mpc_ui_div (mpc_ptr a, unsigned long int b, mpc_srcptr c, mpc_rnd_t rnd)
{
  int inex;
  mpc_t bb;

  if (mpfr_cmp_ui (MPC_IM(c), 0) == 0) /* c is real */
    {
      inex = mpfr_ui_div (MPC_RE(a), b, MPC_RE(c), MPC_RND_RE(rnd));
      mpfr_set_ui (MPC_IM(a), 0, MPC_RND_IM(rnd));
      return MPC_INEX(inex, 0);
    }

  mpc_init2 (bb, sizeof(unsigned long int) * CHAR_BIT);

  mpc_set_ui (bb, b, rnd); /* exact */

  inex = mpc_div (a, bb, c, rnd);

  mpc_clear (bb);

  return inex;
}