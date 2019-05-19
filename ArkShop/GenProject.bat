@echo off


REM ========================================================
REM configure ark api directory
REM ========================================================
set ARK_API_DIR=""

REM ========================================================
REM configure project name 
REM ========================================================
set ProjectName=ArkShop



set MAIN_DIR=%cd%
mkdir workspace
cd workspace
set WORKSPACE_DIR=%cd%

if not exist %ARK_API_DIR% (

echo #
echo #     no ark api directory configured
echo # 



if not exist %cd%\ARK-Server-API ( 

echo #
echo #    start cloning ark api from git repository
echo #

  git clone https://github.com/Michidu/ARK-Server-API

)
  set ARK_API_DIR=%cd%/ARK-Server-API

echo #
echo #    ark api directory set to %cd%\ARK-Server-API
echo #


)

cmake .. -G "Visual Studio 15 Win64" ^
     -DProjectName=%ProjectName% ^
	 -DPATH_ARK_API=%ARK_API_DIR% 
	 
if errorlevel 1 pause % exit /b
	 
echo #
echo #    solution has been created in
echo #    %WORKSPACE_DIR%
echo #	


echo #
echo #    building the project in directory
echo #    %WORKSPACE_DIR%
echo #
cmake --build . --target ALL_BUILD --config Release 

if errorlevel 1 pause % exit /b
echo # 
echo #    finished! solution has been created in
echo #    %WORKSPACE_DIR%\Release 
echo # 

if not exist %WORKSPACE_DIR%\Release\config.json ( 
copy %MAIN_DIR%\Configs\config.json %WORKSPACE_DIR%\Release 
)

if not exist %WORKSPACE_DIR%\Release\PluginInfo.json ( 
copy %MAIN_DIR%\Configs\PluginInfo.json %WORKSPACE_DIR%\Release 
)

   
explorer  %WORKSPACE_DIR%\Release 
 

Pause 




