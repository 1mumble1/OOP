@echo off

SET Invert="%~1"
if %Invert%=="" (
	echo Please specify path to program
	exit /B 1
)

SET Output="%TEMP%\output.txt"

REM Если матрица пуста - ошибка чтения из файла
%Invert% Empty.txt > %Output% && goto err
echo Test 1 succeed

REM Если не будет передан входной файл, будет вывзана ошибка
%Invert% > %Output% && goto err
echo Test 2 succeed

REM Если во входном файле будет матрица больше 3x3, будет вывзана ошибка
%Invert% Matrix4x4.txt > %Output% && goto err
echo Test 3 succeed

REM Если во входном файле будет матрица меньше 3x3, будет вывзана ошибка
%Invert% Matrix2x2.txt > %Output% && goto err
echo Test 4 succeed

REM Если во входном файле будут содержаться не числа, будет вывзана ошибка
%Invert% Text.txt > %Output% && goto err
echo Test 5 succeed

REM Если будет передан несуществующий файл, будет вывзана ошибка
%Invert% Missing.txt > %Output% && goto err
echo Test 6 succeed

REM Если во входном файле будет набор чисел, не являющийся матрицей 3x3, будет вывзана ошибка
%Invert% NotMatrix.txt > %Output% && goto err
echo Test 7 succeed

SET DetIsZero="DetIsZero.txt"

REM Если определитель матрицы равен нулю, обратной матрицы не существует
%Invert% MatrixDetZero.txt > %Output% || goto err
fc %Output% %DetIsZero% > nul || goto err
echo Test 8 succeed

REM Матрица обратная единичной и есть сама единичная матрица
%Invert% UnitMatrix.txt > %Output% || goto err
fc %Output% UnitMatrix.txt > nul || goto err
echo Test 9 succeed

REM Матрица с ненулевым определителем имеет обратную матрицу
%Invert% Matrix.txt > %Output% || goto err
fc %Output% InvertedMatrix.txt > nul || goto err
echo Test 10 succeed

REM Тесты прошли успешно
echo All tests succeed
exit /B 0

REM Переход к этой метке в случае ошибки
:err
echo Test Failed
exit /B 1