#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DIARY_LENGTH 1000

void print_opt(void);
//Ķ����
void printMonth(int year, int month);
void printMonthTitle(int year, int month);
void printMonthName(int month);
void printMonthBody(int year, int month);
int getStartDay(int year, int month);
int getTotalNumberOfDays(int year, int month);
int getNumberOfDaysInMonth(int year, int month);
int isLeapYear(int year);
//�ϱ�
void print_title(void);
int get_date_file_name(void);
void scan_description(char[]);
void put_diary(int, char[]);
int get_diary(int, char[]);
//
void print_account_book(void);


int lastday[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


int main(void)
{
	time_t now;
	struct tm* tp;
	int option, menu, date, year, month, day;

	//���۽� ������ ������� ����Ѵ�
	now = time(NULL);
	tp = localtime(&now);
	printf("���ó�¥ : %d/%d/%d\n", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);

	char description[MAX_DIARY_LENGTH] = "";
	//����â ���
	print_opt();
	
	scanf("%d", &option);


	switch (option)
	{
	case 1:
		//Ķ����
		// �⵵ �Է�
		printf("�⵵ : ");
		scanf("%d", &year);
		// �� �Է�
		printf("�� : ");
		scanf("%d", &month);
		printMonth(year, month);
			
		break;
	case 2:
		//�ϱ�
		while (1)
		{
			description[0] = '\0';
			print_title();
			scanf("%d", &menu);
			system("cls");
			switch (menu)
			{
			case 1:
				//�ϱ� ���� ����
				scan_description(description);
				date = get_date_file_name();
				put_diary(date, description);
				system("cls");
				printf("\n\n~~![%d.txt] �ϱ� �ۼ� �Ϸ�\n\n", date);
				break;
			case 2:
				//�ϱ� ���� ����
				printf("Ȯ���ϰ� ���� ��¥�� �Է����ּ��� (YYYYMMDD): ");
				scanf("%d", &date);
				system("cls");

				if (get_diary(date, description))
					printf("\n\n%d.txt�� ����:\n%s\n\n(�׸� ������ �ƹ� Ű�� ��������.)\n", date, description);
				else
					printf("�� ������ �ϱ⸦ �ۼ����� �ʾҽ��ϴ�.\n(�ƹ� Ű�� ���� ����ȭ������ ���ư���.)\n");

				getchar();
				getchar();
				system("cls");
				break;
			case 3:
				//���α׷� ����
				return 0;
			default:
				//�߸��� ��ȣ �Է�
				system("cls");
				printf("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
				break;
			}
		}
		break;
	case 3:
		//�����
		FILE * fp;
		int earnings = 0;  //����
		int expenditure = 0;  //����
		int Deposit = 0;  //�ܾ�
		int choice = 0;  //���û���
		int day;

		fp = fopen("list.txt", "w"); //���۰� ���ÿ� list.txt ������ �����ȴ�.
		print_account_book();
		scanf("%d", &Deposit);
		fprintf(fp, "\n ���� �ڻ� : %d ��\n", Deposit);  //���� �ڻ��� list.txt ���Ͽ� �Է��Ѵ�.

		while (1)
		{
			if (Deposit == 0)  break;	//�Է¹��� �ڻ��� 0�� �Է½� ����.
			
			printf("\n��� ���� (1.���� 2.���� 3.�ܾ� ��ȸ 4.����) : ");
			scanf("%d", &choice);

			if (choice == 1)  //������ �����ҽ�
			{
				printf("���� �ݾ� : ");
				scanf("%d", &earnings);
				Deposit = Deposit + earnings;

				fprintf(fp, "\n ���� �ݾ� : %d ��\n", Deposit);
				printf("\n%d\n", Deposit);
			}

			else if (choice == 2) // ������ ���ý�
			{
				printf("��¥(YYMMDD) : ");
				scanf("%d", &day);
				printf("����  �ݾ� : ");
				scanf("%d", &expenditure);
				Deposit = Deposit - expenditure;

				fprintf(fp, "\n ��¥ : %d ��\n", day);
				fprintf(fp, "\n ���� �ݾ� : %d ��\n", Deposit);  //�ݾ��� list.txt ���Ͽ� ���
				printf("\n%d\n", Deposit);   //�ݾ��� ȭ�鿡 ���
			}

			else if (choice == 3) //�ܾ���ȸ ���ý�
			{
				printf("\n �ܾ� ��ȸ : %d\n", Deposit);//�ݾ��� ȭ�鿡  ���
				fprintf(fp, "\n �ܾ� ��ȸ : %d ��\n", Deposit); //�ݾ��� list.txt ���Ͽ� ���
			}

			else if (choice == 4) //���Ḧ ���ý�
			{
				printf("���α׷��� ���� �մϴ� \n");
				fclose(fp);
				break;
			}

			else
			{
				printf("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
				break;
			}
		}

		break;
	case 4:
		//���α׷� ����
		return 0;
	default:
		//�߸��� ��ȣ �Է�
		system("cls");
		printf("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
		break;
	}
}


//year�� month�� ���� �޾� �ش� ���� ��� -> title, body
void printMonth(int year, int month) {
	printMonthTitle(year, month);
	printMonthBody(year, month);
}

//���� �⵵�� ���
void printMonthTitle(int year, int month) {
	printMonthName(month);
	printf(" %d\n", year);
	printf("-----------------------------\n");
	printf(" Sun Mon Tue Wed Thu Fri Sat\n");
}

//month�� ���� �޾� �ش� ���� ���� �̸��� ���
void printMonthName(int month) {
	switch (month) {
	case 1: printf("January"); break;
	case 2: printf("February"); break;
	case 3: printf("March"); break;
	case 4: printf("April"); break;
	case 5: printf("May"); break;
	case 6: printf("June"); break;
	case 7: printf("July"); break;
	case 8: printf("August"); break;
	case 9: printf("September"); break;
	case 10: printf("October"); break;
	case 11: printf("November"); break;
	case 12: printf("December"); break;
	}
}

//year�� month�� ���� �޾� ���ϰ� ���� ���
void printMonthBody(int year, int month) {
	int startday = getStartDay(year, month);
	int numberofdaysinmonth = getNumberOfDaysInMonth(year, month);

	for (int i = 0; i < startday; i++) printf("    ");
	for (int i = 1; i <= numberofdaysinmonth; i++) {
		printf("%4d", i);
		if ((i + startday) % 7 == 0) printf("\n");
	}
}

// �ش� ���� �����ϴ� ���� �� �������� ã�� �Լ�
int getStartDay(int year, int month) {
	int startday1800 = 3;
	int totalnumberofdays = getTotalNumberOfDays(year, month);
	return (startday1800 + totalnumberofdays) % 7;
}

// 1800�� 1�� 1�� ���� ��ĥ�� �Ǵ��� ���
int getTotalNumberOfDays(int year, int month) {
	int total = 0;
	for (int i = 1800; i < year; i++) {
		if (isLeapYear(i)) total += 366;
		else total += 365;
	}
	for (int i = 1; i < month; i++) total = total + getNumberOfDaysInMonth(year, i);
	return total;
}

//year�� month�� ���� �޾� �ش���� ������ �ִ���
int getNumberOfDaysInMonth(int year, int month) {
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
	if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	if (month == 2) {
		if (isLeapYear(year) == 1) return 29;
		else return 28;
	}
}

//year�� ���޹޾� �������� Ȯ��
int isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) return 1;
	else return 0;
}

//##########################################################################
//������ ��¥�� ���� �̸����� ����ϱ� ����
//���������� ������ ����.
int get_date_file_name(void)
{
	int year, month, day;
	struct tm* t;
	time_t timer;

	timer = time(NULL);
	t = localtime(&timer);

	year = t->tm_year + 1900;
	month = t->tm_mon + 1;
	day = t->tm_mday;

	return (year * 10000 + month * 100 + day);
}

void print_opt(void)
{
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("�޴�����\n");
	printf("���ϴ� ����� ��ȣ�� �Է� �� ���͸� �����ֽʽÿ�.\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("1. Ķ����\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("2. �ϱ�\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("3. �����\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("4. ���α׷� ����\n");
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");
}

void print_title(void)
{
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("�ϱ���\n");
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");

	printf("���ϴ� ����� ��ȣ�� �Է� �� ���͸� �����ֽʽÿ�.\n");
	for (int i = 0; i < 17; i++)
		printf(" ");
	printf("1. �ϱ� ����\n");
	for (int i = 0; i < 17; i++)
		printf(" ");
	printf("2. �ϱ� ����\n");
	for (int i = 0; i < 17; i++)
		printf(" ");
	printf("3. ���α׷� ����\n");
}

void scan_description(char description[])
{
	int ch;
	unsigned int index = 0;
	char guide[] = "������ �ϱ⸦ �Է��Ͻʽÿ�(�����Ϸ��� ctrl + Z�� ������ enter.)";

	getchar();
	printf("%s(0/%d)\n", guide, MAX_DIARY_LENGTH - 1);

	while ((ch = getchar()) != EOF)
	{
		description[index] = ch;
		index = strlen(description);

		system("cls");
		printf(
			"%s(%d/%d):\n%s",
			guide,
			index,
			MAX_DIARY_LENGTH - 1,
			description
		);

		if (index + 1 == MAX_DIARY_LENGTH - 1)
		{
			puts("\n���� ������ �ʰ��Ͽ� �ۼ��� �����ϰ� �����մϴ�.");
			break;
		}
	}

	description[index + 1] = '\0';
}

void put_diary(int date, char description[])
{
	char filename[20];
	FILE* fp;

	sprintf(filename, "%d", date);
	strcat(filename, ".txt");
	fp = fopen(filename, "w");
	fprintf(fp, "%s", description);
	fclose(fp);
}

int get_diary(int date, char description[])
{
	char filename[20];
	FILE* fp;

	sprintf(filename, "%d", date);
	strcat(filename, ".txt");
	fp = fopen(filename, "r");

	if (fp == NULL)
		return 0;

	fgets(description, MAX_DIARY_LENGTH, fp);
	fclose(fp);
	return 1;
}
//
void print_account_book(void)
{
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("�����\n");
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");
	printf("���� �ڻ��� �Է����ּ���. \n");
}