@GOTO START
#############################################################################
#     		                       _              
#	 	 ___  ___  _ __   __ _| |_ __ _  ___  
#		/ __|/ _ \| '_ \ / _` | __/ _` |/ _ \ 
#		\__ \ (_) | | | | (_| | || (_| | (_) |
#		|___/\___/|_| |_|\__, |\__\__,_|\___/ 
#		                 |___/                
#
#			POWERED BY   SONGTAO  
#			WETCHAT NO.  rim0xs		
# 			Func:install sqlserver auto*  
#			last update:23:12 2019/2/11
#############################################################################




:START
@echo off
setlocal enabledelayedexpansion

REM 调试指针 START
REM ::goto winXreg
REM 调试指针 END

if "%PROCESSOR_ARCHITECTURE%"=="x86"   goto x32
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" goto x64


:x32
set osb=x32
goto show


:x64
set osb=X64
set s2ilx="%~dp0x86\SETUP\SETUPSQL.EXE"
set s2Plx="%~dp0chs_sql2ksp4\x86\setup\setupsql.exe"

ver | find "10.0." > NUL && goto compat_list
ver | find "5.2" > NUL && goto show

reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v !s2ilx! /t REG_SZ /d "WINXPSP3"
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v !s2Plx! /t REG_SZ /d "WINXPSP3"
goto show


:compat_list
::reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v !s2ilx! /t REG_SZ /d "~ WINXPSP3"
::reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v !s2Plx! /t REG_SZ /d "~ WINXPSP3"
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v !s2ilx! /t REG_SZ /d "~ RUNASADMIN WINXPSP3"
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v !s2Plx! /t REG_SZ /d "~ RUNASADMIN WINXPSP3"
goto show

:show
echo %osb%
ver
goto judge


::echo  %~dp0
::echo "%~dp0weili.iss"


:judge
ver | find "5.0." > NUL && goto Legency
ver | find "5.1." > NUL && goto Legency
ver | find "5.2." > NUL && goto Legency
ver | find "6.0." > NUL && goto GETUAC
ver | find "6.1." > NUL && goto GETUAC
ver | find "6.2." > NUL && goto GETUAC
ver | find "6.3." > NUL && goto GETUAC
ver | find "10.0." > NUL && goto GETUAC
@echo 操作系统未受脚本支持
@ver
goto debug


:onlyforwinX
if not exist "%~dp0x86\other\sqlredis_old.exe"  rename  %~dp0x86\other\sqlredis.exe  sqlredis_old.exe
xcopy  %~dp0chs_sql2ksp4\x86\other\sqlredis.exe  %~dp0x86\other\   /Y
xcopy  %~dp0chs_sql2ksp4\x86\system\msvcr71.dll   "C:\Program Files (x86)\Microsoft SQL Server\MSSQL\Binn\" /Y
xcopy  %~dp0chs_sql2ksp4\x86\system\sqlunirl.dll    "C:\Program Files (x86)\Microsoft SQL Server\MSSQL\Binn\" /Y
xcopy  %~dp0chs_sql2ksp4\x86\system\msvcr71.dll   "C:\Program Files (x86)\Microsoft SQL Server\80\Tools\Binn\" /Y
xcopy  %~dp0chs_sql2ksp4\x86\system\sqlunirl.dll    "C:\Program Files (x86)\Microsoft SQL Server\80\Tools\Binn\" /Y
goto Legency

:GETUAC
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit

::reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v "%~dp0x86\setup\setupsql.exe" /t REG_SZ /d "WINXPSP3"
::reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /f /v "%~dp0chs_sql2ksp4\x86\setup\setupsql.exe" /t REG_SZ /d "WINXPSP3"

reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags" /f /v "{186412bc-d2b0-4fa2-805d-4c6f18d8594a}" /t REG_DWORD /d "4"
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags" /f /v "{d6973313-d1ab-487c-85d0-d3af331ea984}" /t REG_DWORD /d "4"
ver | find "10.0." > NUL && goto onlyforwinX


:Legency
if %osb%==X64 goto judge_installed_or_not_X64 
if %osb%==x32 goto judge_installed_or_not_x32



:judge_installed_or_not_X64
reg query "HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Microsoft SQL Server" 2>null 
if %errorlevel%==0 (
echo 已经安装SQL server
goto end
) else (
echo 未安装SQL server,即将开始安装...
goto INSTALLSQL
)
goto debug


:judge_installed_or_not_x32
reg query "HKEY_LOCAL_MACHINE\Software\Microsoft\MSSQLServer\Setup" 2>null 
if %errorlevel%==0 (
echo 已经安装SQL server
goto end
) else (
echo 未安装SQL server,即将开始安装...
goto INSTALLSQL
)
goto debug


::HKEY_LOCAL_MACHINE\Software\Microsoft\MSSQLServer\Setup


:INSTALLSQL
if exist "%PROGRAMFILES(x86)%\Microsoft SQL Server" del "%PROGRAMFILES(x86)%\Microsoft SQL Server" /q /f
if exist "%PROGRAMFILES%\Microsoft SQL Server\80" del "%PROGRAMFILES%\Microsoft SQL Server\80" /q /f
::reg query "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager"  /v  PendingFileRenameOperations
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager"  /v  PendingFileRenameOperations /f 2>NULL
echo 正在安装SQL server 2000 ... 
start "sql2kinfo" %~dp0infobar.bat
start /wait %~dp0x86\setup\setupsql.exe  k=SMS  -m -s  -SMS -f1 %~dp0new.iss
taskkill /FI "WINDOWTITLE eq  sql2kinfo*" /f  2>NULL
ver | find "10.0." > NUL && goto winXsp4


:NOMAL_SP4
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager"  /v  PendingFileRenameOperations /f 2>NULL
echo 正在打 SP4 补丁 ...
start "sql2kpatch" %~dp0infobar2.bat
start /wait %~dp0chs_sql2ksp4\x86\setup\setupsql.exe  k=SMS  -m -s  -SMS -f1 %~dp0SP4.iss
taskkill /FI "WINDOWTITLE eq sql2kpatch*" /f 2>NULL
goto test_pointB
REM 安装已经完成


:winXsp4
echo 正在打SP4补丁....
start "sql2kXpatch" %~dp0infobar_winX.bat
start /wait %~dp0chs_sql2ksp4\x86\setup\setupsql.exe  k=SMS  -m -s  -SMS -f1 %~dp0SP4.iss
taskkill /FI "WINDOWTITLE eq sql2kXpatch*" /f 2>NULL
goto test_pointB
REM 安装已经完成


:test_pointB
net start mssqlserver 

@echo off
netstat -ano|findstr "0.0.0.0:1433" >nul
if "%errorlevel%"=="0" (
  echo Patch成功!
) else (
  echo Patch 安装完成
  echo 测试未成功，如有问题请联系脚本编写人员。!
  net start mssqlserver 
)


:add_firewall_rulls
netsh advfirewall firewall delete rule name="MS SQL SERVER 2000" dir=in protocol=tcp localport=1433
netsh advfirewall firewall add rule name="MS SQL SERVER 2000" dir=in protocol=tcp action=allow localport=1433


:tail
echo ####################################
echo #                                  #
echo # SQL SERVER 2000 安装脚本执行完成 #
echo #                                  #
echo # 联系开发人员 : 请按 Q 键,并回车  #
echo # 退出         : 直接回车          #
echo #                                  #
echo ####################################
echo                                     
set havequestion=
set /p havequestion=
if "%havequestion%"=="Q" start notepad %~dp0README.info.txt
if "%havequestion%"==""  goto end



goto end
=================================================================

:testfun
::goto debug


##################################
:debug
echo this is debug information
pause
exit
##################################


:end
endlocal
REM pause