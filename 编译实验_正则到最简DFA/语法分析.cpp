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
////�﷨��������
//int TESTparse() {
//	int es = 0;
//	if ((fp = fopen(Scanout, "r")) == NULL) {
//		{
//			printf("\n Can not open % S\n", Scanout); es = 10;
//		}
//		if (es == 0)es = program();
//		printf(" == �﷨������� == \n"); switch (es)
//		{
//		case 0: printf("�﷨�����ɹ�\n"); break;
//		case 10: printf("���ļ� % sʧ��", Scanout); break;
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
//	//<program>��{<declaration_list><statement_list>}int program()
//	{��}
//	��
//
