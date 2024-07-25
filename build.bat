@echo off

for /f "tokens=16" %%i in ('ipconfig ^|find /i "ipv4"') do (
	set ip=%%i
	goto success
)

echo What are you doing? You don't have any IP!!!
pause
exit

:success

echo Get IP successfully!
echo #define IP ^"%ip%^" > .\setting\ip.ini

echo Compiling...

set flag=0

g++ .\main\server.cpp -o .\bin\server.exe -static -lws2_32 -Os -std=c++11 -Wall -Wextra
if %errorlevel% neq 0 (
	echo Failed to compile server
	set flag=1
) else (
	echo Compile server successfully!
)
g++ .\main\client.cpp -o .\bin\client.exe -static -lws2_32 -Os -std=c++11 -Wall -Wextra -mwindows
if %errorlevel% neq 0 (
	echo Failed to compile client
	set flag=1
) else (
	echo Compile client successfully!
)

.\tool\ResourceHacker.exe -open ".\bin\server.exe" -save ".\bin\server.exe" -action addoverwrite -res ".\icon\server.ico" -mask ICONGROUP,MAINICON,0
del .\tool\ResourceHacker.ini