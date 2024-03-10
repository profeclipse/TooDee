# determine the project directory based on the location of this script
Set-Variable -Name PROJDIR -Value $PSScriptRoot\..

Push-Location
Set-Location $PROJDIR

if ($args[0] -eq "clean") {
    Remove-Item -Force -Recurse build
}

cmake -S . -B build

Pop-Location

exit 0
