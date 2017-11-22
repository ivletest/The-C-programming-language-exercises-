#include<stdio.h>
#include<math.h>
#define MAX_LINE 10

int getline(char line[]);
int htoi(char line[], int len);

int main()
{
	int len;
	char line[MAX_LINE];
	len = getline(line);

	printf("%s in decimal is: ", line);
	printf("%d\n", htoi(line, len));
	
	return 0;
}

int getline(char line[MAX_LINE])
{
	int i, c;

	for(i = 0; i < MAX_LINE && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	line[i] = '\0';
	return i;
}

int htoi (char line[], int len)
{
	int plc_hold, sum;
	plc_hold = sum = 0;

	for(int i = 0; i < len; i++)
	{
		plc_hold = pow(16, ((len-1) - i)); // set placehoder values for hex system

		if(line[i] >= '0' && line[i] <='9')
			line[i] -= '0';

		else if(line[i] >= 'a' && line[i] <='f')
			line[i] = (line[i] - 'a') + 10;

		else if(line[i] >= 'A' && line[i] <='A')
			line[i] = (line[i] - 'A') + 10;

		else if (line[i] == 'x' || line[i] == 'X')
			line[i] = 0; // reset X mark to zero
		
		else
			return 37707;

		sum += line[i] * plc_hold;
	}
	return sum;
}