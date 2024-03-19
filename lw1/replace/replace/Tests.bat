@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Замена пустой строки в НЕпустом файле дает тот же самый файл
%MyProgram% input.txt "%TEMP%\output.txt" "" a || goto err
fc input.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 succeed

REM Замена пустой строки в пустом файле дает пустой файл
%MyProgram% empty.txt "%TEMP%\output.txt" "" a || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 succeed

REM Замена НЕпустой строки в пустом файле дает пустой файл
%MyProgram% empty.txt "%TEMP%\output.txt" 12 a || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 succeed

REM Замена строки в несуществующем файле приводит к ошибке
%MyProgram% missing.txt "%TEMP%\output.txt" 12 a && goto err
echo Test 4 succeed

REM Если выходной файл не указан, это приводит к ошибке
%MyProgram% input.txt 12 a && goto err
echo Test 5 succeed

REM Если входной и выходной файлы не указаны, это приводит к ошибке
%MyProgram% 12 a && goto err
echo Test 6 succeed

REM Если строка для замены не указана, это приводит к ошибке
%MyProgram% input.txt "%TEMP%\output.txt" a && goto err
echo Test 7 succeed

REM Если строка для замены и искомая строка не указаны, это приводит к ошибке
%MyProgram% input.txt "%TEMP%\output.txt" && goto err
echo Test 8 succeed

REM Если не переданы аргументы, это приводит к ошибке
%MyProgram% && goto err
echo Test 9 succeed

REM Замена строки на такую же строку вернет тот же файл
%MyProgram% input.txt "%TEMP%\output.txt" 1 1 || goto err
fc input.txt "%TEMP%\output.txt" > nul || goto err
echo Test 10 succeed

REM Замена несуществующей строки вернет тот же файл
%MyProgram% input.txt "%TEMP%\output.txt" 0000 1 || goto err
fc input.txt "%TEMP%\output.txt" > nul || goto err
echo Test 11 succeed

SET Test12Check="check12.txt"

REM Замена строки "ma" на строку "mama" дает файл с удвоенным количеством строки "ma"
%MyProgram% input.txt "%TEMP%\output.txt" ma mama || goto err
fc "%TEMP%\output.txt" %Test12Check% > nul || goto err
echo Test 12 succeed

SET Test13Check="check13.txt"

REM Замена большей строки "1231234" на меньшую строку "9" дает новый файл
%MyProgram% input.txt "%TEMP%\output.txt" 1231234 9 || goto err
fc "%TEMP%\output.txt" %Test13Check% > nul || goto err
echo Test 13 succeed

SET Test14Check="check14.txt"

REM Замена меньшей строки "1" на большую строку "0000" дает новый файл
%MyProgram% input.txt "%TEMP%\output.txt" 1 0000 || goto err
fc "%TEMP%\output.txt" %Test14Check% > nul || goto err
echo Test 14 succeed

SET Test15Check="check15.txt"

REM Замена строки "replace" в большом файле на строку "HELP" дает новый большой файл
%MyProgram% largeInput.txt "%TEMP%\output.txt" "replace" "HELP" || goto err
fc "%TEMP%\output.txt" %Test15Check% > nul || goto err
echo Test 15 succeed

REM Тесты прошли успешно
echo All tests succeed
exit /B 0

REM Переход к этой метке в случае ошибки
:err
echo Test Failed
exit /B 1