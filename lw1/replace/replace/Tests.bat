@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM ������ ������ ������ � �������� ����� ���� ��� �� ����� ����
%MyProgram% input.txt "%TEMP%\output.txt" "" a || goto err
fc input.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 succeed

REM ������ ������ ������ � ������ ����� ���� ������ ����
%MyProgram% empty.txt "%TEMP%\output.txt" "" a || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 succeed

REM ������ �������� ������ � ������ ����� ���� ������ ����
%MyProgram% empty.txt "%TEMP%\output.txt" 12 a || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 succeed

REM ������ ������ � �������������� ����� �������� � ������
%MyProgram% missing.txt "%TEMP%\output.txt" 12 a && goto err
echo Test 4 succeed

REM ���� �������� ���� �� ������, ��� �������� � ������
%MyProgram% input.txt 12 a && goto err
echo Test 5 succeed

REM ���� ������� � �������� ����� �� �������, ��� �������� � ������
%MyProgram% 12 a && goto err
echo Test 6 succeed

REM ���� ������ ��� ������ �� �������, ��� �������� � ������
%MyProgram% input.txt "%TEMP%\output.txt" a && goto err
echo Test 7 succeed

REM ���� ������ ��� ������ � ������� ������ �� �������, ��� �������� � ������
%MyProgram% input.txt "%TEMP%\output.txt" && goto err
echo Test 8 succeed

REM ���� �� �������� ���������, ��� �������� � ������
%MyProgram% && goto err
echo Test 9 succeed

REM ������ ������ �� ����� �� ������ ������ ��� �� ����
%MyProgram% input.txt "%TEMP%\output.txt" 1 1 || goto err
fc input.txt "%TEMP%\output.txt" > nul || goto err
echo Test 10 succeed

REM ������ �������������� ������ ������ ��� �� ����
%MyProgram% input.txt "%TEMP%\output.txt" 0000 1 || goto err
fc input.txt "%TEMP%\output.txt" > nul || goto err
echo Test 11 succeed

SET Test12Check="check12.txt"

REM ������ ������ "ma" �� ������ "mama" ���� ���� � ��������� ����������� ������ "ma"
%MyProgram% input.txt "%TEMP%\output.txt" ma mama || goto err
fc "%TEMP%\output.txt" %Test12Check% > nul || goto err
echo Test 12 succeed

SET Test13Check="check13.txt"

REM ������ ������� ������ "1231234" �� ������� ������ "9" ���� ����� ����
%MyProgram% input.txt "%TEMP%\output.txt" 1231234 9 || goto err
fc "%TEMP%\output.txt" %Test13Check% > nul || goto err
echo Test 13 succeed

SET Test14Check="check14.txt"

REM ������ ������� ������ "1" �� ������� ������ "0000" ���� ����� ����
%MyProgram% input.txt "%TEMP%\output.txt" 1 0000 || goto err
fc "%TEMP%\output.txt" %Test14Check% > nul || goto err
echo Test 14 succeed

SET Test15Check="check15.txt"

REM ������ ������ "replace" � ������� ����� �� ������ "HELP" ���� ����� ������� ����
%MyProgram% largeInput.txt "%TEMP%\output.txt" "replace" "HELP" || goto err
fc "%TEMP%\output.txt" %Test15Check% > nul || goto err
echo Test 15 succeed

REM ����� ������ �������
echo All tests succeed
exit /B 0

REM ������� � ���� ����� � ������ ������
:err
echo Test Failed
exit /B 1