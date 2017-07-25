//José Santos nº 33622
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//-----------------------------------LISTA----------------------------------
typedef struct empresa   //estrutura de dados
{
    int dia,mes,ano,opiniao;
    char email_recetor[50],email_emissor[50];
    struct empresa *next;
} EMPRESA;

EMPRESA *makeNodeLista() //Criar Node Lista
{
    EMPRESA *nv=(EMPRESA*)malloc(sizeof(EMPRESA));
    nv->next=NULL;
    return nv;
}

EMPRESA *insertFirst(EMPRESA *L,EMPRESA *nv) //Inserir no inicio da lista
{
    nv->next=L;
    return nv;
}

EMPRESA *findemissor(EMPRESA *L, char email[]) //Encontrar um email emissor numa lista
{
    while(L!=NULL)
    {
        if(strcmp(L->email_emissor,email)==0)
            return(L);
        L=L->next;
    }
    return (NULL);
}

EMPRESA *findrecetor(EMPRESA *L, char *email) //Encontrar um email recetor numa lista
{
    while(L!=NULL)
    {
        if(strcmp(L->email_recetor,email)==0)
            return(L);
        L=L->next;
    }
    return (NULL);
}

void ordenaremissor(EMPRESA **L)  //Ordenar Lista por email emissor
{
    int done = 0;
    if (*L==NULL || (*L)->next==NULL)
        return;
    while(!done)
    {
        EMPRESA **pv=L;            // fonte do apontador para o nodo atual da lista
        EMPRESA *current=*L;            // apontador iterativo local
        EMPRESA *nx=(*L)->next;  // proximo apontador iterativo local
        done=1;
        while(nx)
        {
            if(strcmp(current->email_emissor,nx->email_emissor)>0) //ordenar
            {
                current->next=nx->next;
                nx->next=current;
                *pv=nx;
                done=0;
            }
            pv=&current->next;//nodo atual passa a ser o endereço da variável current->next
            current=nx;     //current passa a ser proximo local
            nx=nx->next;    //nx passa a ser o proximo local
        }
    }
}

void ordenarrecetor(EMPRESA **L)  // Ordenar Lista por email recetor
{
    int done = 0;
    if (*L==NULL || (*L)->next==NULL)
        return;
    while(!done)
    {
        EMPRESA **pv=L;            // fonte do apontador para o nodo atual da lista
        EMPRESA *current=*L;            // apontador iterativo local
        EMPRESA *nx=(*L)->next;  // proximo apontador iterativo local
        done=1;
        while(nx)
        {
            if(strcmp(current->email_recetor,nx->email_recetor)>0)
            {
                current->next=nx->next;
                nx->next=current;
                *pv=nx;
                done=0;
            }
            pv=&current->next;
            current=nx;
            nx=nx->next;
        }
    }
}

void delete_list(EMPRESA **L)  //Apagar uma Lista
{
    EMPRESA *current=*L;
    EMPRESA *next;
    while(current!=NULL)
    {
        next=current->next;
        free(current);
        current=next;
    }
    *L=NULL;
}

//--------------------------------Árvore---------------------------------------------

typedef struct arvore  //Estrutura de dados para arvore
{
    int flag;
    EMPRESA *p;
    struct arvore *fd,*fe;
} ARVORE;

ARVORE *makeNodeArvore() //Criar Node Árvore
{
    ARVORE *nv=(ARVORE*)malloc(sizeof(ARVORE));
    nv->fd=NULL;
    nv->fe=NULL;
    nv->flag=0;
    return nv;
}

int max(int a, int b) //Máx entre 2 numeros
{
    if(a>b)
        return a;
    return b;
}

int min(int a, int b, int n) // Min entre dois numeros
{
    if(a>b)
        a=b;
    if(a>n)
        return (a);
    return (0);
}

int profundidade(ARVORE *A) //Calcular o nível de profundidade de uma árvore
{
    if(A==NULL)
        return 0;
    return(1+max(profundidade(A->fe),profundidade(A->fd)));
}

int Balance(ARVORE *A) //Calcular diferença de nívei entre a sub árvore esquerda e direita
{
    return(profundidade(A->fe)-profundidade(A->fd));
}

ARVORE *rotacaoDireita(ARVORE *A) //Rodar uma árvore á direita
{
    ARVORE *aux;

    if(A== NULL)
        return NULL;
    aux = A->fe;
    if(aux != NULL)
    {
        A->fe = aux->fd;
        aux->fd = A;
        A = aux;
    }
    return A;
}

ARVORE *rotacaoEsquerda(ARVORE *A) //Rodar uma Árvore á esquerda
{
    ARVORE *aux;

    if(A == NULL)
        return NULL;

    aux = A->fd;

    if(aux != NULL)
    {
        A->fd = aux->fe;
        aux->fe = A;
        return aux;
    }
    return A;
}

ARVORE *insertEmissor(ARVORE *A,ARVORE *nv) //Inserir numa árvore por email emissor
{
    if(A==NULL || nv==NULL)
    {
        A=nv;
        return A;
    }
    ARVORE *aux=A;
    while(aux!=NULL)
    {
        if(strcmp(aux->p->email_emissor,nv->p->email_emissor)>=0)  //se raiz >= que inserir vai para a esquerda
        {
            if(aux->fe==NULL)
            {
                aux->fe=nv;
                return A;
            }
            aux=aux->fe;
            continue;
        }
        if(aux->fd==NULL) //senao vai para a direita
        {
            aux->fd=nv;
            return A;
        }
        aux=aux->fd;
    }
    return NULL;
}

ARVORE *insertRecetor(ARVORE *A,ARVORE *nv)//Inserir numa árvore por email recetor
{
    if(A==NULL || nv==NULL)
    {
        A=nv;
        return A;
    }
    ARVORE *aux=A;
    while(aux!=NULL)
    {
        if(strcmp(aux->p->email_recetor,nv->p->email_recetor)>=0)  //se raiz >= que inserir vai para a esquerda
        {
            if(aux->fe==NULL)
            {
                aux->fe=nv;
                return A;
            }
            aux=aux->fe;
            continue;
        }
        if(aux->fd==NULL) //senao vai para a direita
        {
            aux->fd=nv;
            return A;
        }
        aux=aux->fd;
    }
    return NULL;
}

void reset(ARVORE *A) //resetar as flags de uma árvore
{
    if(A==NULL)
        return;
    reset(A->fe);
    A->flag=0;
    reset(A->fd);
}

ARVORE *findEmissorArvore(ARVORE *A,char *n,int valor) //Encontrar um email emissor numa árvore
{
    ARVORE *aux;
    if(A==NULL)
        return NULL;
    if(strcmp(A->p->email_emissor,n)==0 && A->flag==0 && valor<(A->p->opiniao))
    {
        A->flag=1;
        return A;
    }
    aux=findEmissorArvore(A->fe,n,valor);
    if(aux!=NULL)
        return aux;
    return (findEmissorArvore(A->fd,n,valor));
}

ARVORE *findRecetorArvore(ARVORE *A,char *n,int valor) //Encontrar um email recetor numa árvore
{
    ARVORE *aux;
    if(A==NULL)
        return NULL;
    if(strcmp(A->p->email_recetor,n)==0 && A->flag==0 && valor<(A->p->opiniao))
    {
        A->flag=1;
        return A;
    }
    aux=findRecetorArvore(A->fe,n,valor);
    if(aux!=NULL)
        return aux;
    return (findRecetorArvore(A->fd,n,valor));
}

//-----------------------------Lista2----------------------

typedef struct empresa2 	//Estrutra de dados Lista2
{
    char mail[50];
    int id;
    struct empresa2 *next;
} EMPRESA2;

EMPRESA2 *makeNodeLista2() //Make Node Lista2
{
    EMPRESA2 *nv=(EMPRESA2*)malloc(sizeof(EMPRESA2));
    nv->next=NULL;
    return (nv);
}

EMPRESA2 *insertFirstLista2(EMPRESA2 *L, EMPRESA2 *nv) //Insere no inicio da lista2
{
    nv->next=L;
    return(nv);
}

EMPRESA2 *findEmail(EMPRESA2 *L, char chave[]) //Procura por email na lista2
{
    while(L!=NULL)
    {
        if(strcmp(L->mail,chave)==0)
            return(L);
        L=L->next;
    }
    return (NULL);
}

//------------------------Grafo-------------------

typedef struct grafo //Estrutura de dados para o grafo;
{
    int id, opiniao;
    struct grafo *next;
} GRAFO;

GRAFO *makeNodeGrafo() //Make Node Grafo
{
    GRAFO *nv=(GRAFO*)malloc(sizeof(GRAFO));
    nv->next=NULL;
    return (nv);
}

GRAFO *insertFirstGrafo(GRAFO *L, GRAFO *nv) //Insere no início da lista de uma posição do grafo
{
    nv->next=L;
    return nv;
}

//---------------------Outros----------------------------------

EMPRESA *fillList(FILE *f,ARVORE **A,ARVORE **B) //Criar Árvores, Lista e ler ficheiro
{
    char line[100],*value;
    int i=0;
    f=fopen("est_dados_15_16.txt","r");
    EMPRESA *L=NULL,*nv;
    ARVORE *node,*n;
    while(fgets(line,sizeof(line),f)!=NULL)
    {
        nv=makeNodeLista();
        node=makeNodeArvore();
        n=makeNodeArvore();
        value=strtok(line,", ");
        for(i=0; i<strlen(value); i++)
        {
            value[i]=tolower(value[i]);
        }
        strcpy(nv->email_emissor,strdup(value));
        value=strtok(NULL,", ");
        nv->dia=atoi(value);
        value=strtok(NULL,", ");
        nv->mes=atoi(value);
        value=strtok(NULL,", ");
        nv->ano=atoi(value);
        value=strtok(NULL,", ");
        for(i=0; i<strlen(value); i++)
        {
            value[i]=tolower(value[i]);
        }
        strcpy(nv->email_recetor,strdup(value));
        value=strtok(NULL,", ");
        nv->opiniao=atoi(value);
        node->p=nv;
        n->p=nv;
        L=insertFirst(L,nv);
        (*A)=insertEmissor(*A,node);
        if(Balance(*A)>1)
        {
            if(Balance((*A)->fe)<0)
            {
                (*A)->fe=rotacaoEsquerda((*A)->fe);
            }
            *A=rotacaoDireita(*A);
        }
        else if(Balance(*A)<-1)
        {
            if(Balance((*A)->fd)>0)
            {
                (*A)->fd=rotacaoDireita((*A)->fd);
            }
            *A=rotacaoEsquerda(*A);
        }

        (*B)=insertRecetor(*B,n);
        if(Balance(*B)>1)
        {
            if(Balance((*B)->fe)<0)
            {
                (*B)->fe=rotacaoEsquerda((*B)->fe);
            }
            *B=rotacaoDireita(*B);
        }
        else if(Balance(*B)<-1)
        {
            if(Balance((*B)->fd)>0)
            {
                (*B)->fd=rotacaoDireita((*B)->fd);
            }
            *B=rotacaoEsquerda(*B);
        }
    }
    return L;
}

EMPRESA2 *ListGrafo(EMPRESA *L, int *tam) //Cria uma lista com todos os mails diferentes para depois construir o grafo
{
    EMPRESA2 *T=NULL, *nv1=NULL, *nv2=NULL;
    (*tam)=0;

    while(L!=NULL)
    {
        nv1 = findEmail(T,L->email_emissor);
        if(nv1==NULL)
        {
            nv2=makeNodeLista2();
            strcpy(nv2->mail,L->email_emissor);
            nv2->id=(*tam);
            T=insertFirstLista2(T,nv2);
            (*tam)++;
        }
        nv1= findEmail(T,L->email_recetor);
        if(nv1==NULL)
        {
            nv2=makeNodeLista2();
            strcpy(nv2->mail,L->email_recetor);
            nv2->id=(*tam);
            T=insertFirstLista2(T,nv2);
            (*tam)++;
        }

        L=L->next;
    }

    return (T);
}

GRAFO **Grafo(EMPRESA2 *L, int tam) //Criar grafo
{
    EMPRESA2 *aux=NULL;
    GRAFO **G=(GRAFO**)malloc ((tam+1)*sizeof(GRAFO*));
    GRAFO *nv;
    int i, lixo, opiniao, pos1, pos2;
    char str[100], *valor, emissor[50], recetor[50];
    FILE *f;

    f = fopen("est_dados_15_16.txt","r");

    if(f==NULL)
        return (NULL);

    while(fgets(str,sizeof(str),f)!=NULL)
    {
        valor = strtok(str,",");
        strcpy(emissor,valor);

        for(i=0; i<strlen(emissor); i++)
            emissor[i]=tolower(emissor[i]);

        valor = strtok(NULL,",");
        lixo = atoi(valor);

        valor = strtok(NULL,",");
        lixo = atoi(valor);

        valor = strtok(NULL,",");
        lixo = atoi(valor);

        valor = strtok(NULL,",");
        strcpy(recetor,valor);

        for(i=0; i<strlen(recetor); i++)
            recetor[i]=tolower(recetor[i]);

        valor = strtok(NULL,"\n");
        opiniao = atoi(valor);

        aux=L;
        while(aux!=NULL)
        {
            if(strcmp(aux->mail,emissor)==0)
            {
                pos1=aux->id;
                break;
            }
            aux=aux->next;
        }

        aux=L;
        while(aux!=NULL)
        {
            if(strcmp(aux->mail,recetor)==0)
            {
                pos2=aux->id;
                break;
            }
            aux=aux->next;
        }

        nv=makeNodeGrafo();
        nv->id=pos2;
        nv->opiniao=opiniao;
        G[pos1]=insertFirstGrafo(G[pos1],nv);

    }
    return (G);
}

int main()
{
    int query,segundop,i,x=1,tam=0,flag=0;
    char email[50];
    FILE *f=fopen("est_dados_15_16.txt","r");
    EMPRESA *Lista=NULL;
    ARVORE *AE=NULL,*AR=NULL;//AE ORDENADA POR EMISSOR //AR ORDENADA POR RECETOR
    Lista=fillList(f,&AE,&AR);
    EMPRESA2 *T=NULL;
    GRAFO **G=NULL;
    while(x==1)
    {
        scanf("%d",&query);
        if(query==0)
        {
            int size=0;
            ARVORE *aux=NULL;
            EMPRESA *aux2=NULL,*nv,*R=NULL;
            scanf("%d %s",&segundop,&email);
            for(i=0; i<strlen(email); i++)
            {
                email[i]=tolower(email[i]);
            }
            do
            {
                aux=findRecetorArvore(AR,email,segundop);
                if(aux!=NULL)
                {
                    aux2=findemissor(R,aux->p->email_emissor);
                    if(aux2==NULL)
                    {
                        size++;
                        nv=makeNodeLista();
                        strcpy(nv->email_emissor,aux->p->email_emissor);
                        R=insertFirst(R,nv);
                    }
                }
            }
            while(aux!=NULL);
            printf("%d\n",size);
            if(R!=NULL)
                ordenaremissor(&R);
            aux2=R;
            while(aux2!=NULL)
            {
                printf("%s\n",aux2->email_emissor);
                aux2=aux2->next;
            }
            delete_list(&R);
            reset(AR);
        }
        if(query==1)
        {
            int size=0;
            ARVORE *aux=NULL;
            EMPRESA *aux2=NULL,*nv,*R=NULL;
            scanf("%d %s",&segundop,&email);
            for(i=0; i<strlen(email); i++)
            {
                email[i]=tolower(email[i]);
            }
            do
            {
                aux=findEmissorArvore(AE,email,segundop);
                if(aux!=NULL)
                {
                    aux2=findrecetor(R,aux->p->email_recetor);
                    if(aux2==NULL)
                    {
                        size++;
                        nv=makeNodeLista();
                        strcpy(nv->email_recetor,aux->p->email_recetor);
                        R=insertFirst(R,nv);
                    }
                }
            }
            while(aux!=NULL);
            printf("%d\n",size);
            if(R!=NULL)
                ordenarrecetor(&R);
            aux2=R;
            while(aux2!=NULL)
            {
                printf("%s\n",aux2->email_recetor);
                aux2=aux2->next;
            }
            delete_list(&R);
            reset(AE);
        }
        if(query==2)
        {
            if(flag==0)
            {
                T=ListGrafo(Lista,&tam); //criar lista de todos os mails (sem repetidos)
                G=Grafo(T,tam);
                flag++;
            }
            scanf("%d",&segundop);
            EMPRESA *R=NULL, *auxE=NULL, *nv=NULL, *ver=NULL;
            EMPRESA2 *aux=T;
            GRAFO *aux2,*aux3;
            int i,c=0,cc=0,size=0;

            for(i=0; i<=tam; i++)
            {
                aux2=G[i];
                while(aux2!=NULL)
                {
                    aux3=aux2;
                    c=0;
                    cc=0;

                    while(aux3!=NULL)
                    {
                        if((aux3->opiniao>2) && (aux3->id==aux2->id))
                            c++;
                        aux3=aux3->next;
                    }
                    aux3=G[aux2->id];

                    while(aux3!=NULL)
                    {
                        if((aux3->opiniao>2) && (aux3->id==i))
                            cc++;
                        aux3=aux3->next;
                    }

                    c=min(c,cc,segundop);


                    if(c>segundop)
                    {

                        aux=T;

                        while(aux!=NULL)
                        {
                            if(aux->id==i)
                            {
                                nv=makeNodeLista();
                                strcpy(nv->email_emissor,aux->mail);
                                break;
                            }
                            aux=aux->next;
                        }

                        ver=findemissor(R,nv->email_emissor);

                        if(ver==NULL)
                        {
                            R=insertFirst(R,nv);
                            size++;
                        }

                        aux=T;

                        while(aux!=NULL)
                        {
                            if(aux->id==aux2->id)
                            {
                                nv=makeNodeLista();
                                strcpy(nv->email_emissor,aux->mail);
                                break;
                            }
                            aux=aux->next;
                        }

                        ver=findemissor(R,nv->email_emissor);

                        if(ver==NULL)
                        {
                            R=insertFirst(R,nv);
                            size++;
                        }
                    }
                    aux2=aux2->next;
                }
            }

            printf("%d\n",size);

            if(R!=NULL)
            {
                ordenaremissor(&R);
            }
            auxE=R;

            while(auxE!=NULL)
            {
                printf("%s\n",auxE->email_emissor);
                auxE=auxE->next;
            }
            delete_list(&R);

        }
    }
    return 0;
}
