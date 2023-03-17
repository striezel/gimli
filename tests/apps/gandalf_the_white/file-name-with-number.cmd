:: Script to test executable when file is valid.
::
::  Copyright (C) 2022, 2023  Dirk Stolle
::
::  This program is free software: you can redistribute it and/or modify
::  it under the terms of the GNU Lesser General Public License as published by
::  the Free Software Foundation, either version 3 of the License, or
::  (at your option) any later version.
::
::  This program is distributed in the hope that it will be useful,
::  but WITHOUT ANY WARRANTY; without even the implied warranty of
::  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
::  GNU Lesser General Public License for more details.
::
::  You should have received a copy of the GNU Lesser General Public License
::  along with this program.  If not, see <http://www.gnu.org/licenses/>.

@echo off

:: 1st parameter = executable path
if "%1" EQU "" (
  echo First parameter must be executable file!
  exit /B 1
)

:: 2nd parameter = current directory
if "%2" EQU "" (
  echo Second parameter must be current directory!
  exit /B 1
)

SET EXECUTABLE=%1
"%EXECUTABLE%" "%2"\rgb2.jpeg
if %ERRORLEVEL% NEQ 0 (
  echo Executable did not exit with code 0.
  exit /B 1
)

if NOT EXIST "%2"\rgb2_white_1.jpeg (
  echo File rgb2_white_1.jpeg was not created!
  exit /B 1
)

del /Q "%2"\rgb2_white_1.jpeg

exit /B 0
