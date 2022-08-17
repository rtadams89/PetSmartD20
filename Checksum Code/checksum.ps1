[int]$secret=58
while($true){
[int]$dieValue = Read-Host -Prompt "Die value"
[int]$rollCount = Read-Host -Prompt "Roll #"
[int]$suppliedChecksum = Read-Host -Prompt "Checksum value"
Write-Output "`n"
$expectedChecksum = (((($dieValue+$secret)*10)%($rollCount*3))+$dieValue)


if ( $suppliedChecksum -eq $expectedChecksum )
{
    Write-Output "Legitimate Role"
}
else
{
	Write-Output "FAKE. Expected checksum is $expectedChecksum"
}
Write-Output "`n`n`n"

}