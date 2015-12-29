write hello powershell
$i = 0
while($i -ne 10)
{
	write "input plaintext:" 
	$line = read-host
	write $line
	$i = $i + 1
}
