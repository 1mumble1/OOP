@echo off

SET Invert="%~1"
if %Invert%=="" (
	echo Please specify path to program
	exit /B 1
)

SET Output="%TEMP%\output.txt"

REM ���� ������� ����� - ������ ������ �� �����
%Invert% Empty.txt > %Output% && goto err
echo Test 1 succeed

REM ���� �� ����� ������� ������� ����, ����� ������� ������
%Invert% > %Output% && goto err
echo Test 2 succeed

REM ���� �� ������� ����� ����� ������� ������ 3x3, ����� ������� ������
%Invert% Matrix4x4.txt > %Output% && goto err
echo Test 3 succeed

REM ���� �� ������� ����� ����� ������� ������ 3x3, ����� ������� ������
%Invert% Matrix2x2.txt > %Output% && goto err
echo Test 4 succeed

REM ���� �� ������� ����� ����� ����������� �� �����, ����� ������� ������
%Invert% Text.txt > %Output% && goto err
echo Test 5 succeed

REM ���� ����� ������� �������������� ����, ����� ������� ������
%Invert% Missing.txt > %Output% && goto err
echo Test 6 succeed

REM ���� �� ������� ����� ����� ����� �����, �� ���������� �������� 3x3, ����� ������� ������
%Invert% NotMatrix.txt > %Output% && goto err
echo Test 7 succeed

SET DetIsZero="DetIsZero.txt"

REM ���� ������������ ������� ����� ����, �������� ������� �� ����������
%Invert% MatrixDetZero.txt > %Output% || goto err
fc %Output% %DetIsZero% > nul || goto err
echo Test 8 succeed

REM ������� �������� ��������� � ���� ���� ��������� �������
%Invert% UnitMatrix.txt > %Output% || goto err
fc %Output% UnitMatrix.txt > nul || goto err
echo Test 9 succeed

REM ������� � ��������� ������������� ����� �������� �������
%Invert% Matrix.txt > %Output% || goto err
fc %Output% InvertedMatrix.txt > nul || goto err
echo Test 10 succeed

REM ����� ������ �������
echo All tests succeed
exit /B 0

REM ������� � ���� ����� � ������ ������
:err
echo Test Failed
exit /B 1