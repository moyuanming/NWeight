#include "LocalIncludeFile.h"
int FileExists(char *filename)
{	
	return (access(filename, 0) == 0);	
}
/******************************************************************************************************
* 创建指定文件名的文件
******************************************************************************************************/
void CreateMsgFile(char *FilePath,int FileLength)
{	
	FILE *fp;
	char *temp;
	if((fp=fopen(FilePath,"wt+"))==NULL)
	{	
		printf("Cannot open file strike any key exit!");	
		//exit(1);	
	}
	if(FileLength>0)
	{	
		temp =(char*) malloc(FileLength);	
		memset(temp,'0',FileLength);	
		fwrite(temp,FileLength,1,fp);	
		free(temp);	
	}
	fclose(fp);	
}
