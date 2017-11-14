#include <stdio.h>
#define MAXLINE 1000  //Input characters limiter

char line[MAXLINE];  //Input line
char err_line[MAXLINE]; // Lines of Error

//int err_index[MAXLINE] [MAXLINE] // Bracket characters array arranged in order [ type ] [ line ]
int brack, brace, par, s_quote, d_quote;/* Variables for the symbols(brackets, quotes etc..). 
Opening symbol adds three, closing subtracts three (this serves as an index for err_index array which is 
arranged in groups by three). if the end result is zero all open brackets were closed */
//line_no, type_i; // place on the line, line number, and and type_index 0 = '[', 1 = '{' 2 = '(' 3 = '"' 4 = ' ' '
int line_no = 1;
//place = type_i = 0;


int check_line(void); // Check the text function declaration.
void print_err(void); // Print errors function declaration.


int main()
{
	
	check_line();
	print_err();
	return 0;
	
}

int check_line(void)
{
	int c, i;
	brack = brace = par = s_quote = d_quote = 0;
	//brack = 0;
	// brace = 1000; 
	// par = 2000;
	// s_quote = 3000;
	// d_quote = 4000;
	
	for (i = 0; i < MAXLINE -1 && (c = getchar()) != EOF; ++i)
	{
		line[i] = c;
		
		if (c == '\n')
			++line_no;
		
		switch(line[i])
		{
			case '[' : // c is an opening bracket
			{
				//err_index[brack][brack] = { '[' , line_no }; 
				brack++;
				break;
			}
			case ']' : // c is a closing bracket
			{
				if(brack > 0) // if there IS an open bracket
				
					brack--;
				else // if there is NO open bracket 
				{
					err_line[line_no] = ']'; // remember the line of error
					brack = 0; // reset
				}
				break;
			}
			case '{' : // The same logic goes for braces and parentheses
				brace++;
				break;
			case '}' :
			{
				if(brace > 0)
					brace--;
				else
				{
					err_line[line_no] = '}';
					brace = 0;
				}
				break;
			}
			case '(' :
				par++;
				break;
			case ')' :
			{
				if(par > 0)
					par--;
				else
				{
					err_line[line_no] = ')';
					par = 0;
				}
				break;
			}
			case '\'' : // if c is a single quote 
			{
				if (s_quote == 0 && d_quote == 0) // if there are no open quotes (single or double)
				{
					s_quote++; 
				}
				else if (s_quote == 1 &&  line[i -1] != '\\') // else if a single quote is open and previous character is not escape '\'
				{
					s_quote--;
				}
				break;
			}
			
			case '\"' : // Same logig goes for double quotes
			{
				if (d_quote == 0 && s_quote == 0)
				{
					d_quote++;
				}
				else if (d_quote == 1 && line[i -1] != '\\')
				{
					d_quote--;
				}
				break;
			}
			default:
				break;
		}
	}
	
	line[i] = '\0';
	
	return i;
}

void print_err(void)
{
	int i;
	
	for ( i = 0; i < MAXLINE - 1; ++i)
	{
		if (err_line[i] == ']' || err_line[i] == '}' || err_line[i] == ')')
			printf("Line: %d - Closing %c without pair.\n", i, err_line[i]);
	}
	if(brack != 0)
		printf("%d un-closed '[' !\n", brack);
	if(brace != 0)
		printf("%d un-closed '{' !\n", brace);
	if(par != 0)
		printf("%d un-closed '(' !\n", par);
	if (s_quote != 0)
		printf("%d un-closed ' ' ' !\n", s_quote);
	if (d_quote != 0)
		printf("%d un-closed '\"' !\n", d_quote);
	
}