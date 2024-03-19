@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

SET Output="%TEMP%\output.txt"
SET NonMagic="OutputNonMagic.txt"
SET Error="OutputError.txt"

REM Любое валидное число является НЕмагическим
%MyProgram% < input.txt > %Output% || goto err
fc %Output% %NonMagic% > nul || goto err
echo Test 1 succeed

REM Пустой файл должен вывести ошибку
%MyProgram% < Empty.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 2 succeed

REM Отрицательное число выводит ошибку
%MyProgram% < InputNegativeNumber.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 3 succeed

REM Если во входном файле содержится что-то, кроме цифр, это выводит ошибку
%MyProgram% < InputNonValidValue.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 4 succeed

REM Если содержится нецелое число, это выводит ошибку
%MyProgram% < InputRealNumber.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 5 succeed

REM Если содержится нецелое число, это выводит ошибку
%MyProgram% < InputRealNumberWithDot.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 6 succeed

REM Если содержится число, выходящее из диапозона uint64_t, это выводит ошибку
%MyProgram% < InputOutOfRange.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 7 succeed

REM Если содержится число на границе диапозона uint64_t, это немагическое число
%MyProgram% < InputInRange.txt > %Output% || goto err
fc %Output% %NonMagic% > nul || goto err
echo Test 8 succeed

REM Тесты прошли успешно
echo All tests succeed
exit /B 0

REM Переход к этой метке в случае ошибки
:err
echo Test Failed
exit /B 1