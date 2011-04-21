@REM	Build script to compile Netcat on WIN32 using MinGW
@REM
@REM	Rodney Beede	(http://www.rodneybeede.com)
@REM
@REM	2009-09-02
@REM
@REM	Tested with gcc 3.4.5 and MinGW version 5.1.4
@REM
@REM	[[ diegocr ]]
@REM
@REM	2010-12-14
@REM
@REM	Tested with gcc 4.5.0 and MinGW version 3.1.8(?)
@REM	Added more compiler options and strip usage
@echo off

SET PROGRAM=nc.exe
SET PCOPY=COPY /Y %PROGRAM% c:\windows\system32

SET COMPILER=c:\MinGW\bin\gcc.exe
SET STRIP=c:\MinGW\bin\strip.exe
SET LIB_DIR=c:\MinGW\lib

@REM	not needed? SET CFLAGS=-c -DWIN32 -DNDEBUG -D_CONSOLE -DTELNET
SET XFLAGS=-O3 -march=i686
SET CFLAGS=-c %XFLAGS% -DTELNET
SET LFLAGS=%XFLAGS%

del *.o
del nc.exe

"%COMPILER%" %CFLAGS% getopt.c

"%COMPILER%" %CFLAGS% doexec.c

"%COMPILER%" %CFLAGS% netcat.c

@REM Note that the -l libraries MUST come at the very end or linking will fail
"%COMPILER%" getopt.o doexec.o netcat.o -o %PROGRAM% %LFLAGS% -Wl,-L"%LIB_DIR%",-lkernel32,-luser32,-lwinmm,-lws2_32
"%STRIP%" -s %PROGRAM%
%PCOPY%

echo Operation Completed
