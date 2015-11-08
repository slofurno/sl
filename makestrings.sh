max=500
for i in `seq 2 $max`
do
    cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 1 >> strings.txt
done

cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1