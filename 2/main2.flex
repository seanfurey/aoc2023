%{
#include <math.h>
%}

	int n = 0;
	int id = 0;
	int red=0;
	int green=0;
	int blue=0;
    int total=0;

%%
[0-9]+ { n=atoi(yytext); }
: { id=n; }
red { if (n>red) red=n; }
green { if (n>green) green=n; }
blue { if (n>blue) blue=n; }
\n {
total += red*green*blue;
printf("%d\n", total);
red = green = blue = 0;
}
. {}
