#!/bin/bash
# ����: wc1.bash ����
# ����� �μ� ������ Ȯ���ϰ� wc ��ɾ �����Ѵ�. 

if [ $# -eq 1 ]
then
    wc $1
else
    echo ����: $0 ����
fi