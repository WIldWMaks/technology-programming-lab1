@echo off
chcp 65001 >nul
cd /d "%~dp0"
where g++ >nul 2>nul
if errorlevel 1 set "PATH=C:\msys64\ucrt64\bin;%PATH%"
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 -static -finput-charset=UTF-8 -fexec-charset=UTF-8 Base.cpp Input.cpp Submarine.cpp Sailboat.cpp Motorboat.cpp main.cpp -o ships.exe
if errorlevel 1 (pause & exit /b 1)
echo Сборка завершена. Запустите ships.exe.
pause
