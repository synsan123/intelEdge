#!/bin/bash
# ����: invite.bash 
# ���� �ʴ� ������ ������.
 
invitee=(lee kim choi)
for person in ${invitee[*]}
do
    echo "�ʴ��� �� : ���� ���� �Ļ� ���ӿ� �ʴ��մϴ�." | \
    mail "${person}@gmail.com"
done