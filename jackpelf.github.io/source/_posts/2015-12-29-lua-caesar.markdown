---
layout: post
title: "lua-caesar"
date: 2015-12-29 00:02:51 +0800
comments: true
categories: 
---
```lua
#!/usr/bin/lua
print("input plaintext")
text = io.read()
print("ciphertext is:")
i = 1
while(i <= string.len(text))
do
	tmp = (string.byte(text,i))
	if(tmp >= 97 and tmp <= 122)
	then
		tmp = 97 + (tmp - 97 + 5) % 26
		io.write(string.char(tmp))
	elseif(tmp >= 65 and tmp <= 90)
	then
		tmp = 65 + (tmp - 65 + 5) % 26
		io.write(string.char(tmp))
	else
		io.write(string.char(tmp))
	end
	i = i+1
end
print("")
```
