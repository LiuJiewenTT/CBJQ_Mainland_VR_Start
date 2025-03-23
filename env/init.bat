@echo off
if not exist "%~dp0bin\" mkdir "%~dp0bin\"

@REM 为mingw32-make.exe创建快捷方式
if exist "%~dp0bin\make.exe" (
    del /F /Q "%~dp0bin\make.exe"
)
call :which "mingw32-make.exe"
if ERRORLEVEL 1 exit /b 1
mklink "%~dp0bin\make.exe" "%which_retv%"

goto :eof


:which
    set "which_retv=%~$PATH:1"
    if not defined which_retv (
        echo ERROR: %1 not found in PATH
        exit /b 1
    )
    exit /b 0
goto :eof
