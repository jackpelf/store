<?php
$con = mysql_connect("localhost", "root", "11223344");
if (!$con)
	{
		die("could not connect:".mysql_error());
	}
mysql_select_db("userpw", $con);
$username = $_POST['username'];
$passwd = $_POST['passwd'];
$result = mysql_query("select * from userpw where username='$username'");
if(! $result)
{
	echo 'error'.mysql_error();
}
else
{
	if($passwd == mysql_fetch_array($result)['passwd'])
		echo 'success';
}

?>


<html>
<title>login in</title>
<body>
<form method="post"/>
username: <input type="text" name="username"/><br/>
passwd: <input type="text" name="passwd"/><br/>
<input type="submit" name="button" value="login">

</body>
</html>
