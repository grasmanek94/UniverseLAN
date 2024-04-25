@echo off

cd genie
genie vs2017

if not ["%errorlevel%"]==["0"] (
	pause
	exit /b %errorlevel%
)

start projects/vs2017/Unet.sln
