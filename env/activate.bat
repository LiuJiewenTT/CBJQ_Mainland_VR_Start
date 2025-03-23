@echo off
setlocal enabledelayedexpansion
set env_name=env
if exist "%~dp0env_name.txt" (
    for /f "usebackq tokens=*" %%i in ("%~dp0env_name.txt") do set env_name=%%i
)
endlocal && set PROMPT=(%env_name%) $P$G

set PATH=%~dp0bin;%PATH%
