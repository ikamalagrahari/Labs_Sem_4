/*
	mktemp.c	Create a temporary file name.
	Copyright (c) 1996,1997 by Christopher Heng. All rights reserved.

	$Id: mktemp.c 1.5 2002/06/20 06:44:30 chris Exp $

	This code is released under the terms of the GNU General Public
	License Version 2. You should have received a copy of the GNU
	General Public License along with this program; if not, write to the
	Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,
	USA.

	The mktemp() function does not exist in the Watcom 10.[0-6] library.
*/

#include <errno.h>	/* errno, ENOENT */
#include <io.h>		/* access() */
#include <string.h>	/* strlen(), strcmp() */
#include "mktemp.h"	/* our own header */

#define	MAXVAL	(65535u)	/* unsigned is at least this (ANSI) */

/*
	mktemp

	Returns a string containing a temporary filename.

	The caller must initialise "templ" to contain 6 trailing
	'X's. mktemp() will directly modify the templ contents,
	replacing the 'X's with the filename.

	WARNING: your prefix in "templ" + the six trailing 'X's,
	must not exceed the DOS filesystem naming limitations or
	unpredictable results may occur. For example, since a filename
	cannot exceed 8 characters in length, you cannot call
	mktemp() with a templ of "mytempXXXXXX". Note that
	"unpredictable results" does not mean that mktemp() will
	return NULL. It means exactly that _unpredictable_ results
	will occur (probably depending on your prefix).

	Returns: - pointer to "templ" on success;
		 - NULL on failure. Note that even if NULL is returned,
		the "templ" contents would have been changed
		as well.

	Example:
		char tempfilename[] = "\\tmp\\myXXXXXX" ;
*/
char * mktemp ( char * templ )
{
	static unsigned val ;
	static char fch = 'A' ;

	char *s ;
	char *startp ;
	size_t len ;
	unsigned tval ;

	/* do some sanity checks */
	/* make sure that templ is at least 6 characters long */
	/* and comprises the "XXXXXX" string at the end */
	if ((len = strlen(templ)) < 6 ||
		strcmp( (s = startp = templ + len - 6), MKTEMP_TEMPLATE ))
		return NULL ;
	for ( ; fch <= 'Z'; val = 0, fch++ ) {
		/* plug the first character */
		*startp = fch ;
		/* convert val to ascii */
		/* note that we skip the situation where val == MAXVAL */
		/* because if unsigned has a maximum value of MAXVAL */
		/* in an implementation, and we do a compare of */
		/* val <= MAXVAL, the test will always return true! */
		/* Our way, we have at least a cut-off point: MAXVAL. */
		for ( ; val < MAXVAL; ) {
			tval = val++ ;
			for (s = startp + 5; s > startp ; s--) {
				*s = (char) ((tval % 10) + '0') ;
				tval /= 10 ;
			}
			if (access( templ, 0 ) == -1 && errno == ENOENT)
				return templ ;
		}
	}
	return NULL ;
}
