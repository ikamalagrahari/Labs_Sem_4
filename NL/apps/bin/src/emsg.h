/*
	emsg.h		Error messages.
	Copyright (c) 1996-2003 by Christopher Heng. All rights reserved.

	$Id: emsg.h 1.5 2003/11/26 15:20:40 chris Exp $
*/

#if !defined(EMSG_H_INCLUDED)
#define	EMSG_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

/* macros */
#define	EMSG_BAKFILENAME	"%s: File cannot have a .bak extension "\
							"when used with -b flag.\n"
#define	EMSG_CONVERT		"%s: File read/write error while "\
							"converting %s.\n"
#define	EMSG_INTERNAL		"%s: Internal error: %s.\n"
#define	EMSG_NOFILENAME		"%s: Need to specify filename or redirect "\
							"stdin.\n"
#define	EMSG_NOMEM			"%s: Insufficient memory to run program.\n"
#define	EMSG_NOTEMPNAME		"%s: Unable to create temporary file for converting %s.\n"
#define	EMSG_OPENFILE		"%s: Unable to open file %s.\n"
#define	EMSG_SIGNAL			"%s: Terminated by user.\n"
#define	EMSG_WRONGDOSVER	"%s: Requires DOS 3.1 and above.\n"
#define	EMSG_ACCESSFILE		"%s: Unable to access file %s.\n"
#define	EMSG_NOTREADABLE	"%s: No read permission for %s.\n"
#define	EMSG_NOTWRITEABLE	"%s: No write permission for %s. Use -f to force conversion.\n"
#define	EMSG_CHOWN			"%s: Unable to change ownership of %s.\n"
#define	EMSG_SYMLINK		"%s: Unable to dereference symbolic link %s.\n"
#define	EMSG_CREATETEMP		"%s: Unable to create temporary file %s for converting %s.\n"

/* internal error macros */
#define	EINTNL_DIRECTION	"unknown direction"

#if defined(__cplusplus)
}
#endif

#endif
