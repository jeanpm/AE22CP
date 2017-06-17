#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	const char* s = "12319283721093809840982984791791287393812";

for (int i = 0; i < strlen(s); i++)
	printf("%c\t%d\n", s[i], (int) s[i] - '0'); 
}
