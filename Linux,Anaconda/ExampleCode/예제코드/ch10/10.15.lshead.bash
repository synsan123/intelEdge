#!/bin/bash
# ����: lshead.bash

lshead() {
  echo "�Լ� ����, �Ű����� $1"
  date
  echo "���͸� $1 ���� ó�� 3�� ���ϸ� ����Ʈ"
  ls -l $1 | head -4
}

echo "�ȳ��ϼ���"
lshead /tmp
