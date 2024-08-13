/*
	tofrodos.c	Converts text files between DOS and Unix formats.
	Copyright (c) 1996-2003 by Christopher Heng. All rights reserved.

	$Id: tofrodos.c 1.10 2003/11/26 15:20:40 chris Exp $
*/

/* this should always be first */
#include "config.h"

/* standard headers */
#include <signal.h>	/* signal() */
#include <stdio.h>	/* FILE functions */
#include <stdlib.h>	/* EXIT_SUCCESS, mkstemp() in some systems */
#include <string.h>	/* strrchr(), strlen(), strcpy(), strcat() */
#include <sys/stat.h>	/* stat() */

#if defined(UNIX)
#if defined(MAXPATHLEN_HEADER)
#include MAXPATHLEN_HEADER
#endif
#endif

#if defined(_MSC_VER) || defined(__WATCOMC__)
#include <sys/utime.h>
#else	/* everybody else keeps this in the include directory */
#if defined(UNIX)
#include <sys/types.h>
#endif
#include <utime.h>
#endif

/* conditionally included headers */
#if defined(MSDOS) || defined(WIN32)
#include <fcntl.h>	/* O_BINARY */
#include <io.h>		/* chmod(), setmode(), isatty(), mktemp() (VC++) */
#endif

#if defined(HAVE_GETOPT_H)
#include <getopt.h>	/* optind, getopt() */
#endif

#if defined(HAVE_MKTEMP_H) && defined(MKTEMP_HEADER)
#include MKTEMP_HEADER
#endif

#if defined(HAVE_UNISTD_H)
#include <unistd.h>	/* chmod(), mktemp(), isatty(), chown(), readlink(), mkstemp() in some systems, (getopt()) */
#endif

#if defined(__DJGPP__) || defined(__GO32__)
#include <dir.h>
#endif

/* our headers */
#include "emsg.h"
#include "tofrodos.h"
#include "utility.h"
#include "version.h"

/* macros */
#define	BAKEXT		".bak"	/* backup file extension */
#define	DIRSLASH	'/'	/* works for both MSDOS and Unix */
#define	DIRSLASHSTR	"/"
#define	MKTEMP_TEMPL	"XXXXXX"
#define	NEWBUFSIZ	16384	/* buffer size for the files */

/* conditional macros */
#if defined(MSDOS) || defined(WIN32)
#if !defined(_MAX_DIR) || (_MAX_DIR < 260)	/* MAXDIRSIZE */
#define MAXDIRSIZE	260
#else
#define	MAXDIRSIZE	_MAX_DIR
#endif
#if !defined(_MAX_NAME) || (_MAX_NAME < 260)	/* MAXFILESIZE */
#define MAXFILESIZE	260
#else
#define	MAXFILESIZE	_MAX_NAME
#endif
#if !defined(_MAX_PATH) || (_MAX_PATH < 260)	/* MAXPATHSIZE */
#define	MAXPATHSIZE	260
#else
#define	MAXPATHSIZE	_MAX_PATH
#endif
#if !defined(_MAX_DRIVE)
#define	_MAX_DRIVE	3		/* for the benefit of djgpp */
#endif
#endif

#if defined(MSDOS) || defined(WIN32)
#define	INFILEMODE	"rb"
#define	OUTFILEMODE	"wb"
#else
#define	INFILEMODE	"r"
#define	OUTFILEMODE	"w"
#endif

#if !defined(MSDOS)
#define	CURRENTDIR	"./"
#endif


/* global variables */
int abortonerr ; /* 1 if should abort when there is error in any file */
		/* in a list of files, 0 carry on (default) */
int alwaysconvert ; /* convert all \r\n to \r\r\n when direction */
		/* is UNIXTODOS, and delete all \r when direction is */
		/* DOSTOUNIX */
int direction = DEFDIRECTION ; /* UNIXTODOS or DOSTOUNIX */
int forcewrite ; /* convert even if file is not writeable */
int preserve ;	/* 1 if we are to preserve owner (Unix) and date (all) */
char * progname = VERSN_PROGNAME ;/* name of binary (ie, argv[0]) */
int overwrite = 1 ;	/* 1 = overwrite original file, 0 = make backup */
int verbose ;

/* local variables */
static char * infilename = "stdin" ;
static FILE * tempfp ;
static char * tempfilename ;

/* local functions */
#if !defined(UNIX)
static int checkmode ( char * filename, unsigned short * origfilemodep,
	struct utimbuf * filetimebufp );
#else
static int checkmode ( char * filename, unsigned short * origfilemodep,
	struct utimbuf * filetimebufp, uid_t * ownerp, gid_t * groupp );
#endif
static int convert ( FILE * infp, FILE * outfp );
static int openandconvert ( char * filename );
#if !defined(UNIX)
#define openandconvert_preamble	openandconvert
#else
static int openandconvert_preamble ( char * filename );
#endif

/*
	main

	tofrodos converts ASCII text files to/from a DOS CR-LF deliminated
	form from/to a Unix LF deliminated form.

	Usage: tofrodos [options] [file...]

	Exit codes:
		EXIT_SUCCESS	success	(stdlib.h)
		EXIT_ERROR	error	(tofrodos.h)
*/
int main ( int argc, char ** argv )
{
	/* initialise and parse the options */
	if (init( argv[0] ) || parseargs( argc, argv ))
		return EXIT_ERROR ;

	/* check if we are to convert from stdin */
	if (argc == optind) {
	    if (isatty( fileno( stdin ) )) {
		/* stdin must be redirected else you should supply a */
		/* filename. */
		fprintf( stdout, EMSG_NOFILENAME, progname );
		return EXIT_ERROR ;
	    }
	    /* otherwise stdin has been redirected */
#if defined(MSDOS) || defined(WIN32)
	    /* need to make sure the input and output files are binary */
	    /* on MSDOS and WIN32 */
	    setmode( fileno( stdin ), O_BINARY );
	    setmode( fileno( stdout ), O_BINARY );
#endif
	    return openandconvert( NULL );
	}

	/* if we reach here, we have a (list?) of files to convert */
	/* (ignore stdin) */
	while (optind < argc) {
	    if (verbose)
			puts( argv[optind] );
	    if (openandconvert_preamble( argv[optind] ) != 0 && abortonerr)
			return EXIT_ERROR ;
	    optind++ ;
	}

	return EXIT_SUCCESS ;
}

/*
	sighandler

	Handles SIGINT and SIGTERM. Prints a message, closes and
	deletes the temporary files and quits with EXIT_ERROR.

        It never returns (and Watcom C knows it).
*/
void sighandler ( int sig )
{
	/* restore signal handler, in case we have the old unsafe */
        /* behaviour */
	signal( sig, sighandler );

	/* print error message if verbose */
	if (verbose)
		fprintf( stderr, EMSG_SIGNAL, progname );

	/* close the temporary file and delete it */
	if (tempfp != NULL) {
		fclose( tempfp );
		tempfp = NULL ;
	}
	if (tempfilename != NULL) {
		remove( tempfilename );
                tempfilename = NULL ;
	}

        exit( EXIT_ERROR );
}

/* ---------------------------- local functions --------------------- */
/*
	checkmode

	Checks that the file we are supposed to convert is indeed
	writeable. We don't really need for it to be writeable, since
	we actually open a new file and eventually delete the current
	file.

	However, if a file is marked not-writeable, we should at least
	respect the user's choice and abort unless he flags the
	forcewrite flag.

	At the same time we also save the current mode of the file
	so that we can set the converted file to the same mode. The
	value is saved in the variable pointed to by origfilemodep.

	Returns: 0 on success, -1 on error.

	If -1 is returned, it could mean one of few things:
	1) some component of the path was not valid (directory or the file
	itself) (DOS/Unix) or search permission was denied (Unix)
	2) the file is not readable
	3) the file is not writeable and forcewrite is zero.
	An error message is displayed on error.
*/
#if !defined(UNIX)
static int checkmode ( char * filename, unsigned short * origfilemodep,
	struct utimbuf * filetimebufp )
#else
static int checkmode ( char * filename, unsigned short * origfilemodep,
	struct utimbuf * filetimebufp, uid_t * ownerp, gid_t * groupp )
#endif
{
	struct stat statbuf ;

	/* get the file information */
	if (stat( filename, &statbuf )) {
		/* couldn't stat the file. */
		fprintf( stdout, EMSG_ACCESSFILE, progname, filename );
		return -1 ;
	}
	/* save the mode */
	*origfilemodep = statbuf.st_mode ;
	/* save the file times for restore later */
	filetimebufp->actime = statbuf.st_atime ;
	filetimebufp->modtime = statbuf.st_mtime ;
#if defined(UNIX)
	/* save the owner and group id */
	*ownerp = statbuf.st_uid ;
	*groupp = statbuf.st_gid ;
#endif
	/* check if file can be read - this is actually redundant for */
	/* DOS systems. */
	if (!(statbuf.st_mode & S_IRUSR)) { /* not readable */
		fprintf( stdout, EMSG_NOTREADABLE, progname, filename );
		return -1 ;
	}
	/* check if file can be written to, if forcewrite is 0 */
	if (!forcewrite && !(statbuf.st_mode & S_IWUSR)) { /* not writeable */
		fprintf( stdout, EMSG_NOTWRITEABLE, progname, filename );
		return -1 ;
	}
	return 0 ;
}

/*
	convert

	Does the actual work of converting infp to outfp.

	If direction is DOSTOUNIX, "\r\n" pairs will be converted to
	'\n'. However, standalone '\r' without a '\n' immediately
	following will not be eliminated unless alwaysconvert is
	nonzero.

	If direction is UNIXTODOS, '\n' will be converted to "\r\n".
	However "\r\n" pairs are not converted to '\r\r\n' unless
	alwaysconvert is nonzero.

        Returns 0 on success, -1 on error.
*/
static int convert ( FILE * infp, FILE * outfp )
{
	int prevch ;
	int c ;

	/* actually it is very simple to do the conversion in DOS/WIN32 */
	/* because the stdio library does this work automatically for */
	/* us. But because we want this program to work on Linux as */
	/* well, a little bit of work stands before us (but only a little). */

	prevch = EOF ;

	if (direction == UNIXTODOS) {
		/* basically we convert all newlines to "\r\n" unless */
		/* the file is already in "\r\n" format. The problem here */
		/* is when you have special situations like a Unix */
		/* text file with lines that have a '\r' just */
		/* before a '\n'. These lines will */
		/* not be converted to "\r\r\n" since the function */
		/* below assumes the line has already been converted. */
		/* To force the conversion of all \n to \r\n regardless */
		/* of preceding characters, set alwaysconvert to 1. */
		while ( (c = getc( infp )) != EOF ) {
			if (c == '\n' && (alwaysconvert || prevch != '\r')) {
				if (putc( '\r', outfp ) == EOF)
					break ;
			}
#if defined(__BORLANDC__)
#pragma warn -sig
#endif
			/* always emit the current character */
			if (putc( c, outfp ) == EOF)
				break ;
#if defined(__BORLANDC__)
#pragma warn .sig
#endif
			prevch = c ;                        	 
		}
	}
	else if (direction == DOSTOUNIX) {
	    if (!alwaysconvert) {
		/* basically we withhold emitting any '\r' until we */
		/* are sure that the next character is not a '\n'. */
		/* If it is not, we emit the '\r', if it is, we */
		/* only emit the '\n'. */
		while ( (c = getc( infp )) != EOF ) {
			if (prevch == '\r') {
				/* '\r' is a special case because we don't */
				/* emit a '\r' until the next character */
				/* has been read */
				if (c == '\n') { /* a "\r\n" pair */
#if defined(__BORLANDC__)
#pragma warn -sig
#endif
					/* discard previous '\r' and */
					/* just put the '\n' */
					if (putc( c, outfp ) == EOF)
						break ;
#if defined(__BORLANDC__)
#pragma warn .sig
#endif
				}
				else {	/* prevch was a standalone '\r' */
                                	/* emit the standalone '\r' */
					if (putc( '\r', outfp ) == EOF)
						break ;
					/* emit the current character if */
                                        /* it is not a '\r' */
#if defined(__BORLANDC__)
#pragma warn -sig
#endif
					if (c != '\r') {
						if (putc( c, outfp ) == EOF)
							break ;
					}
#if defined(__BORLANDC__)
#pragma warn .sig
#endif
				}
			}
			else { /* prevch was not '\r' */
				/* emit current character if it is not */
				/* a '\r' */
				if (c != '\r') {
#if defined(__BORLANDC__)
#pragma warn -sig
#endif
					if (putc( c, outfp ) == EOF)
						break ;
#if defined(__BORLANDC__)
#pragma warn .sig
#endif
				}
			}
			prevch = c ;
		}
	    }	/* alwaysconvert == 0 */
	    else { /* eliminate all '\r' */
		while ((c = getc( infp )) != EOF) {
			if (c != '\r') {
#if defined(__BORLANDC__)
#pragma warn -sig
#endif
				if (putc( c, outfp ) == EOF)
					break ;
#if defined(__BORLANDC__)
#pragma warn .sig
#endif
			}
			/* else skip all carriage returns */
		}
	    }
	}
	else {
		fprintf( stderr, EMSG_INTERNAL, progname, EINTNL_DIRECTION );
		return -1 ;
	}

	/* if we reach here, either we've reached an EOF or an error */
	/* occurred. */
	if (!feof( infp )) { /* error */
		fprintf( stderr, EMSG_CONVERT, progname, infilename );
                return -1 ;
	}
	return 0 ;
}

#if defined(UNIX)
/*
	openandconvert_preamble

	On a Unix-type system (including Linux and BSD systems), it is
	possible for a given filename to be merely a symlink. This function
	obtains the real filename given the symlink, and calls
	openandconvert() with the real file name. It simply calls openandconvert()
	if the filename is not a symlink.

	Note: this function only exists on Unix-type systems. On MSDOS and Windows,
	openandconvert_preamble() is merely a macro that resolves to
	openandconvert().

	Returns: whatever openandconvert() returns. (0 on success, -1 on
	error. Error messages will be displayed on error before returning.
*/
static int openandconvert_preamble ( char * filename )
{
	struct stat statbuf ;
	char		realfilepath[MAXPATHLEN+1] ;
	int			len ;

	/* get the file information */
	if (lstat( filename, &statbuf )) {
		/* couldn't stat the file. */
		fprintf( stdout, EMSG_ACCESSFILE, progname, filename );
		return -1 ;
	}

	if (S_ISLNK(statbuf.st_mode)) {
		/* get the real filename for symbolic links */
		/* Note: the S_ISLNK() macro is supposed to exist in sys/stat.h in */
		/* Early Unices may not have this macro. If it does not exist, you */
		/* may have to define it yourself, a la S_ISDIR() and family. */
		/* eg, #define S_ISLNK(x) (((x) & S_IFMT) == S_IFLNK) */
		/* or something like that. */

		if ((len = readlink( filename, realfilepath, (sizeof(realfilepath) - 1) )) != -1) {
			/* got to null terminate the string - there is always space because */
			/* we passed readlink() the size of the buffer less 1. */
			realfilepath[len] = '\0' ;
			if (verbose)
				printf( "%s resolves to %s\n", filename, realfilepath );
			return openandconvert( realfilepath );
		}
		fprintf( stderr, EMSG_SYMLINK, progname, filename );
		return -1 ;
	}
	/* If we reach here, "filename" is not a symbolic link */
	return openandconvert( filename );
}
#endif


/*
	openandconvert

	Called to open the files and convert the contents. If you want
	it to convert stdin to stdout, call it with NULL as the filename
	argument; otherwise pass the function the name of the input file.

	Returns: 0 on success, -1 on error. Error messages will be
        displayed on error before returning.
*/
static int openandconvert ( char * filename )
{
	FILE *			infp ;
	FILE *			outfp ;
	int				err ;
	char *			bakfilename ;
	unsigned short	origfilemode ;	/* file mode of original file */
	struct utimbuf	filetimebuf ;
#if defined(MSDOS) || defined(WIN32)
	char 			drv[_MAX_DRIVE];
	char 			dir[MAXDIRSIZE];
	char 			fname[MAXFILESIZE];
	char 			tempname[MAXPATHSIZE];
#else
	char * 			s ;
	char * 			t ;
	char * 			p ;
	size_t 			len ;
	int				replacech ;
	char			c ;
#endif
#if defined(UNIX)
	uid_t			ownerid ;
	gid_t			groupid ;
#endif
#if NEWBUFSIZ > BUFSIZ
	char *			inbufptr ;
	char *			outbufptr ;
#endif
#if defined(HAVE_MKSTEMP)
	    int  		tempfiledes;
#endif

	/* make sure we initialise */
	bakfilename = NULL ;

	if (filename != NULL) { /* stdin is not redirected */

		/* check for appropriate permissions on the file */
		/* also saves the mode in origfilemode */
#if !defined(UNIX) 
		if (checkmode( filename, &origfilemode, &filetimebuf ))
			return -1 ;
#else
		if (checkmode( filename, &origfilemode, &filetimebuf,
			&ownerid, &groupid ))
			return -1 ;
#endif

	    /* we need to create a temporary and backup filename (if */
	    /* applicable) in the same directory */
	    /* as our file. This is easy to do for DOS since we have the */
	    /* _splitpath(), _makepath() functions. */
#if defined(MSDOS) || defined(WIN32)
	    _splitpath( filename, drv, dir, fname, NULL );
	    _makepath( tempname, drv, dir, MKTEMP_TEMPL, NULL );
	    tempfilename = xstrdup( tempname );
	    if (!overwrite) {
			_makepath( tempname, drv, dir, fname, BAKEXT );
			if (!strcmp( tempname, filename )) {
				fprintf( stderr, EMSG_BAKFILENAME, filename );
				goto err_freetempfn ;
			}
			bakfilename = xstrdup( tempname );
	    }
#else	/* neither MSDOS nor WIN32 */
	    /* check if there is a path prefix */
	    if ((s = strrchr( filename, DIRSLASH )) != NULL) {
			c = *++s ;	/* save the character after the slash */
			*s = '\0';
			replacech = 1 ;
			len = strlen( filename ) ;
			t = filename ;
	    }
	    else {
	    	replacech = c = 0 ;	/* I init c to suppress the warning */
					/* issued by gcc -Wall */
	    	len = sizeof(CURRENTDIR) - 1 ;
	    	t = CURRENTDIR ;
	    }
	    /* got to add the extension manually */
	    tempfilename = xmalloc( len + sizeof(MKTEMP_TEMPL) );
	    strcpy( tempfilename, t ); /* path leading to filename */
	    strcat( tempfilename, MKTEMP_TEMPL ); /* filename */
	    if (replacech)
		*s = c ;
	    if (!overwrite) {
			bakfilename	= xmalloc( strlen( filename ) +
							sizeof( BAKEXT ) );
			/* copy the filename */
			strcpy( bakfilename, filename );
			/* strip any trailing extension */
			p = bakfilename + strlen( bakfilename ) - 1 ;
			while (p != bakfilename) {
				if (*p == '.') {
					*p = '\0' ; /* strip current extension */
					break ;
				}
				if (*p == '/') /* no extension */
					break ;
				p-- ;
			}
			/* add the new extension */
			strcat( bakfilename, BAKEXT );
	    }
#endif

#if defined(HAVE_MKSTEMP)
	    /* create the temporary file */
	    if ((tempfiledes = mkstemp( tempfilename )) == -1) {
#else
	    /* make the temp filename */
	    if (mktemp( tempfilename ) == NULL) {
#endif
			fprintf( stderr, EMSG_NOTEMPNAME, progname, filename );
err_freebakfn:
			if (!overwrite && bakfilename != NULL)
				free( bakfilename );
#if defined(MSDOS) || defined(WIN32)
err_freetempfn:
#endif
			free( tempfilename );
			tempfilename = NULL ;
			return -1 ;
	    }

	    /* open the filename as the input file */
	    if ((infp = fopen( filename, INFILEMODE )) == NULL) {
			fprintf( stderr, EMSG_OPENFILE, progname, filename );
			goto err_freebakfn ;
	    }
	    /* associate the infilename with the filename for error */
	    /* messages */
	    infilename = filename ;

	    /* open the temp file as the output file */
#if defined(HAVE_MKSTEMP)
	    if ((tempfp = fdopen( tempfiledes, OUTFILEMODE )) == NULL) {
#else
	    if ((tempfp = fopen( tempfilename, OUTFILEMODE )) == NULL) {
#endif
			fprintf( stderr, EMSG_CREATETEMP, progname, tempfilename, filename );
			fclose( infp );
			goto err_freebakfn ;
	    }
	    outfp = tempfp ;

	} /* if filename != NULL */
	else { /* filename == NULL, ie stdin is redirected */
		infp = stdin ;
		outfp = stdout ;

		/* not needed, but we do this for the record, and for */
		/* fussy compilers */
		origfilemode	= 0 ;
		memset( &filetimebuf, 0, sizeof( struct utimbuf ) );

#if defined(UNIX)
		ownerid	= groupid	= 0 ;
#endif

	}

#if NEWBUFSIZ > BUFSIZ
	/* (don't use xmalloc() because if we can't get what we want, */
	/* we just don't bother, and go ahead with the minimum) */
	if ((inbufptr = malloc( NEWBUFSIZ )) != NULL)
		setvbuf( infp, inbufptr, _IOFBF, NEWBUFSIZ );
	if ((outbufptr = malloc( NEWBUFSIZ )) != NULL)
		setvbuf( outfp, outbufptr, _IOFBF, NEWBUFSIZ );
#endif
	/* do the conversion */
	err = convert( infp, outfp );

	/* close the files */
	fclose( infp );
	fclose( outfp );

	if (filename == NULL) {
	    /* remove the output file handle from the global to avoid */
	    /* double attempts to close the same file */
	    tempfp = NULL ;
	}

#if NEWBUFSIZ > BUFSIZ
	/* got to free buffers we allocated first */
	if (inbufptr != NULL)
		free( inbufptr );
	if (outbufptr != NULL)
		free( outbufptr );
#endif

	if (filename != NULL) { /* stdin was not redirected */

	    if (err) { /* there was an error */
        	/* delete the temp file since we've already created it */
        	remove ( tempfilename );
			goto err_freebakfn ;
	    }

	    /* if we need to back up, delete any backup files of the */
	    /* same name first (in case we are running on DOS where */
	    /* a rename does not delete the file automatically) */
	    if (!overwrite) {
			/* remove existing backup files of same name */
			remove( bakfilename );
			/* rename the original file to the back up name */
			rename( filename, bakfilename );
	    }
	    else { /* if we do not need to back up delete the original file */
#if defined(MSDOS) || defined(WIN32)
			/* for MSDOS, we need to make sure the file is writeable */
			/* otherwise we cannot delete! Under Unix, this is not */
			/* necessary, since a file can be deleted if we */
			/* have write permissions for the directory */
            chmod( filename, S_IRUSR|S_IWUSR );
#endif
			remove( filename );
	    }

	    /* rename the temp file to the original file name */
	    rename( tempfilename, filename );

	    /* remove the temp file name from the global for our */
	    /* signal handler*/
	    tempfilename = NULL ;

	    /* free memory we allocated */
	    if (!overwrite && bakfilename != NULL)
			free( bakfilename );

		if (preserve) {
			/* change to the original file time */
			utime( filename, &filetimebuf );
#if defined(UNIX)
			/* Change the owner to the owner of the original file. */
			/* We ignore errors since the user might simply want */
			/* to use -p to set the file time, and not being root, */
			/* chown() will fail on Linux. However, we issue an error */
			/* message if the user wants verbosity. */
			if (chown( filename, ownerid, groupid ) && verbose)
				fprintf( stdout, EMSG_CHOWN, progname, filename );
#endif
		}

	    /* change the file mode to reflect the original file mode */
        chmod( filename, origfilemode );

	}	/* stdin was not redirected */

	return err ;
}
