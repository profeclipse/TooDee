param (
    $target = 'sandbox'
)

# determine project directory based on the location of this script
Set-Variable -Name PROJDIR -Value $PSScriptRoot\..

Push-Location
Set-Location $PROJDIR
cmake --build build --target $target
Pop-Location
