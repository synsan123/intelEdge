#!/bin/bash
# ����: score2.bash
# ������ ���� ������ �����Ͽ� ����Ʈ�Ѵ�. 

echo -n '���� �Է�: '
read score 
let grade=$score/10
case $grade in
    "10" | "9") echo A;;
    "8") echo B;;
    "7") echo C;;
    *) echo ��� ����;;
esac
