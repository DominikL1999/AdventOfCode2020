#Parameters
param(
    [int]$DayNumber,
    [string]$ProblemName
)

#Script
$ProblemFolder = "Day" + [string]$DayNumber + "-" + $ProblemName
New-Item -ItemType Directory -Force -Path $ProblemFolder

Set-Location $ProblemFolder
New-Item -ItemType Directory -Name "input"
New-Item -ItemType File -Name "input/input.txt"
New-Item -ItemType File -Name "input/test-input.txt"

Copy-Item -Path ../templates/template.cpp -Destination main.cpp
Copy-Item -Path ../templates/Compile.ps1 -Destination Compile.ps1
Copy-Item -Path ../templates/Run.ps1 -Destination Run.ps1