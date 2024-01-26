#!/bin/bash
# 사용법: reply.bash 
# 계속 여부를 입력받아 프린트한다. 

echo -n "계속 하겠습니까 ?"
read reply
if  [ $reply == "Y" ] || [ $reply == "y" ]
then
    echo "계속합니다"
else
    echo "중지합니다"
fi