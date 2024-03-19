@echo off

SET Crypt="%~1"
if %Crypt%=="" (
	echo Please specify path to program
	exit /B 1
)

SET Output="%TEMP%\output.txt"
SET Output1="%TEMP%\output1.txt"
SET Output2="%TEMP%\output2.txt"

REM ����������� ������� ����� ���� ������ ����
%Crypt% crypt Empty.txt %Output% 100 || goto err
fc %Output% Empty.txt > nul || goto err
echo Test 1 succeed

REM ������������� ������� ����� ���� ������ ����
%Crypt% decrypt Empty.txt %Output% 100 || goto err
fc %Output% Empty.txt > nul || goto err
echo Test 2 succeed

REM ������ ���������� ��� ��������� �����������, ���� ������
%Crypt% input.txt %Output% 100 && goto err
echo Test 3 succeed

REM ������ ���������� ��� ��������� �����, ���� ������
%Crypt% crypt input.txt 100 && goto err
echo Test 4 succeed

REM ������ ���������� ��� ����� ���������, ���� ������
%Crypt% crypt input.txt %Output% && goto err
echo Test 5 succeed

REM ���� �������� ����� �� ����������, ��� ���� ������
%Crypt% crypt Missing.txt %Output% 100 && goto err
echo Test 6 succeed

REM ���� ������� ������������ ����� �����������, ��� ���� ������
%Crypt% code input.txt %Output% 100 && goto err
echo Test 7 succeed

REM ���� ������� ������������ ����, ��� ���� ������
%Crypt% crypt input.txt %Output% CODE && goto err
echo Test 8 succeed

REM ���� ������� ���� ������ 0, ��� ���� ������
%Crypt% crypt input.txt %Output% -1 && goto err
echo Test 9 succeed

REM ���� ������� ���� ������ 255, ��� ���� ������
%Crypt% crypt input.txt %Output% 2555 && goto err
echo Test 10 succeed

REM ��� ����������� ����� � ������������� ��������� ����� � ��� �� ������ 255, ����� ��� �� ����� ����
%Crypt% crypt input.txt %Output1% 255 || goto err
%Crypt% decrypt %Output1% %Output2% 255 || goto err
fc input.txt %Output2% > nul || goto err
echo Test 11 succeed

REM ��� ������������� ����� � ����������� ��������� ����� � ��� �� ������ 0, ����� ��� �� ����� ����
%Crypt% crypt input.txt %Output1% 0 || goto err
%Crypt% decrypt %Output1% %Output2% 0 || goto err
fc input.txt %Output2% > nul || goto err
echo Test 12 succeed

REM ��� ����������� ����� � ������������� ��������� ����� � ��� �� ������ 123, ����� ��� �� ����� ����
%Crypt% crypt input.txt %Output1% 123 || goto err
%Crypt% decrypt %Output1% %Output2% 123 || goto err
fc input.txt %Output2% > nul || goto err
echo Test 13 succeed

REM ����� ������ �������
echo All tests succeed
exit /B 0

REM ������� � ���� ����� � ������ ������
:err
echo Test Failed
exit /B 1