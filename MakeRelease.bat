@echo off
setlocal

echo.
echo ============================
echo        Release Build
echo ============================
echo.

cmake -S . -B build
if errorlevel 1 (
    echo.
    echo CMake configuration failed.
    pause
    exit /b 1
)

echo.
echo Building Release...
echo.

cmake --build build --config Release
if errorlevel 1 (
    echo.
    echo Release build failed.
    pause
    exit /b 1
)

echo.
echo ============================
echo       Build Successful!
echo ============================
echo.

pause