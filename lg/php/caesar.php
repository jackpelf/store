<center>
<form method="post">
plaintext:<input type="text" name="plaintext"><br>
<input type="submit">
</form>
</center>
<?php
echo "ciphertext: \r\n";
$i = 0;
$str = $_POST["plaintext"];
for($i = 0; $i<= strlen($str); $i++)
{
	$tmp = ord($str[$i]);
	if($tmp >= 97 && $tmp <= 122){
		$tmp = 97 + ($tmp - 97 + 5) % 26;
		echo chr($tmp);
	}
	else if($tmp >= 65 && $tmp <= 90){
		$tmp = 65 + ($tmp - 65 + 5) % 26;
		echo chr($tmp);
	}
	
}
?>
