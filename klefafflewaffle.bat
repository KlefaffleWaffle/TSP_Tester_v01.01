@echo off
set /a count=1

call :getCurrentDate
goto checkPathsExist


:checkPathsExist (
    if exist "D:\TSP Tests" (
        echo.
    ) else (
        md "D:\TSP Tests"
    )

    if exist "D:\TSP Tests\%year%\%month%\%day%" (
        echo.
    ) else (
        md "D:\TSP Tests\%year%\%month%\%day%"
    )

    goto checkPathsExistLoop
)


:checkPathsExistLoop (
    if exist "D:\TSP Tests\%year%\%month%\%day%\%count%" (
        echo Folder %count% Exists.
        
        set /a count+=1
        goto checkPathsExistLoop

    ) else (
        md "D:\TSP Tests\%year%\%month%\%day%\%count%"
        cd "D:\TSP Tests\%year%\%month%\%day%\%count%"

        echo. > "D:\TSP Tests\%year%\%month%\%day%\%count%\input.txt"
        echo. > "D:\TSP Tests\%year%\%month%\%day%\%count%\output.txt"

        exit
    )
)


:getCurrentDate (
    for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
    set & set "year=%dt:~0,4%" & set "month=%dt:~4,2%" & set "day=%dt:~6,2%"

    exit /b
)