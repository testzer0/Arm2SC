if [[ $# -ne 1 ]]
then
	echo "usage: bash repeat.sh <ntimes>"
else
	awk "{a[NR]=$0}END{for (i=0; i<45; i++){for(k in a){print a[k]}}}" inu.c > outu.c
fi