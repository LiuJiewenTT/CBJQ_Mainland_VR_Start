@echo off
if exist "%~dp0bin\" del /F /S /Q "%~dp0bin\" 
call "%~dp0init.bat"
