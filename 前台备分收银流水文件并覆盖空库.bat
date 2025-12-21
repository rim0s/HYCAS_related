::XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
::		                       _              
::		 ___  ___  _ __   __ _| |_ __ _  ___  
::		/ __|/ _ \| '_ \ / _` | __/ _` |/ _ \ 
::		\__ \ (_) | | | | (_| | || (_| | (_) |
::		|___/\___/|_| |_|\__, |\__\__,_|\___/ 
::		                 |___/                
::			POWERED BY     
::			PHONE 	NO.  	
::			QQ 	NO.  
::			WETCHAT NO.  		
:: 			Func:resolve HYAPP error when reboot sys after loss the power
::			last update:23:25 2019/7/9
::XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 
:GETINFO
::====================get date============================================== 
@set "Ymd=%date:~,4%%date:~5,2%%date:~8,2%"
@if "%TIME:~0,1%"==" " (set NewTime=0%TIME:~1,7%) else (set NewTime=%TIME:~0,8%)
@set Ymdt=%DATE:~0,4%%DATE:~5,2%%DATE:~8,2%%NewTime::=%
@echo 	%Ymdt%
::====================get date  end========================================= 

::====================XRJ batch start========================================
REM  Collected from HYAPP version131 update-batch-APP from XRJ
::=====================================================================
if /i %PROCESSOR_IDENTIFIER:~0,3%==x86 (
    for /f "tokens=1,2,* " %%i in ('REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\HYCAS" ^| findstr /i "PATH"') do set "HYCASPath=%%k"
) else (
    for /f "tokens=1,2,* " %%i in ('REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\HYCAS" ^| findstr /i "PATH"') do set "HYCASPath=%%k"
)
@echo off
set attach1="sp_attach_db 'hypos', '
set attach2=\posdb\hypos_Data.MDF','
set attach3=\posdb\hypos_log.LDF'"
set "osqlstr=%attach1%%HYCASPath%%attach2%%HYCASPath%%attach3%"
echo osqlstr == %osqlstr%  >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
echo osqlstr == %osqlstr%
::====================XRJ batch end========================================

:GetSystemVersion
@echo ================Getting System Version================================
@echo off
cls

ver | find "4.0." > NUL &&  goto unsupport  
ver | find "4.10." > NUL &&  goto unsupport 
ver | find "4.90." > NUL &&  goto unsupport  
ver | find "3.51." > NUL &&  goto unsupport  
ver | find "5.0." > NUL &&  goto unsupport  
ver | find "5.1." > NUL &&  goto Legency  
ver | find "5.2." > NUL &&  goto unsupport   
ver | find "6.0." > NUL &&  goto unsupport  
ver | find "6.1." > NUL &&  goto GETUAC 
ver | find "6.2." > NUL &&  goto GETUAC  
ver | find "6.3." > NUL && goto GETUAC
ver | find "10.0." > NUL && goto GETUAC

:unsupport
@echo current system version unsupport
@goto debug

:GETUAC
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit

echo XXX
goto CleanUpTheScene

:Legency
::do something here
goto CleanUpTheScene

@echo                                         
@echo                                         
@echo                                         
@echo                                         
@echo                                         
@echo                                         
@ver  
@echo               Error ...  Please Contect 
@echo                   wechat  rim0xs
@echo            ---------------------------------

:CleanUpTheScene
@for %%a in (
_isdel.exe
adv_pos.exe
advertisement.exe
autotask.exe
basepay.exe
basket.exe
Calibrat.exe
CLIMNGR.EXE
CLISUPER.EXE
daemon.exe
dataclear.exe
datatr~1.exe
datatrans.exe
dbeng50.exe
dpsdeal.exe
fee_insteadpay.exe
filecopy.exe
filediff.exe
FINANCE.EXE
flowdeal.exe
flowerr.exe
goodscode.exe
goodsprice.exe
hy_bill_send_out.exe
hy_bill_updown.exe
hydtp.exe
hyservice.exe
HYSET.EXE
hystart.exe
hyupgrade_client.exe
hyupgrade_myself.exe
inorder.exe
jkl_bill_updown.exe
jkl_data_down.exe
jkl_interface.exe
jkl_pos_check.exe
jkl_sendrp.exe
lableprint.exe
Lcd.exe
MACRO.EXE
Myshutdown.exe
Panel.exe
Panelcn.exe
pos.exe
pos_change.exe
pos_de~1.exe
pos_device.exe
pos_send.exe
Prnset.exe
Prnsetcn.exe
SALEANS.EXE
scm_datatrans.exe
scmitf_bx.exe
send.exe
Setup.exe
setversion.exe
shop.exe
Sm.exe
stock.exe
SUPPLIER.EXE
SYSMNGR.EXE
test_data.exe
Tm.exe
tobacco.exe
tool_shop.exe
tool_shop_modify.exe
userno.exe
userno_card.exe
userno_check.exe
userno_scm.exe
watchdog.exe
Wf11.exe
wms_rf.exe
) do (
   @taskkill /im %%a /f 
)>> c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt


:getlastprint
@echo off
@echo ===last flowlist info=== >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@dir /l %HYCASPath%\posprint.txt >> c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@echo ================ >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@type %HYCASPath%\posprint.txt >> c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@echo ================ >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@echo. >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@echo ===last flowlist info end=== >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
(for /f "delims=" %%a in ('type %HYCASPath%\pos.dll') do (
    echo;%%a|find  "mdloc=">nul&&set MainDefineLocal=%%a
))
@echo %MainDefineLocal%
for /f "tokens=1* delims=*" %%i in ('echo %MainDefineLocal%') do set MainDefineLocal=%%i%%j
@echo %MainDefineLocal% 
@set mdlocal=%MainDefineLocal:mdloc=%
@echo mdlocal is %mdlocal%end
@echo mdlocal is %mdlocal% >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt

if  %mdlocal%==hypos (
     goto BCHYPOS
) else (
     goto BCSYBASE
)


:BCHYPOS
echo mdloc=hypos  startt backing up  >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
osql -S -E -Q "sp_detach_db hypos"
net stop mssqlserver



:BCSYBASE
echo mdloc=md1  startt backing up  of sybase >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@ren "c:\mdcas\posdb" "posdb%Ymdt%backup"
@if exist "c:\posdb%Ymdt%backup\" echo backup Done! >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@mkdir "c:\mdcas\posdb"

if exist "c:\mdcas\posdb" (
    xcopy "c:\mdcas\posdbbak\*"  "c:\mdcas\posdb\"  /Y /F /E /K /R  >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
) else (
    md "c:\mdcas\posdb"
    xcopy "c:\mdcas\posdbbak\*"  "c:\mdcas\posdb\"  /Y /F /E /K /R  >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
)


if %mdlocal%==hypos (
    echo Attaching MSDB of HYPOS >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
    net start mssqlserver
    osql -S -E -Q %osqlstr%    >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
)


:end
@Echo All Done! Please Check!
@Echo All Done! Please Check!  >>c:\mdcas\log\Backup_POSDB_log_%Ymdt%.txt
@start c:\mdcas\pos.exe
cls
echo.
echo.
echo.
echo OK OK OK OK OK OK OK OK OK OK OK OK OK !
pause 
exit





:debug
@echo ===this is debug info ===
REM show something here!

@echo ===debug info End    ===
@pause
@exit
