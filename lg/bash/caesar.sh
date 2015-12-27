s="hello bash"
echo $s
test=1234
index=$((test + 1))
echo index: $index
echo ${id}
read name
for((i=0;i<=20;i++))
do 
	echo $((${name:$i:1}))
done
echo $name
