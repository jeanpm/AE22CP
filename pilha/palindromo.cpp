#include <stack>
#include <assert.h>
#include <stdio.h>

bool isPalindrome2(char* p)
{
	std::stack<char> s;
	
	int i = 0;	
	bool empilhar = true;
	char atual = p[i];
	
	while (p[i] != '\0')
	{
		atual = p[i++];
		
		if (atual == 'C') {		
			empilhar = false;
			continue;
		}
		
		if (empilhar) 
			s.push(atual);
		else {
			if (s.empty() || (s.top() != atual))
				return false;
			s.pop();
		}
	}
	
	if (!s.empty()) return false;
		
	return true;
}

bool isPalindrome(char* p)
{
	std::stack<char> s;
	
	int i = 0;	
	
	while (p[i] != 'C' && p[i] != '\0')
		s.push(p[i++]);
	
	if (p[i] != '\0') i++;
	
	while (p[i] != '\0')
	{	
		if (s.empty() || (s.top() != p[i++]))
			return false;
		s.pop();
	}
	
	if (!s.empty()) return false;
		
	return true;
}

int main (int argc, char** argv)
{
	assert(argc == 2);
	
	char* p = argv[1];
	printf("%s\n", isPalindrome(p) ? "true" : "false");	
}
