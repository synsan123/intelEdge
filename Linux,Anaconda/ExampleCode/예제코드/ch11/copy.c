#include <stdio.h>
#include "copy.h"

/*  from�� to�� ����; to�� ����� ũ�ٰ� ����*/ */
void copy(char from[], char to[])
{
   int i;

   i = 0;
   while ((to[i] = from[i]) != '\0')
       ++i;
} 