echo off
echo hello bat
set/p text=input plaintext: 
echo %text%
for /l %%i in (1,1,10) do (
set/p text=input plaintext: 
echo %text%
)
pause
