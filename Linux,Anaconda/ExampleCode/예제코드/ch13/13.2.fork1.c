#include <stdio.h>
#include <unistd.h>

/* �ڽ� ���μ����� �����Ѵ�. */
int main()
{ 
    int pid;
    printf("[%d] ���μ��� ���� \n", getpid());
    pid = fork();  
    printf("[%d] ���μ��� : ���ϰ�  %d\n", getpid(), pid);
}
