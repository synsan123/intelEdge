#include <stdio.h>
#include <unistd.h>

/* echo 명령어를 실행한다. */
int main( ) 
{    
	printf("시작\n");
    execl("/bin/echo", "echo", "hello", NULL);
	printf("exec 실패!\n"); 
}