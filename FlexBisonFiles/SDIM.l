%option C++ noyywrap

%{
    #include <iostream>
    #include "SDIM.tab.h"
int line_no = 0;
void Error(const char* msg);
%}

whitespace [ \t]+

letter [A-Za-z]

digit ([0-9])+

integer [+-](digit)+

float [+-]?{digit}+(\.)?{digit}+[fd]?

string \"[^\n"]+\"




%%

"/*"		{
		int c;

		while((c = yyinput()) != 0)
			{
			if(c == '\n')
				++line_no;

			else if(c == '*')
				{
				if((c = yyinput()) == '/')
					break;
				else
					unput(c);
				}
			}
}

{whitespace} /* skip whitespace characters */

{integer} std::cout << " Integer literal " << YYText() << "\n";

{float} std::cout << " Float literal " << YYText() << "\n";


";" std::cout << "Semicolon \n";

\n line_no++;

. Error("Unmatched character sequence")
%%
void Error(const char* msg)
{
    std::cout << "Error: " << msg << "\n";
}
int main(int argc, char** argv)
{

    FlexLexer* lex = new yyFlexLexer;
    lex->yyin = 
    while(lex->yylex() != 0)
    {

    }
    return 0;
}