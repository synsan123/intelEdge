#include <stdio.h>
#include <unistd.h>

/* echo ��ɾ �����Ѵ�. */
int main( ) 
{    
	printf("����\n");
    execl("/bin/echo", "echo", "hello", NULL);
	printf("exec ����!\n"); 
}