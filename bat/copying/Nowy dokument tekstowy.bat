@echo off
chcp 65001
xcopy /y %CD%\Users\%USERNAME%\Desktop\bat\copying\file.png C:\Users\%USERNAME%\Desktop
start C:\Users\%USERNAME%\Desktop\

echo %USERNAME%
pause