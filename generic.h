/* generic.h -- anything you don't #undef at the end remains in effect.
   The ONLY things that go in here are generic indicator flags; it's up
   to your programs to declare and call things based on those flags.

   You should only need to make changes via a minimal system-specific section
   at the end of this file.  To build a new section, rip through this and
   check everything it mentions on your platform, and #undef that which needs
   it.  If you generate a system-specific section you didn't find in here,
   please mail me a copy so I can update the "master".

   I realize I'm probably inventing another pseudo-standard here, but
   goddamnit, everybody ELSE has already, and I can't include all of their
   hairball schemes too.  HAVE_xx conforms to the gnu/autoconf usage and
   seems to be the most common format.  In fact, I dug a lot of these out
   of autoconf and tried to common them all together using "stupidh" to
   collect data from platforms.

   In disgust...  _H*  940910, 941115.  Pseudo-version: 1.1  */

#ifndef GENERIC_H		/* only run through this once */
#define GENERIC_H

/* =============================== */
/* System calls, lib routines, etc */
/* =============================== */

/* How does your system declare malloc, void or char?  Usually void, but go
   ask the SunOS people why they had to be different... */
#define VOID_MALLOC

/* notably from fwtk/firewall.h: posix locking? */
#define HAVE_FLOCK		/* otherwise it's lockf() */

/* if you don't have setsid(), you might have setpgrp().
#define HAVE_SETSID

/* random() is generally considered better than rand() */
/* xxx: rand48? */
#define HAVE_RANDOM

/* if your machine doesn't have lstat(), it should have stat() [dos...] */
#define HAVE_LSTAT

/* different kinds of term ioctls.  How to recognize them, very roughly:
   sysv/POSIX_ME_HARDER:  termio[s].h, struct termio[s], tty.c_*[]
   bsd/old stuff:  sgtty.h, ioctl(TIOCSETP), sgttyb.sg_*, tchars.t_*
#define HAVE_TERMIOS

/* dbm vs ndbm */
#define HAVE_NDBM

/* extended utmp/wtmp stuff.  MOST machines still do NOT have this SV-ism */
#define UTMPX

/* some systems have nice() which takes *relative* values... [resource.h] */
#define HAVE_SETPRIORITY

/* a sysvism, I think, but ... */
#define HAVE_SYSINFO

/* punted for now: setown / siocspgrp ... see firewall.h */

/* ============= */
/* Include files */
/* ============= */

/* Presence of these can be determined via a script that sniffs them
   out if you aren't sure. */

/* stdlib comes with most modern compilers, but ya never know */
#define HAVE_STDLIB_H

/* not on a DOS box! */
#define HAVE_UNISTD_H

/* stdarg is a weird one */
#define HAVE_STDARG_H

/* dir.h or maybe ndir.h otherwise. */
#define HAVE_DIRENT_H

/* string or strings */
#define HAVE_STRINGS_H

/* if you don't have lastlog.h, what you want might be in login.h */
#define HAVE_LASTLOG_H

/* predefines for _PATH_various */
#define HAVE_PATHS_H

/* assorted others */
#define HAVE_PARAM_H
#define HAVE_SYSMACROS_H	/* in sys/! */
#define HAVE_TTYENT_H		/* securetty et al */

/* ==================== */

/* Still maybe have to do something about the following, if it's even
   worth it.  I just grepped a lot of these out of various code, without
   looking them up yet:
	   
#define HAVE_EINPROGRESS
#define HAVE_F_SETOWN
#define HAVE_SETENV ... now *there's* a hairy one; **environ is portable
#define BIG_ENDIAN/little_endian ... *please* try to avoid this stupidity
#define HAVE_GETUSERSHELL ... you could always pull it out of getpwent()
#define HAVE_SETE[UG]ID ... lib or syscall, it varies on diff platforms
#define HAVE_STRCHR ... should actually be handled by string/strings
#define HAVE_PSTAT
#define HAVE_ST_BLKSIZE ... a stat() thing?
#define HAVE_IP_TOS
#define HAVE_STRFTIME ... screw this, we should just INCLUDE one for lame
   old boxes that don't have it [sunos 3.x, early 4.x?]
#define HAVE_VFPRINTF
#define HAVE_SHADOW_PASSWD  ... in its multitudinous schemes?? ... how
   about sumpin' like #define SHADOW_PASSWD_TYPE ... could get grody.
#define SIG*  ... what a swamp, punt for now; should all be in signal.h
#define HAVE_STRCSPN  ... see larry wall's comment in the fwtk regex code
#define ULTRIX_AUTH  ... bwahaha.
#define HAVE_YP  or NIS or whatever you wanna call it this week
randomness about VARARGS??

There's also the issue about WHERE various .h files live, sys/ or otherwise.
There's a BIG swamp lurking where network code of any sort lives.

*/

/* ======================== */
/* System-specific sections */
/* ======================== */

/* By turning OFF various bits of the above,  you can customize for
   a given platform.  /*

/* DOS boxes, with MSC; you may need to adapt to a different compiler. */
#ifdef MSDOS
#undef HAVE_FLOCK
#undef HAVE_RANDOM
#undef HAVE_LSTAT
#undef HAVE_TERMIOS
#undef UTMPX
#undef HAVE_SYSINFO
#undef HAVE_UNISTD_H
#undef HAVE_DIRENT_H	/* unless you have the k00l little wrapper from L5!! */
#undef HAVE_STRINGS_H
#undef HAVE_LASTLOG_H
#undef HAVE_PATHS_H
#undef HAVE_PARAM_H
#undef HAVE_SYSMACROS_H
#undef HAVE_TTYENT_H
#endif /* MSDOS */

/* buglix 4.x; dunno about 3.x on down.  should be bsd4.2. */
#ifdef ULTRIX
#undef UTMPX
#undef HAVE_PATHS_H
#undef HAVE_SYSMACROS_H
#endif /* buglix */

/* some of this might still be broken on older sunoses */
#ifdef SUNOS
#undef VOID_MALLOC
#undef UTMPX
#undef HAVE_PATHS_H
#endif /* sunos */

/* "contact your vendor for a fix" */
#ifdef SOLARIS
/* has UTMPX */
#undef HAVE_SETPRIORITY
#undef HAVE_STRINGS_H	/* this is genuinely the case, go figure */
#undef HAVE_PATHS_H
#undef HAVE_TTYENT_H
#endif /* SOLARIS */

/* whatever aix variant MIT had at the time */
#ifdef AIX
#undef UTMPX
#undef HAVE_LASTLOG_H
#define HAVE_LOGIN_H	/* "special", in the educational sense */
#endif /* aix */

/* linux, which is trying as desperately as the gnu folks can to be
   POSIXLY_CORRECT.  I think I'm gonna hurl... */
#ifdef LINUX
#undef UTMPX
#undef HAVE_SYSINFO
#undef HAVE_TTYENT_H
#endif /* linux */

/* irix 5.x; may not be correct for earlier ones */
#ifdef IRIX
/* wow, does irix really have everything?! */
#endif /* irix */

/* osf on alphas */
#ifdef OSF
#undef UTMPX
#endif /* osf */

/* they's some FUCKED UP paths in this one! */
#ifdef FREEBSD
#undef UTMPX
#undef HAVE_SYSINFO
#undef HAVE_LASTLOG_H
#undef HAVE_SYSMACROS_H
#endif /* freebsd */

/* From the sidewinder site, of all places; may be unreliable */
#ifdef BSDI
#undef UTMPX
#undef HAVE_LASTLOG_H
#undef HAVE_SYSMACROS_H
#undef HAVE_TTYENT_H
/* and their malloc.h was in sys/ ?! */
#endif /* bsdi */

/* netbsd/44lite, jives with amiga-netbsd from cactus */
#ifdef NETBSD
#undef UTMPX
#undef HAVE_SYSINFO
#undef HAVE_LASTLOG_H
#endif /* netbsd */

/* Make some "generic" assumptions if all else fails */
#ifdef GENERIC
#undef HAVE_FLOCK
#if defined(SYSV) && (SYSV < 4)  /* TW leftover: old SV doesnt have symlinks */
#undef HAVE_LSTAT
#endif /* old SYSV */
#undef HAVE_TERMIOS
#undef UTMPX
#undef HAVE_PATHS_H
#endif /* generic */

/* ================ */
#endif /* GENERIC_H */
