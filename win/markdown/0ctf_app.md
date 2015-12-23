
打印文件222中和文件111中相同的行

    grep -Ff 111 222
    
operator模块提供的itemgetter函数用于获取对象的哪些维的数据
Python内置的排序函数sorted可以对list或者iterator进行排序

    sorted(iterable[, cmp[, key[, reverse]]])
    key为函数，指定取待排序元素的哪一项进行排序
    
dict.items()方法返回字典的(键,值)元组对的列表


###pwntool disasm
disasm(data, arch)

 pin.sh -injection child -t sandbox.so -- ./login

关闭aslr调试

login地址是aslr的，pin的地址是aslr的，本地是静态的
本地，有一个固定rwx地址，改写shellcode，和exit在pin中的指针
远程，泄漏pin的地址，并改写

