REM build script for engine
@ECHO off
SetLocal EnableDelayedExpansion

REM Get's list of all C files
SET c_filenames= 
FOR /R %%f in (*.cpp) do (
	SET c_filenames=!c_filenames! %%f
)

SET assembly=mclone
SET compiler_flags=-Wvarargs -Wall -Werror
SET include_flags=-Isource -Ithird_party/Include
SET linker_flags=-luser32 -lgdi32 -lshell32 -lopengl32 -lmsvcrt -lglfw3 -Lthird_party/Libs
SET defines=-D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%%..."
clang++ %c_filenames% %compiler_flags% -o ./bin/%assembly%.exe %defines% %include_flags% %linker_flags%
