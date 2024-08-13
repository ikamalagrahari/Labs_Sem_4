/*
	utility.h	Utility functions.
	Copyright (c) 1996,1997 by Christopher Heng. All rights reserved.

	$Id: utility.h 1.3 2002/06/20 06:44:32 chris Exp $
*/

#if !defined(UTILITY_H_INCLUDED)
#define	UTILITY_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

/* function declarations */
#if defined(__WATCOMC__)	/* errnomem() never returns */
#pragma aux errnomem aborts
#endif
extern void errnomem ( int exitcode );
extern void * xmalloc ( size_t len );
extern char * xstrdup( const char * s );

#if defined(__cplusplus)
}
#endif


#endif
