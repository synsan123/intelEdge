#!/bin/bash
# ����: menu.bash 
# �޴��� ���� �ش� ��ɾ �����Ѵ�. 

echo ��ɾ� �޴�
cat << MENU
	    d       : ��¥ �ð�
	    l       : ���� ���͸� ����
	    w       : ����� ����
	    q       : ����
MENU
stop=0
while (($stop == 0))
do
    echo -n '? '
    read reply
	case $reply in
	    "d") date;;
	    "l") ls;;
	    "w") who;;
	    "q") stop=1;;
	    *) echo �߸��� ����;;
	esac
done