echo input plaintext
read name
echo $name
l=`expr length $name`
echo $l
i=0
while [ $i -le $l ]
do
	tmp=${name:$i:1}
	echo $tmp
	i=`expr $i + 1`
done
