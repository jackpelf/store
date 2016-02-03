import sys
import subprocess
ans = []
while True:
	for j in range(256):
		if j % 16 == 15:
			print j
		p = subprocess.Popen('./ey_or', stdin = subprocess.PIPE, stdout = subprocess.PIPE)
		for x in ans:
			p.stdin.write(str(x) + '\n')
		p.stdin.write(str(j) + '\n')
		p.stdin.close()
		ret = p.wait()
		if ret != 1:
			ans.append(j)
			print ans
			break
