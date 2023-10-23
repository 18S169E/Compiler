//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <ctype.h>
//#include<conio.h>
//int TESTparse();
//int program();
//int compound_stat();
//int statement();
//int expression_stat();
//int expression();
//int bool_expr();
//int additive_expr();
//int term();
//int factor();
//int if_stat();
//int while_stat();
//int for_stat();
//int write_stat();
//int read_stat();
//int declaration_stat();
//int declaration_list();
//int statement_list();
//int compound_list();
//char token[20], token1[40]; extern char Scanout[300];
//FILE* fp;
////语法分析程序
//int TESTparse() {
//	int es = 0;
//	if ((fp = fopen(Scanout, "r")) == NULL) {
//		{
//			printf("\n Can not open % S\n", Scanout); es = 10;
//		}
//		if (es == 0)es = program();
//		printf(" == 语法分析结果 == \n"); switch (es)
//		{
//		case 0: printf("语法分析成功\n"); break;
//		case 10: printf("打开文件 % s失败", Scanout); break;
//		case 1: printf("\n"); break;
//		case 2: printf("\n"); break;
//		case 3: printf("\n"); break;
//		case 4: printf("\n"); break;
//		case 5: printf("\n"); break;
//		case 6: printf("\n"); break;
//		case 7: printf("\n"); break;
//		}
//	}
//
//	return(es);
//	//<program>à{<declaration_list><statement_list>}int program()
//	{…}
//	…
//
