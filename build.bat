@echo off

SETLOCAL

call ".\shell.bat"

set CURRENT_DIR=%~dp0

REM cl flags

set CLFLAGS=/W4 /Zi /nologo /MD /MP4 /WX /EHsc
set CLFLAGS=%CLFLAGS% /wd4005 /wd4305 /wd4267
set CLFLAGS=%CLFLAGS% /I%CURRENT_DIR%\libs /I%CURRENT_DIR%\libs\glfw\include /I%CURRENT_DIR%\libs\glm

set LINKFLAGS=glfw3.lib opengl32.lib shell32.lib gdi32.lib user32.lib kernel32.lib /link
set LINKFLAGS=%LINKFLAGS% /LIBPATH:%CURRENT_DIR%\libs\glfw\lib-vc2022

set CFILES=

REM Create build directory if it doesnt exist already

REM IF NOT EXIST ".\build\" mkdir build

REM Get all .cpp files from code dir as well from GLAD source

REM pushd ".\code"
REM for /R %%c in (*.cpp) do call set CFILES=%%c %%CFILES%%
REM popd

REM pushd ".\libs\glad"
REM for /R %%c in (*.c) do call set CFILES=%%c %%CFILES%%
REM popd

REM Compile

REM pushd ".\build\"
REM cl %CLFLAGS% %CFILES% %LINKFLAGS%
REM popd

ENDLOCAL
