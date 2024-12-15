@echo off

REM Define source and destination directories
set SOURCE=standalone\data
set DESTINATION=build\standalone\runtime\data

REM Create the destination directory if it doesn't exist
if not exist "%DESTINATION%" (
    mkdir "%DESTINATION%"
)

REM Copy the contents of the source directory to the destination directory
xcopy "%SOURCE%" "%DESTINATION%" /E /I /Y

REM Confirm completion
echo Data folder has been copied to the runtime directory.
