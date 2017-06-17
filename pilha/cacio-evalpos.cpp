#include <bits/stdc++.h>
#include <math.h>
#include <ctype.h>

using namespace std;

double operacao(char c, double a, double b);
double evalposfix(const char* expressao);

int main() {
    string expressao;
    cin >> expressao;
    
   //expressao.c_str();
    
    double r;
    
        printf("%s\n", isblank(expressao.c_str()[1]) ? "true" : "false");

    r = evalposfix(expressao.c_str());

    // para teste no pc
    //printf("%.2f\n",r);

    // para envio
    printf("%f",r);
    return 0;
    
}

//funÃ§Ãµes 
double evalposfix(const char* expressao)
{
    stack<double> pilha; 
    int i=0;
    double t;
    while(expressao[i]!='\0')
    {
        //debug
        //printf("%d\n",i);
       

        if(isdigit(expressao[i]))
        {
            pilha.push((double) expressao[i] - '0' );
            //debug:
            printf("inseriu %c\n",expressao[i]);
        }
        else 
        {
            if(pilha.size()<2)
            {
                printf("ERRO! NÃ£o hÃ¡ operandos suficientes.\n");
            }
            else
            {
                double a, b;
                b =  pilha.top();
                pilha.pop();
                a = pilha.top();
                pilha.pop();
                t = operacao(expressao[i],a,b);
                
                pilha.push(t);
                //DEBUG 
                //printf("%f \t",pilha.top());
            }               
        }
        i++;
       
    }

    return(pilha.top());
    
}
double operacao(char c, double a, double b)
{
    if(c == '*')                // operaÃ§Ã£o de multiplicaÃ§Ã£o
    {       
        return(a*b);
    }
    if(c == '+')                // operaÃ§Ã£o de adiÃ§Ã£o
    {
        return(a+b);
    }
    if(c == '-')                // operaÃ§Ã£o de subtraÃ§Ã£o
    {
        return(a-b); 
    }
    if(c == '/')                // operaÃ§Ã£o de divisÃ£o
    {
        return(a/b);
    }
    if(c == '^')                // operaÃ§Ã£o de  potenciaÃ§Ã£o
    {
        return(pow(a,b));
    }
    
    return 0;
}
