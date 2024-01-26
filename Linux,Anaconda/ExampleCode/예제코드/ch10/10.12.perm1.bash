#!/bin/bash
# ����: perm1.bash ����*
# ������ �����Ѱ� �̸��� ����Ʈ�Ѵ�. 

if [ $# -eq 0 ]
then
    echo ����: $0 ����*
	exit 1
fi

echo " ������      ����"
for file in $*
do
    if [ -f $file ]
	then
	    fileinfo=`ls -l $file`
	    perm=`echo $fileinfo | cut -d' ' -f1`
	    echo "$perm   $file"
	fi
done