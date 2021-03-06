/* Copyright 2008 BORDEAUX I UNIVERSITY & INRIA 
**
** This file is part of the PaStiX parallel sparse matrix package.
**
** This software is governed by the CeCILL-C license under French law
** and abiding by the rules of distribution of free software. You can
** use, modify and/or redistribute the software under the terms of the
** CeCILL-C license as circulated by CEA, CNRS and INRIA at the following
** URL: "http://www.cecill.info".
** 
** As a counterpart to the access to the source code and rights to copy,
** modify and redistribute granted by the license, users are provided
** only with a limited warranty and the software's author, the holder of
** the economic rights, and the successive licensors have only limited
** liability.
** 
** In this respect, the user's attention is drawn to the risks associated
** with loading, using, modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean that it is complicated to manipulate, and that also
** therefore means that it is reserved for developers and experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards
** their requirements in conditions enabling the security of their
** systems and/or data to be ensured and, more generally, to use and
** operate it in the same conditions as regards security.
** 
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
*/
/************************************************************/
/**                                                        **/
/**   NAME       : kass.h                                  **/
/**                                                        **/
/**   AUTHORS    : Pascal HENON                            **/
/**                                                        **/
/**   FUNCTION   : Compute a block structure of the factor **/
/**                obtained by a ILU(k) factorization      **/
/**                                                        **/
/**                                                        **/
/**   DATES      : # Version 0.0  : from : 30/01/2006      **/
/**                                 to                     **/
/**                                                        **/
/************************************************************/

void kass(int            levelk, 
	  int            rat, 
	  SymbolMatrix * symbptr, 
	  PASTIX_INT            baseval,
	  PASTIX_INT            vertnbr, 
	  PASTIX_INT            edgenbr, 
	  PASTIX_INT          * verttab,
	  PASTIX_INT          * edgetab, 
	  Order        * orderptr, 
	  MPI_Comm       pastix_comm);

/* void kass(int alpha, int rat, SymbolMatrix * symbptr, Graph * graphptr, Order * orderptr, MPI_Comm pastix_comm); */

void ifax(PASTIX_INT n, PASTIX_INT *ia, PASTIX_INT *ja, PASTIX_INT levelk, PASTIX_INT  cblknbr, PASTIX_INT *rangtab, PASTIX_INT *perm, PASTIX_INT *iperm, SymbolMatrix *symbmtx);

