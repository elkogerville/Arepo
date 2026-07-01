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
 * \file        src/init/endrun.c
 * \date        05/2018
 * \brief       Clean-up of a simulation run
 * \details     This file contains the function to clean up a simulation run.
 *
 * \par Major modifications and contributions:
 *
 * - DD.MM.YYYY Description
 * - 03.05.2018 Prepared file for public release -- Rainer Weinberger
 */

#include "../main/allvars.h"
#include "../main/proto.h"

#ifdef HAVE_HDF5
#include <hdf5.h>
#endif /* #ifdef HAVE_HDF5 */

#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>


/*! \brief This function ends the simulations in case of no error.
 *
 *  This method has to be called by all processes. It should be used only
 *  if the simulation ends without a errors.
 *  Otherwise terminate() should be used instead.
 *
 *  \return void
 */
void endrun()
{
  mpi_printf("Code run for %f seconds!\n", timediff(StartOfRun, second()));
  mpi_printf("endrun called, calling MPI_Finalize()\nbye!\n\n");
  fflush(stdout);

#ifdef HAVE_HDF5
  /*The hdf5 library will sometimes register an atexit() handler that calls its
   * error handler. In AREPO this is set to my_hdf_error_handler, which calls
   * MPI_Abort. Calling MPI_Abort after MPI_Finalize is not allowed.
   * Hence unset the HDF error handler here
   */
  H5Eset_auto(NULL, NULL);
#endif /* #ifdef HAVE_HDF5 */

#ifdef RUNNING_SAFETY_FILE
  if(All.Ti_Current < TIMEBASE) /* simulation has not reached the final time */
    {
      char running_fname[MAXLEN_PATH], running_done_fname[MAXLEN_PATH];
      sprintf(running_fname, "./running");
      sprintf(running_done_fname, "./running_done");
      rename(running_fname, running_done_fname);
      mpi_printf("moved ./running file to ./running_done, job can now restart.\n");
    }
  else
    mpi_printf("leaving ./running file in place since run is complete to prevent any restarts.\n");
#endif /* #ifdef RUNNING_SAFETY_FILE */

  MPI_Finalize();
  exit(0);
}
