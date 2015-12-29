---
layout: post
title: "powershell-cat"
date: 2015-12-29 11:06:48 +0800
comments: true
categories: 
---
```
write hello powershell
$i = 0
while($i -ne 10)
{
	write "input plaintext:" 
	$line = read-host
	write $line
	$i = $i + 1
}
```
