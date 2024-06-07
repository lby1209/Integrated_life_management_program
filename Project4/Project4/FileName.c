#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DIARY_LENGTH 1000

void print_opt(void);
//캘린더
void printMonth(int year, int month);
void printMonthTitle(int year, int month);
void printMonthName(int month);
void printMonthBody(int year, int month);
int getStartDay(int year, int month);
int getTotalNumberOfDays(int year, int month);
int getNumberOfDaysInMonth(int year, int month);
int isLeapYear(int year);
//일기
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

	//시작시 현재의 년월일을 출력한다
	now = time(NULL);
	tp = localtime(&now);
	printf("오늘날짜 : %d/%d/%d\n", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);

	char description[MAX_DIARY_LENGTH] = "";
	//선택창 출력
	print_opt();
	
	scanf("%d", &option);


	switch (option)
	{
	case 1:
		//캘린더
		// 년도 입력
		printf("년도 : ");
		scanf("%d", &year);
		// 월 입력
		printf("월 : ");
		scanf("%d", &month);
		printMonth(year, month);
			
		break;
	case 2:
		//일기
		while (1)
		{
			description[0] = '\0';
			print_title();
			scanf("%d", &menu);
			system("cls");
			switch (menu)
			{
			case 1:
				//일기 쓰기 시작
				scan_description(description);
				date = get_date_file_name();
				put_diary(date, description);
				system("cls");
				printf("\n\n~~![%d.txt] 일기 작성 완료\n\n", date);
				break;
			case 2:
				//일기 보기 시작
				printf("확인하고 싶은 날짜를 입력해주세요 (YYYYMMDD): ");
				scanf("%d", &date);
				system("cls");

				if (get_diary(date, description))
					printf("\n\n%d.txt의 정보:\n%s\n\n(그만 보려면 아무 키나 누르세요.)\n", date, description);
				else
					printf("그 날에는 일기를 작성하지 않았습니다.\n(아무 키나 눌러 메인화면으로 돌아가기.)\n");

				getchar();
				getchar();
				system("cls");
				break;
			case 3:
				//프로그램 종료
				return 0;
			default:
				//잘못된 번호 입력
				system("cls");
				printf("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
				break;
			}
		}
		break;
	case 3:
		//가계부
		FILE * fp;
		int earnings = 0;  //수입
		int expenditure = 0;  //지출
		int Deposit = 0;  //잔액
		int choice = 0;  //선택사항
		int day;

		fp = fopen("list.txt", "w"); //시작과 동시에 list.txt 파일이 생성된다.
		print_account_book();
		scanf("%d", &Deposit);
		fprintf(fp, "\n 현재 자산 : %d 원\n", Deposit);  //현재 자산을 list.txt 파일에 입력한다.

		while (1)
		{
			if (Deposit == 0)  break;	//입력받은 자산이 0을 입력시 종료.
			
			printf("\n기능 선택 (1.수입 2.지출 3.잔액 조회 4.종료) : ");
			scanf("%d", &choice);

			if (choice == 1)  //수입을 선택할시
			{
				printf("수입 금액 : ");
				scanf("%d", &earnings);
				Deposit = Deposit + earnings;

				fprintf(fp, "\n 수입 금액 : %d 원\n", Deposit);
				printf("\n%d\n", Deposit);
			}

			else if (choice == 2) // 지출을 선택시
			{
				printf("날짜(YYMMDD) : ");
				scanf("%d", &day);
				printf("지출  금액 : ");
				scanf("%d", &expenditure);
				Deposit = Deposit - expenditure;

				fprintf(fp, "\n 날짜 : %d 원\n", day);
				fprintf(fp, "\n 지출 금액 : %d 원\n", Deposit);  //금액을 list.txt 파일에 출력
				printf("\n%d\n", Deposit);   //금액을 화면에 출력
			}

			else if (choice == 3) //잔액조회 선택시
			{
				printf("\n 잔액 조회 : %d\n", Deposit);//금액을 화면에  출력
				fprintf(fp, "\n 잔액 조회 : %d 원\n", Deposit); //금액을 list.txt 파일에 출력
			}

			else if (choice == 4) //종료를 선택시
			{
				printf("프로그램을 종료 합니다 \n");
				fclose(fp);
				break;
			}

			else
			{
				printf("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
				break;
			}
		}

		break;
	case 4:
		//프로그램 종료
		return 0;
	default:
		//잘못된 번호 입력
		system("cls");
		printf("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
		break;
	}
}


//year와 month를 전달 받아 해당 월을 출력 -> title, body
void printMonth(int year, int month) {
	printMonthTitle(year, month);
	printMonthBody(year, month);
}

//월과 년도를 출력
void printMonthTitle(int year, int month) {
	printMonthName(month);
	printf(" %d\n", year);
	printf("-----------------------------\n");
	printf(" Sun Mon Tue Wed Thu Fri Sat\n");
}

//month를 전달 받아 해당 달의 영어 이름을 출력
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

//year와 month를 전달 받아 요일과 일을 출력
void printMonthBody(int year, int month) {
	int startday = getStartDay(year, month);
	int numberofdaysinmonth = getNumberOfDaysInMonth(year, month);

	for (int i = 0; i < startday; i++) printf("    ");
	for (int i = 1; i <= numberofdaysinmonth; i++) {
		printf("%4d", i);
		if ((i + startday) % 7 == 0) printf("\n");
	}
}

// 해당 월의 시작하는 날이 몇 요일인지 찾는 함수
int getStartDay(int year, int month) {
	int startday1800 = 3;
	int totalnumberofdays = getTotalNumberOfDays(year, month);
	return (startday1800 + totalnumberofdays) % 7;
}

// 1800년 1월 1일 부터 며칠이 되는지 계산
int getTotalNumberOfDays(int year, int month) {
	int total = 0;
	for (int i = 1800; i < year; i++) {
		if (isLeapYear(i)) total += 366;
		else total += 365;
	}
	for (int i = 1; i < month; i++) total = total + getNumberOfDaysInMonth(year, i);
	return total;
}

//year와 month를 전달 받아 해당월에 몇일이 있는지
int getNumberOfDaysInMonth(int year, int month) {
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
	if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	if (month == 2) {
		if (isLeapYear(year) == 1) return 29;
		else return 28;
	}
}

//year를 전달받아 윤년인지 확인
int isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) return 1;
	else return 0;
}

//##########################################################################
//오늘의 날짜를 파일 이름으로 사용하기 위해
//정수형으로 변경해 리턴.
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
	printf("메뉴선택\n");
	printf("원하는 기능의 번호를 입력 후 엔터를 눌러주십시오.\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("1. 캘린더\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("2. 일기\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("3. 가계부\n");
	for (int i = 0; i < 20; i++)
		printf(" ");
	printf("4. 프로그램 종료\n");
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
	printf("일기장\n");
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");

	printf("원하는 기능의 번호를 입력 후 엔터를 눌러주십시오.\n");
	for (int i = 0; i < 17; i++)
		printf(" ");
	printf("1. 일기 쓰기\n");
	for (int i = 0; i < 17; i++)
		printf(" ");
	printf("2. 일기 보기\n");
	for (int i = 0; i < 17; i++)
		printf(" ");
	printf("3. 프로그램 종료\n");
}

void scan_description(char description[])
{
	int ch;
	unsigned int index = 0;
	char guide[] = "오늘의 일기를 입력하십시오(종료하려면 ctrl + Z를 누르고 enter.)";

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
			puts("\n글자 제한을 초과하여 작성을 종료하고 저장합니다.");
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
	printf("가계부\n");
	for (int i = 0; i < 50; i++)
		printf("*");
	printf("\n");
	printf("현재 자산을 입력해주세요. \n");
}