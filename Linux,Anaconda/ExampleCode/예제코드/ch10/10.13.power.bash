#!/bin/bash
# ����: power.bash 
# 2�� 1�º��� 10�±��� ����Ʈ�Ѵ�. 

let i=2
let j=1
while (( $j <= 10 ))
do
    echo '2 ^' $j = $i
    let i*=2
    let j++
done
