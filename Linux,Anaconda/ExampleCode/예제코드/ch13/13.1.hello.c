 #include <stdio.h>
 #include <unistd.h>
  
 int main()
 { 
     printf("Hello !\n");
     printf("���� ���μ��� ��ȣ : [%d] \n", getpid());
     printf("�� �θ� ���μ��� ��ȣ : [%d] \n", getppid());
     system("ps");
 }