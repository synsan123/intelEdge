#!/bin/bash
# ����: count1.bash [���͸�]
# ��� ���͸� ���� ���ϰ� ������͸� ������ ����Ʈ�Ѵ�.

if [ $# -eq 0 ]
then
    dir="."
else
    dir=$1
fi

echo -n $dir ���� ���ϰ� ������丮 ����:
ls $dir | wc -l
