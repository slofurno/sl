max=5000
printf "char *testkeys[] = {\"asdf\"" > input.c
for i in `seq 0 $max`
do
  next=$(tr -dc '[:alnum:]' < /dev/urandom  | dd bs=8 count=1 2>/dev/null)
  #next=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 1)
  printf ",\"$next\"" >> input.c
done
printf "};" >> input.c

#cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1
