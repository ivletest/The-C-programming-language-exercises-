#include <stdio.h>
#define MAX 1000

int remove (char line[MAX], int i, int temp);

int main()
{
	char line[MAX];
	int text, i, temp;
	i =  temp = 0;
	
	while ((text = getchar()) != EOF && i < MAX)
	{
		line[i] = text;
		
		if (line[i] == '*' && i > 0 && line[i -1] == '/')
			temp = i - 1;
		else if (line[i] == '/' && i > 0 && line[i - 1] == '*')
			i = remove(line, i, temp);
		i++;
	}
	
	printf ("%s", line);
	return 0;
}

int remove (char line[MAX], int i, int temp)
{
	while( i >= temp)
	{	
		line[i] = ' ';
		i--;
	}
	if(line[i-1] == '\n')
		i -=2;
	else
		i -=1;
	return i;
}
