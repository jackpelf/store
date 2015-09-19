import codecs
import os
import os.path

nux = True
fp = open("d:\what\dirlog.txt","w")

def dir_walk(dirc):
    global nux
    for f in os.listdir(dirc):
        fil = os.path.join(dirc, f)
        if os.path.isdir(fil) and nux:
            #write to file
            fil += '\n'
            fp.write(fil.decode('utf-8'))
            fil = fil[0:len(fil)-1]
            
            nux = False
            dir_walk(fil)
            nux = True
        elif os.path.isfile(fil):
            fil += '\n'
            fp.write(fil.decode('utf-8'))




dir_walk('d:\Blue')
fp.write("---------------------------------\n")
dir_walk('d:\what')
fp.write("---------------------------------\n")
fp.close()
	
	
