---
layout: post
title: "ruby-caesar"
date: 2015-12-28 18:03:07 +0800
comments: true
categories: 
---
```ruby
#!/usr/bin/ruby
puts "input plaintext";
plaintext = gets;
i = 0;
puts "ciphertext is :"
while i < plaintext.length do
	ch = plaintext[i].ord;
	if ch >= 97 and ch <= 122 then
		print (97 + (ch - 97 + 5) % 26).chr;
	elsif ch >= 65 and ch <= 90 then
		print (65 + (ch - 65 + 5) % 26).chr;
	else 
		print ch.chr;
	end
	i = i + 1
end
puts ""
```
