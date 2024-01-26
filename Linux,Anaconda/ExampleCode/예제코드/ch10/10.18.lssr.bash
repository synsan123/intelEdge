#!/bin/bash
# 사용법 lssr.bash [디렉터리]
# 대상 디렉터리와 모든 하위 디렉터리 내에 있는 파일들의 크기를 리스트한다. 

if [ $# -eq 0 ]
then
   dir="."
else
   dir=$1
fi

if [ ! -d $dir ]
then
   echo $0\: $dir 디렉터리 아님
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

