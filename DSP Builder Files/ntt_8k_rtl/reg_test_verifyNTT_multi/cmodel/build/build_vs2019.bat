@ECHO OFF
SET CMAKE_PATH=../
IF NOT "%~1"=="" (
    SET CMAKE_PATH=%~1
)
cmake -G "Visual Studio 16 2019" %CMAKE_PATH%
if %ERRORLEVEL% EQU 0 cmake --build . --parallel 16 --config RelWithDebInfo 2>&1 && echo Build status: %errorlevel%
