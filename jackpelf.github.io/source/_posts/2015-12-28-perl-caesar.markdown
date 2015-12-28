---
layout: post
title: "perl-caesar"
date: 2015-12-28 23:40:39 +0800
comments: true
categories: 
---
```perl
#!/usr/bin/perl
$i = 0;
$s = "abcdg";
print "input plaintext: \n";
$text = <STDIN>;
while($i < length($text))
{
	$tmp = substr($text, $i, 1);
	$tmp = ord($tmp);
	if($tmp >= 97 && $tmp <= 122)
	{
		$tmp = 97 + ($tmp - 97 + 5) % 26;
		print chr($tmp);
	}
	elsif($tmp >= 65 && $tmp <= 90)
	{
		$tmp = 65 + ($tmp - 65 + 5) % 26;
		print chr($tmp);
	}
	else{
		print chr($tmp);
	}
	$i = $i + 1;
}
```
