#include <stdio.h>
#include <string.h>

char *usr_strcpy(char *dest, const char *src);
int main(int argc, char* argv[])
{
	char str[80];
	char name[80]={0};
//	printf("문자열을 입력하세요! ");
//	puts("이름을 입력하세요! ");
	fputs("이름을 입력하세요! ",stdout);
//	scanf("%s",str);	
//	gets(str);
	fgets(str,sizeof(str),stdin);
//	str[strlen(str)-1] = '\0';
	str[strcspn(str,"\n")] = '\0';

	usr_strcpy(name,"이름:");
//	printf("%s", usr_strcpy(name,"이름:"));
	strcat(name,str);		
//	puts(name);			//이름:홍길동
	fputs(name,stdout);
	return 0;
}

char *usr_strcpy(char *dest, const char *src)
{
    char *tmp = dest;

//    while ((*dest++ = *src++) != '\0')
        /* nothing */;

	while(*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
    *dest = '\0';
    return tmp;
}
