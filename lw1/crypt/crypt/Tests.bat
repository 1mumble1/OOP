@echo off

SET Crypt="%~1"
if %Crypt%=="" (
	echo Please specify path to program
	exit /B 1
)

SET Output="%TEMP%\output.txt"
SET Output1="%TEMP%\output1.txt"
SET Output2="%TEMP%\output2.txt"

REM Кодирование пустого файла дает пустой файл
%Crypt% crypt Empty.txt %Output% 100 || goto err
fc %Output% Empty.txt > nul || goto err
echo Test 1 succeed

REM Декодирование пустого файла дает пустой файл
%Crypt% decrypt Empty.txt %Output% 100 || goto err
fc %Output% Empty.txt > nul || goto err
echo Test 2 succeed

REM Запуск приложения без параметра кодирования, дает ошибку
%Crypt% input.txt %Output% 100 && goto err
echo Test 3 succeed

REM Запуск приложения без выходного файла, дает ошибку
%Crypt% crypt input.txt 100 && goto err
echo Test 4 succeed

REM Запуск приложения без ключа кодировки, дает ошибку
%Crypt% crypt input.txt %Output% && goto err
echo Test 5 succeed

REM Если входного файла не существует, это дает ошибку
%Crypt% crypt Missing.txt %Output% 100 && goto err
echo Test 6 succeed

REM Если передан некорректный режим кодирования, это дает ошибку
%Crypt% code input.txt %Output% 100 && goto err
echo Test 7 succeed

REM Если передан некорректный ключ, это дает ошибку
%Crypt% crypt input.txt %Output% CODE && goto err
echo Test 8 succeed

REM Если передан ключ меньше 0, это дает ошибку
%Crypt% crypt input.txt %Output% -1 && goto err
echo Test 9 succeed

REM Если передан ключ меньше 255, это дает ошибку
%Crypt% crypt input.txt %Output% 2555 && goto err
echo Test 10 succeed

REM При кодировании файла и декодировании выходного файла с тем же ключом 255, будет тот же самый файл
%Crypt% crypt input.txt %Output1% 255 || goto err
%Crypt% decrypt %Output1% %Output2% 255 || goto err
fc input.txt %Output2% > nul || goto err
echo Test 11 succeed

REM При декодировании файла и кодировании выходного файла с тем же ключом 0, будет тот же самый файл
%Crypt% crypt input.txt %Output1% 0 || goto err
%Crypt% decrypt %Output1% %Output2% 0 || goto err
fc input.txt %Output2% > nul || goto err
echo Test 12 succeed

REM При кодировании файла и декодировании выходного файла с тем же ключом 123, будет тот же самый файл
%Crypt% crypt input.txt %Output1% 123 || goto err
%Crypt% decrypt %Output1% %Output2% 123 || goto err
fc input.txt %Output2% > nul || goto err
echo Test 13 succeed

REM Тесты прошли успешно
echo All tests succeed
exit /B 0

REM Переход к этой метке в случае ошибки
:err
echo Test Failed
exit /B 1