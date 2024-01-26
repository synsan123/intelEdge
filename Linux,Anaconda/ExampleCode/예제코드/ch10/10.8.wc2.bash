#!/bin/bash
# 사용법: wc2.bash 
# 명령줄 인수의 개수를 확인하고 wc 명령어를 실행한다. 

if (( $# == 1 ))
then
    wc $1
else
    echo 사용법: $0 파일
fi