#!/bin/bash
# ����: reply.bash 
# ��� ���θ� �Է¹޾� ����Ʈ�Ѵ�. 

echo -n "��� �ϰڽ��ϱ� ?"
read reply
if  [ $reply == "Y" ] || [ $reply == "y" ]
then
    echo "����մϴ�"
else
    echo "�����մϴ�"
fi