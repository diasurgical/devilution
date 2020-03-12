@echo off

cd Excel
set PATH=..\..\..\Utils\Bin
call :COMPILE_XL xl_ipre
call :COMPILE_XL xl_isuf
call :COMPILE_XL xl_item
call :COMPILE_XL xl_mfile
call :COMPILE_XL xl_mis
call :COMPILE_XL xl_monst
call :COMPILE_XL xl_obj
call :COMPILE_XL xl_quest
call :COMPILE_XL xl_sfx
call :COMPILE_XL xl_spell
call :COMPILE_XL xl_uitem
call :COMPILE_XL xl_umon
cd ..

cd Text
set PATH=..\..\..\Utils\Bin
call :COMPILE_TXT speech
cd ..

cd Spawn

cd Excel
set PATH=..\..\..\..\Utils\Bin
call :COMPILE_XL xl_sfx
cd ..

cd Text
set PATH=..\..\..\..\Utils\Bin
call :COMPILE_TXT speech
cd ..

cd ..

pause
exit

:COMPILE_XL
MakeXL %1.txt ..\%1.cpp ..\%1.h
goto :eof

:COMPILE_TXT
MakeText %1.txt ..\%1.cpp ..\%1.h
goto :eof
