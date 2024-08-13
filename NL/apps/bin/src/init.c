/*
	init.c		Initialisation functions.
	Copyright (c) 1996-2003 by Christopher Heng. All rights reserved.

	$Id: init.c 1.10 2003/11/26 15:20:40 chris Exp $
*/

/* this should always be first */
#include "config.h"

/* standard headers */
#if defined(HAVE_GETOPT_H)
#include <getopt.h>	/* getopt() (what else?) */
#endif

#include <signal.h>	/* signal() (surprise!) */
#include <stdlib.h>	/* _splitpath(), _MAX_FNAME, exit, EXIT_SUCCESS */
#include <stdio.h>	/* EOF */
#include <string.h>	/* stricmp() */

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(__DJGPP__) || defined(__GO32__)
#include <dir.h>
#endif

/* our own headers */
#include "emsg.h"
#include "tofrodos.h"
#include "utility.h"
#include "version.h"

/* macros */
#define	HELPFMT		"Usage: %s [options] [file...]\n"\
			"-a\tAlways convert (DOS to Unix: kill all CRs;\n"\
			"\tUnix to DOS: convert all LFs to CRLFs)\n"\
			"-b\tMake backup of original file (.bak).\n"\
			"-d\tConvert DOS to Unix.\n"\
			"-e\tAbort processing files on error in any file.\n"\
			"-f\tForce: convert even if file is not writeable.\n"\
			"-h\tDisplay help on usage and quit.\n"\
			"-o\tOverwrite original file (no backup).\n"\
			"-p\tPreserve file owner and time.\n"\
			"-u\tConvert Unix to DOS.\n"\
			"-v\tVerbose.\n"\
			"-V\tShow version and quit.\n"
#define	OPTLIST		"abdefhopuvV"
#define	VERFMT		"%s Ver %d.%d "\
			"Converts text files between DOS and Unix formats.\n"\
			"Copyright (c) 1996-2003 by Christopher Heng. "\
                        "All rights reserved.\n"

#if defined(MSDOS) || defined(WIN32)
#if !defined(_MAX_NAME) || (_MAX_NAME < 260)
#define MAXFILESIZE	260
#else
#define	MAXFILESIZE	_MAX_NAME
#endif
#endif

#if !defined(MSDOS)
#define	DIRSLASH	'/'
#endif


/* local functions */
static void showhelp ( void );
static void showversion ( void );

/*
	init

	Checks for correct operating system version (DOS only).
	Sets the default direction of conversion.
	Sets the signal traps.

	Returns 0 on success, -1 on error.
*/
int init ( char * firstarg )
{
#if defined(MSDOS) || defined(WIN32)
	char filename[MAXFILESIZE];
#else
	char * s ;
#endif

#if defined(MSDOS) && !defined(__DJGPP__) && !defined(__GO32__)
	/* Check that we have the minimum version of DOS needed. */
	/* We only run on DOS 3.1 and above. */
	if (_osmajor < 3 ||
		(_osmajor == 3 && _osminor < 10)) {
		fprintf( stderr, EMSG_WRONGDOSVER, progname );
		return -1 ;
	}
#endif

	/* set the name of the binary to set default direction of */
	/* conversion */
#if defined(MSDOS) || defined(WIN32)
	/* got to extract the name from the full path and extension */
	_splitpath( firstarg, NULL, NULL, filename, NULL );
	progname = xstrdup( filename );
#else	/* neither MSDOS nor WIN32 - assume Unix */
	/* got to wipe out the path prefix if any */
	if ((s = strrchr( firstarg, DIRSLASH )) == NULL)
		progname = firstarg ;
	else { /* we got the last slash - let's get rid of it */
		progname = ++s ;
	}
#endif

	/* set the default direction: Unless we are explicitly named */
	/* to convert in a particular direction, the default direction */
	/* depends on the system. If we are on a DOS system, it is to */
	/* convert from Unix to DOS. If we are on a Unix system, it */
	/* is to convert from DOS to Unix. */
	if (!stricmp( progname, FROMDOSNAME ) ||
		!stricmp( progname, FROMDOSNAME2 ))
		direction = DOSTOUNIX ;
	else if (!stricmp( progname, TODOSNAME ) ||
		!stricmp( progname, TODOSNAME2 ))
		direction = UNIXTODOS ;

	/* set the signal traps - we use the old Unix version 7 signal */
	/* mechanism since that is most portable to DOS. In any case, */
	/* we don't do anything sophisticated when we receive a signal */
	/* except cleaning up and quitting! */
	if (signal( SIGINT, sighandler ) == SIG_IGN)
		signal( SIGINT, SIG_IGN );
	if (signal( SIGTERM, sighandler ) == SIG_IGN)
		signal( SIGTERM, SIG_IGN );

	return 0 ;
}

/*
	parseargs

	Parses the options.

        Returns 0 on success, -1 on error.
*/
int parseargs ( int argc, char ** argv )
{
	int c ;

	while ((c = getopt( argc, argv, OPTLIST )) != EOF) {
		switch( c ) {
			case 'a': /* force conversion of all \r\n to \n */
				alwaysconvert = 1 ;
				break ;
			case 'b': /* make backup of original file */
				overwrite = 0 ;
				break ;
			case 'd': /* DOS to Unix */
				direction = DOSTOUNIX ;
				break ;
			case 'e': /* abort processing list of files if */
				  /* we encounter errors in any file in */
				  /* a list of file names */
				abortonerr = 1 ;
				break ;
			case 'f': /* convert even if file is not writeable*/
				forcewrite = 1 ;
				break ;
			case 'h': /* display short usage screen and quit */
               	showhelp() ;
				exit( EXIT_SUCCESS );
				break ;
			case 'o': /* overwrite original file (default) */
            	overwrite = 1 ;
            	break ;
			case 'p': /* preserve file owner and date */
				preserve = 1 ;
				break ;
			case 'u': /* Unix to DOS */
				direction = UNIXTODOS ;
				break ;
			case 'v': /* verbose */
				verbose = 1 ;
				break ;
			case 'V': /* show version and quit */
				showversion() ;
				exit( EXIT_SUCCESS );
				break ;
			default:  /* error */
				return -1 ;
		}
	}
	if (verbose)
        	showversion();
	return 0 ;
}

static void showversion ( void )
{
	static int vershown ;

	if (!vershown) {
		printf( VERFMT, VERSN_PROGNAME, VERSN_MAJOR, VERSN_MINOR );
		vershown = 1 ;
	}
	return ;
}

/*
	showhelp

	Display the short usage help screen.
*/
static void showhelp ( void )
{
	showversion();
	printf( HELPFMT, progname );
	return ;
}
