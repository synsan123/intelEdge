#include <stdlib.h>
#include <stdio.h>

/* �θ� ���μ����� �ڽ� ���μ����� �����ϰ� ���� �ٸ� �޽����� ����Ʈ�Ѵ�. */
int main() 
{
   int pid;

   pid = fork();
   if(pid ==0){  /* �ڽ� ���μ��� */
      printf("[Child] : Hello, world pid=%d\n",getpid());
   }
   else {        /* �θ� ���μ��� */
      printf("[Parent] : Hello, world pid=%d\n",getpid());
   }
}
