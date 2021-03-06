/* Coverage of the N-terminal peptides*/

/*	第一部分：提取数据
	把peptide sequence和protein ID从fasta文件提取出来，存放到structure中。
	把打到的peptide序列和指认的protein ID也提取出来，存放到structure中。
	声明char类型的structure
	文件读取，用文件指针间接访问AA */

/*	第二部分：比对序列
	提取peptide——
	匹配到对应的protein ID——
	提取对应protein序列——
	判断peptide序列第一个是不是M，如果是，则比较peptide与protein的第二个AA，知道连续匹配5个AA——
	如果第一个不是M，则比较peptide第一个AA和protein第二个AA——
	若第二个AAmatch，则依次比较下一个AA，直到连续匹配5个AA
	若第二个AA不match，则比较peptide第一个AA和protein第三个AA——
	若match，则依次比较下一个AA，直到连续匹配5个AA——
	若三个AA都不match，则认为不是N端肽
 */

#include <stdlib.h>
#include <stdio.h>

#define BASE 20371
/*#define LONG 30
#define COUNT 5
#define RESULT_PATH E:
#define FASTA_PATH E:\MCF7.fasta*/

#define ERROR -1

char * get_proteinid(char *p, int n);
char * get_peptideseq(char *p, int n);
char * buff;						//缓冲区指针
char * start_point;
char * peptideseq;
int size;

/* struct peptide {
		char peptide_sequence[];		//把肽段序列存为字符串数组
		char peptide_protein[];			//protein ID也存为字符串数组
	}
	
struct fasta {
		char fasta_sequence[];			//把FASTA中肽段序列存为字符串数组
		char fasta_protein[];			//protein ID也存为字符串数组
}
*/

int main(void)
{
	//FILE * file_target;
	FILE * file_fasta;			//声明fasta文件指针
	size = 0;					//用于计算文件大小，分配动态内存
	static int i;				//counter
	static int pos;				//指认蛋白ID位置
	static int seq_pos;			//指认蛋白AA序列位置
	
	file_fasta = fopen ("MCF7.fasta","rt");	//打开fasta文件
	if (file_fasta == NULL) {
		printf("ERROR:cannot retrieve this file.\n");
	return ERROR;}
	
	fseek(file_fasta, 0L, SEEK_END);
	size = ftell(file_fasta);
	/* 读出文件大小，并存入size中 */
	
	rewind(file_fasta);										//将*file_fasta指针重新指向文件开头
	printf("The size of file_fasta is %d.\n", size);
	buff = (char *)malloc(size-1);									//给fasta文件分配内存
	start_point = (char *)malloc(size-1);
	peptideseq = (char *)malloc(size-1);
	if (buff == NULL || start_point == NULL) return ERROR;
	fread (buff, size-1, 1, file_fasta);								//将*file_fasta指向的内容读入buff缓冲区
	start_point = buff;										//将*start_point指向buff首地址，用于free内存
	peptideseq = buff;
	//printf("%s\n", buff);										//打印fasta文件，用于调试
	
	for (int y = 0; y < 4; y++) {
		for (; *buff;buff++) {										//循环一直进行，直到break
		//printf("%p\n",buff);
		i++;
		if ((*buff == '|') && (*(buff + 7) == '|')) {
			pos = i + 7; 									//static类型变量i自动初始化
			printf("The value of pos is %d\n", pos);
		}

		if ((*buff == 'M') && (*(buff - 1) == '\n')) {						//设置跳出循环条件
			seq_pos = i - 1;
			printf("The value of seq_pos is %d\n", seq_pos);
			break;
		}
	}
	
	char * mm = get_proteinid(peptideseq, pos);
	char * seq = get_peptideseq(peptideseq, seq_pos);
	
	printf("proteinID=\n%s\n", mm);
	printf("SEQ=\n%s\n",seq);

	free(mm);
	free(seq);

	}

	

	buff = start_point;
	
	free(buff);


	
	fclose(file_fasta);
	
	return 0;
}


	/*on going...
	file_target = fopen ("PATH","rt");
	char peptide[COUNT][LONG];
	char database[][];	
	for (int x = 0; x < LONG; i++) {								//外层循环是peptide
		for (int y = 0; y < BASE;j++) {								//内层循环是比对database
			f 
	
		}
	}
	*/

/* 从FASTA文件读取蛋白ID */
char *get_proteinid(char *p, int n) {
	static char * m, * t;
	m = (char *)malloc(n);
	t = (char *)malloc(n);
	if (m == NULL || n == NULL)
		return NULL;
	t = m;
	while(n--) {
		*m++ = *p++;
	}
	*(m) = '\0';
	return t;
}

/* 从FASTA文件读取蛋白序列 */
char *get_peptideseq(char *p, int n) {
	static char * m, * t;
	m = (char *)malloc(30);
	t = (char *)malloc(30);
	if (m == NULL || n == NULL) 
		return NULL;
	t = m;
	p = p + n;

	for (int x = 0;x < 25; x++) {
		*m++ = *p++;
	}
	*(m) = '\0';
	return t;
}









