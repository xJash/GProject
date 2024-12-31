@echo off
::
:: �� ��ġ ������ ������Ʈ�� ��� ������ SDK�� Include������ �����Ѵ�.
:: ���� ����� ���ϵ��� �Ӽ��� �б� �������� �����.
::

:: FIND THE SDK DIRECTORY 
:: Prefer the most local sdk dir, 
:: so order these checks such that local dirs set the variable last.
set SDK_INCLUDE=not_found
if exist ..\..\SDK\NkCore       set SDK_INCLUDE=..\..\SDK\NkCore\Include
if exist ..\..\..\SDK\NkCore    set SDK_INCLUDE=..\..\..\SDK\NkCore\Include
if (%SDK_INCLUDE%)==(not_found) goto :ERROR_NO_SDK

echo (���� �߰��� �����̳� ������ ���ϸ� ����)

:: COPY STANDARD FILES
if exist ..\*Nk*.h      xcopy /D /F /I /R /Y ..\*Nk*.h      %SDK_INCLUDE%
if exist ..\*Nk*.inl    xcopy /D /F /I /R /Y ..\*Nk*.inl    %SDK_INCLUDE%

:: COPY USER SPECIFIED FILES
:==LOOP
if (%~1)==() goto LOOP_END
if exist "%~1" xcopy /D /F /I /R /Y "%~1" %SDK_INCLUDE%
shift
goto LOOP
:==LOOP_END

:: MARK FILES READ ONLY
if exist %SDK_INCLUDE% attrib +R %SDK_INCLUDE%\*

exit /b

:==ERROR_NO_SDK
echo %0: ġ������ ����: SDK ������ ã�� �� �����ϴ�.
exit 1

