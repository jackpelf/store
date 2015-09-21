from sys import *
from os import *

system("cd ~/store/ja*/pub* ; rake generate; cp -r ~/store/beifen/* ~/store/jackpelf.github.io/public/blog/2015/09; git add .; git commit -m '9.7'; git push https://github.com/jackpelf/jackpelf.github.io.git master")
