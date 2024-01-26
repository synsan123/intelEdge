#!/bin/bash
# ���� lssr.bash [���͸�]
# ��� ���͸��� ��� ���� ���͸� ���� �ִ� ���ϵ��� ũ�⸦ ����Ʈ�Ѵ�. 

if [ $# -eq 0 ]
then
   dir="."
else
   dir=$1
fi

if [ ! -d $dir ]
then
   echo $0\: $dir ���͸� �ƴ�
   exit 1
fi

cd $dir
echo -e "\n $dir :"
ls -s

for x in *
do
   if [ -d $x ]
   then
     /home/chang/bash/lssr.bash $x
   fi
done

