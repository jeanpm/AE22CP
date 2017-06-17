# include <stdio.h>
# define MAX 100

typedef struct mate{
    char value;
}elem;



typedef struct{
    elem L[MAX];
    int quant;
}Pilha;

void CriaPilha(Pilha *p)
{
    p->quant = 0;
}



// Inserir
int Inserir(Pilha *x, elem *e, int pos)
{
    if(x->quant == MAX)
    {
        return -1;
    }
    else if(pos > x->quant)
    {
        return -2;
    }
    else
    {
        if(x->quant == pos)
        {
            x->L[pos] = *e;
        }
        else
        {
            int i;
            for(i=x->quant ; i>pos ; i--)
            {
                x->L[i] = x->L[i-1];
            }
            x->L[pos] = *e;
        }
        x->quant++;
    }
    return 1;
}

int Push(Pilha *p, elem *e)
{
    return Inserir(p, e, p->quant);
}



//Remover
int Remove(Pilha *x, int pos)
{
    int i;
    if(pos > x->quant)
    {
        return -1;
    }
    else
    {
        for(i=pos ; i < x->quant ; i++)
        {
            x->L[i] = x->L[i+1];
        }
        x->quant--;
    }
    return -1;
}

int Pop(Pilha *p)
{
    return Remove(p, p->quant-1);
}

int main(void)
{
    Pilha P1;
    CriaPilha(&P1);
    char M[] = "{[(a+b)*c]-[d]{}";
    int i;
    for(i=0 ; M[i] != '\0' ; i++)
    {
        if(M[i] == '(' || M[i] == '[' || M[i] == '{')
        {
        	elem e = {M[i]};
            if(M[i] == '(')
            {            	
//                Push(&P1, &M[i]);
                Push(&P1, &e);
            }
            else if(M[i] == '[')
            {
//                Push(&P1, &M[i]);
                Push(&P1, &e);
            }
            else
            {
//                Push(&P1, &M[i]);
                Push(&P1, &e);
            }
        }

        else if(M[i] == ')' || M[i] == ']' || M[i] == '}')
        {
            if(M[i] == ')')
            {
                if(P1.L[P1.quant-1].value == '(')
                {
                    Pop(&P1);
                }
                else
                {
                    //return -1;
                }
            }
            else if(M[i] == ']')
            {
                if(P1.L[P1.quant-1].value == '[')
                {
                    Pop(&P1);
                }
                else
                {
                    //return -1;
                }
            }
            else
            {
                if(P1.L[P1.quant-1].value == '{')
                {
                    Pop(&P1);
                }
                else
                {
                    //return -1;
                }
            }
        }
    }
    for(i=0 ; i<P1.quant ; i++)
    {
        printf("%c ", P1.L[i].value);
    }
}


/*
int Exer01(Pilha *p, char M[])
{
    int i;
    for(i=0 ; M[i] != '\0' ; i++)
    {
        if(M[i] == '(' || M[i] == '[' || M[i] == '{')
        {
            if(M[i] == '(')
            {
                Push(&p, &M[i]);
                printf("oi");

            }
            else if(M[i] == '[')
            {
                Push(&p, &M[i]);
            }
            else
            {
                Push(&p, &M[i]);
            }
        }

        else if(M[i] == ')' || M[i] == ']' || M[i] == '}')
        {
            if(M[i] == ')')
            {
                if(p->L[p->quant].value == '(')
                {
                    Pop(&p);
                }
                else
                {
                    return -1;
                }
            }
            else if(M[i] == ']')
            {
                if(p->L[p->quant].value == '[')
                {
                    Pop(&p);
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                if(p->L[p->quant].value == '{')
                {
                    Pop(&p);
                }
                else
                {
                    return -1;
                }
            }
        }
    }
    return 1;
}
*/
