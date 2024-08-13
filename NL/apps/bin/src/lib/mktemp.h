/*
	mktemp.h	Declares my mktemp() function.
	Copyright (c) 1996,1997 by Christopher Heng. All rights reserved.

	$Id: mktemp.h 1.3 2002/06/20 06:44:30 chris Exp $
*/

#if !defined(MKTEMP_H_INCLUDED)
#define	MKTEMP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* macros */
#define	MKTEMP_TEMPLATE	"XXXXXX"

/* functions declarations */
extern char * mktemp ( char * templ );

#ifdef __cplusplus
}
#endif

#endif
