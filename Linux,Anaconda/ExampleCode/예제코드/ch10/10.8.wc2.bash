#!/bin/bash
# ����: wc2.bash 
# ����� �μ��� ������ Ȯ���ϰ� wc ��ɾ �����Ѵ�. 

if (( $# == 1 ))
then
    wc $1
else
    echo ����: $0 ����
fi