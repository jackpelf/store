<input type="text" name="plaintxt" value = "input plaintext"/>
<script type="text/javascript">
function func()
{
	var str=document.getElementsByName("plaintxt")[0].value;
	var i=0;
	document.write("<br/>ciphertext is <br/>");
	while(i != str.length)
	{
		var tmp = str[i].charCodeAt();
		if (tmp >= 97 && tmp <= 122){
			var ch = String.fromCharCode(97 + (tmp - 97 + 5) % 26);
			document.write(ch);
		}
		else if (tmp >= 65 && tmp <= 90){
			var ch = String.fromCharCode(65 + (tmp - 65 + 5) % 26);
			document.write(ch);
		}
		else 
			document.write(String.fromCharCode(tmp));
		i = i+1;
	}
}
</script>
<button onclick = "func()">encrypt</button>
