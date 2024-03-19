@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

SET Output="%TEMP%\output.txt"
SET NonMagic="OutputNonMagic.txt"
SET Error="OutputError.txt"

REM ����� �������� ����� �������� ������������
%MyProgram% < input.txt > %Output% || goto err
fc %Output% %NonMagic% > nul || goto err
echo Test 1 succeed

REM ������ ���� ������ ������� ������
%MyProgram% < Empty.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 2 succeed

REM ������������� ����� ������� ������
%MyProgram% < InputNegativeNumber.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 3 succeed

REM ���� �� ������� ����� ���������� ���-��, ����� ����, ��� ������� ������
%MyProgram% < InputNonValidValue.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 4 succeed

REM ���� ���������� ������� �����, ��� ������� ������
%MyProgram% < InputRealNumber.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 5 succeed

REM ���� ���������� ������� �����, ��� ������� ������
%MyProgram% < InputRealNumberWithDot.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 6 succeed

REM ���� ���������� �����, ��������� �� ��������� uint64_t, ��� ������� ������
%MyProgram% < InputOutOfRange.txt > %Output% || goto err
fc %Output% %Error% > nul || goto err
echo Test 7 succeed

REM ���� ���������� ����� �� ������� ��������� uint64_t, ��� ������������ �����
%MyProgram% < InputInRange.txt > %Output% || goto err
fc %Output% %NonMagic% > nul || goto err
echo Test 8 succeed

REM ����� ������ �������
echo All tests succeed
exit /B 0

REM ������� � ���� ����� � ������ ������
:err
echo Test Failed
exit /B 1