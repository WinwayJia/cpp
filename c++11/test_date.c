#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int getLastMonthSecond()
{
	time_t liNow = time(NULL);
	struct tm loTm;
	if (localtime_r(&liNow, &loTm))
	{
		// 一天为单位
		loTm.tm_hour = 0;
		loTm.tm_min = 0;
		loTm.tm_sec = 0;
		if (0 == loTm.tm_mon)
		{
			loTm.tm_mon = 11;
			loTm.tm_year --;
		}
		else
		{
			loTm.tm_mon --;
		}
	}
	return mktime(&loTm);
}

int getCurrentYearMonth()
{
	time_t liNow = time(NULL);
	struct tm loTm;
	if (localtime_r(&liNow, &loTm))
	{
		loTm.tm_mday -= 9;
		return (loTm.tm_year+1900) * 10000 + (loTm.tm_mon + 1) * 100 + loTm.tm_mday;
	}
	return -1;
}

int getLastYearMonth()
{
	time_t liNow = time(NULL);
	struct tm loTm;
	if (localtime_r(&liNow, &loTm))
	{
		if (0 == loTm.tm_mon)
			return (loTm.tm_year+1900-1) * 100 + 12;
		else
			return (loTm.tm_year+1900) * 100 + loTm.tm_mon;
	}
	return -1;
}

int strToDate(const char* date)
{
	int liYMD = atoi(date);

	int miYear = liYMD / 10000;
	int miMonth = (liYMD % 10000) / 100;
	int miDay = liYMD % 100;

	printf("%d %d %d\n", miYear, miMonth, miDay);
	return 0;
}

void output(const char* sec)
{
	time_t t = atoi(sec);

	struct tm* tm = localtime(&t);
	printf("%d%02d%02d %02d:%02d:%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

int main(int argc, char** argv)
{
	char *endptr;
	unsigned long long  tmp = strtoull("9008000000197641", &endptr, 10);
	printf("%llu\n", tmp);

	time_t liTime = time(NULL);
	struct tm *lpTm = localtime(&liTime);

	lpTm->tm_mday -= 1;

	printf("%d - %d = %d\n", (int)liTime, (int)mktime(lpTm), (int)(liTime-mktime(lpTm))); 

	printf("%08d %08d %08d\n", getLastMonthSecond(), getCurrentYearMonth(), getLastYearMonth());


	char* date = "20150807";

	strToDate(date);


	output(argv[1]);
	return 0;
}
