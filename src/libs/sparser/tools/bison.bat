@REM Run bison under Windows.  This script is needed so that bison can
@REM find m4, even if neither program is present in PATH.

echo Windows Batch BISON call

@set bison=%1
set BISON_PKGDATADIR=%2
set M4=%3
@set output=%4
@set input=%5

%bison% -d --verbose -o %output% %input%
