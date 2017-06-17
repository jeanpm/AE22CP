#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ND {
    char data;
    struct ND * prev;
    struct ND * next;
} DoubleNode;

typedef struct {
    int quant;
    struct ND * head;
    struct ND * tail;
} DoubleLinkedList;

void DoubleLinkedList_PrintAllNodes(DoubleLinkedList * l);



// INIT FUNCTIONS
DoubleNode * DoubleLinkedList_Node(char data){
    DoubleNode * nd = malloc(sizeof(DoubleNode));
    nd->data = data;
    return nd;
}

DoubleLinkedList * DoubleLinkedList_New(){
    DoubleLinkedList * l = malloc(sizeof(DoubleLinkedList));
    l->quant = 0;
    return l;
}




// INSERTION FUNCTIONS
void DoubleLinkedList_AddAtTail(DoubleLinkedList * l, DoubleNode * nd){
    if(l->quant == 0){
        l->head = nd;
    } else if(l->quant > 1){
        nd->prev = l->tail;
        l->tail->next = nd;
        l->tail = nd;
    } else {
        l->head->next = nd;
        nd->prev = l->head;
        l->tail = nd;
    }l->quant++;
}

void DoubleLinkedList_AddAtHead(DoubleLinkedList * l, DoubleNode * nd){
    nd->next = l->head;
    l->head = nd;
    l->quant++;
}

void DoubleLinkedList_AddAt(DoubleLinkedList *l, DoubleNode * nd, int pos){
    if(l->quant == 0 || pos == 0){
        DoubleLinkedList_AddAtHead(l, nd);
    } else if (pos == l->quant) {
        DoubleLinkedList_AddAtTail(l, nd);
    } else if (pos < l->quant){
        DoubleNode * temp = l->head;
        int count=0;
        while(count < pos){
            temp = temp->next;
            count++;
        }
        nd->next = temp;
        nd->prev = temp->prev;
        temp->prev->next = nd;
        temp->prev = nd;
        l->quant++;
    }
}




// REMOVE FUNCTIONS
void DoubleLinkedList_RemoveFromTail(DoubleLinkedList *l){
    if(l->quant <= 1){
        l->head = NULL;
    } else {
        l->tail = l->tail->prev;
    }
    if(l->quant > 0){
        l->quant--;
    }
}

void DoubleLinkedList_RemoveFromHead(DoubleLinkedList *l){
    if(l->quant != 0){
        l->head = l->head->next;
        free(l->head->prev);
        l->quant--;
    }
}

void DoubleLinkedList_RemoveAt(DoubleLinkedList *l, int pos){
    if(l->quant > 0){
        if(pos == 0){
            DoubleLinkedList_RemoveFromHead(l);
        } else if(pos < l->quant){
            int count=0;
            DoubleNode * temp = l->head;
            while(count < pos-1){
                temp = temp->next;
                count++;
            }
            temp->next = temp->next->next;
            l->quant--;
        }
    }
}




// DEBUGGING FUNCTIONS
void DoubleLinkedList_PrintAllNodes(DoubleLinkedList * l){
    DoubleNode * temp = l->head;
    for(int i=0; i < l->quant; i++){
//        if(temp != NULL){
            //printf("Node %2d:  %c\n", i, temp->data);
            //[!]
            printf("%c", temp->data);
            temp = temp->next;
/*        } else {
            printf("Falha de Segmentacao.\n");
            return;
        }
*/      
    }
    printf("\n");
}




// EXERCISE FUNCTIONS
DoubleLinkedList * DoubleLinkedList_StringToList(char *longInt){
    DoubleLinkedList * l = DoubleLinkedList_New();
    for(int i=0; i < strlen(longInt); i++){
        DoubleNode * temp = DoubleLinkedList_Node(longInt[i]);
        DoubleLinkedList_AddAtTail(l, temp);
    }
    return l;
}

int charToInt(char num){
    return (int)(num - '0');
}

int intToChar(int num){
    return (char)(num + '0');
}

DoubleLinkedList * DoubleLinkedList_Add(DoubleLinkedList *l, DoubleLinkedList *m){
    DoubleNode * biggerPoint = l->head;
    DoubleNode * lesserPoint = m->head;
    DoubleLinkedList * result = DoubleLinkedList_New();
    if(l->quant < m->quant){
        biggerPoint = m->head;
        lesserPoint = l->head;
    }
    //printf("");
    int sumRest=0;
    while(lesserPoint != NULL){
        int sum = charToInt(biggerPoint->data) + charToInt(lesserPoint->data) + sumRest;
        DoubleNode * digit = DoubleLinkedList_Node(intToChar(sum%10));
        if(sum >= 10) {
            sumRest = 1;
        } else {
            sumRest = 0;
        }
        DoubleLinkedList_AddAtHead(result, digit);
        biggerPoint = biggerPoint->next;
        lesserPoint = lesserPoint->next;
    }

    while(biggerPoint != NULL){
        int sum = charToInt(biggerPoint->data) + sumRest;
        sumRest = 0;
        
        DoubleNode * digit = DoubleLinkedList_Node(sum);
        DoubleLinkedList_AddAtHead(result, digit);
        biggerPoint = biggerPoint->next;
    }
    if(sumRest == 1){
        DoubleNode * digit = DoubleLinkedList_Node(1);
        DoubleLinkedList_AddAtHead(result, digit);
    }
    return result;
}


int main(int argc, char** argv){

    char * a = argv[1];//"000000000000999999999999999999999";
    char * b = argv[2]; //"22";
    DoubleLinkedList * l = DoubleLinkedList_StringToList(a);
    DoubleLinkedList * m = DoubleLinkedList_StringToList(b);
    
    //[!]
DoubleLinkedList_PrintAllNodes(l);
DoubleLinkedList_PrintAllNodes(m);

    DoubleLinkedList * result = DoubleLinkedList_Add(l, m);
    DoubleLinkedList_PrintAllNodes(result);
    return 0;

    // (B) A motivacao para usar listas dinamicas nesse problema eh que 
    //     Nao depende do tamanho do numero em termos de algarismos, e
    //     Possibilita trabalhar com numeros de tamanhos "infinitos".
}





