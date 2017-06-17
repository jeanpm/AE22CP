void printLista(Lista* l)
{
	if (l->inicio != NULL)
	{
		Item* curr = l->inicio;
		while(curr != l->fim)
		{
			fprintf(stderr, "%d", curr->valor); 
			curr = curr->prox;
		}
		fprintf(stderr, "%d\n", curr->valor); 
	}
}
