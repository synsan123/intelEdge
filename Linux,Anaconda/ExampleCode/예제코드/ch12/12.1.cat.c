#include <stdio.h>

/* �ؽ�Ʈ ���� ������ ǥ����¿� ����Ʈ */
int main(int argc, char *argv[])
{
   FILE *fp;
   int c;

   if (argc < 2) 
      fp = stdin;               // ����� �μ��� ������ ǥ���Է� ��� 
   else	
      fp = fopen(argv[1],"r");	// �б� �������� ���� ����  
	
   c = getc(fp);      		// ���Ϸκ��� ���� �б�
   while (c != EOF) { 		// ���ϳ��� �ƴϸ�
      fputc(c, stdout); 	// ���� ���ڸ� ǥ����¿� ���
      c = fgetc(fp); 		// ���Ϸκ��� ���� �б� 
   }
   fclose(fp); 
   return 0;
}
