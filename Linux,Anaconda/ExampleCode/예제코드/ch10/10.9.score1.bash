#!/bin/bash
# ����: score1.bash
# ������ ���� ������ �����Ͽ� ����Ʈ�Ѵ�. 
 
echo -n '���� �Է�: '
read score
if (( $score >= 90 ))
then
        echo A 
elif (( $score >= 80 ))  
then
        echo B
elif (( $score >= 70 )) 
then
        echo C
else
        echo ��� ����
fi
