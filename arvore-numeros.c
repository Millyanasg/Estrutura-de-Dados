#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef enum { F, T } boolean;

typedef struct No {
	int dado;
	struct No *ladoA;
	struct No *ladoB;
} No;

typedef struct Tronco {
	struct Tronco *antes;
	char *str; 
} Tronco;

struct No* novoNo(int dado)
{
    struct No* no = malloc(sizeof(struct No));
    no->dado = dado;
    no->ladoA = no->ladoB = NULL;
    return no;
}

void exibirTronco(Tronco *p) {
	if(p == NULL) {
		return;
	}
	
	exibirTronco(p->antes);
	printf("%s", p->str);
}

void exibirArvore(No *folha, Tronco *antes, boolean eladoA)
{
	if(folha == NULL) {
		return;
	}
	
	char *string_antes = "    ";
	Tronco *tronco = (Tronco*) malloc(sizeof(Tronco));
	tronco->antes = antes;
	tronco->str = string_antes;
	
	exibirArvore(folha->ladoB, tronco, T);
	
	if(antes == NULL) {
		tronco->str = "———";
	} else if(eladoA == T) {
		tronco->str = ".———";
		string_antes = "   |";
	} else {
		tronco->str = "`———";
        antes->str = string_antes;
	}
	
	exibirTronco(tronco);
	printf(" %d\n", folha->dado);
	
	if(antes) {
		antes->str = string_antes;
	}
	tronco->str = "   |";
	
	exibirArvore(folha->ladoA, tronco, F);
}

void preOrdem(No* folha) {
	if(folha) {
		printf("%d \t", folha->dado);
		preOrdem(folha->ladoA);
		preOrdem(folha->ladoB);
	}
}

int main() {
	setlocale(LC_ALL,"Portuguese");
	
    //inicio do desenho
	No *folha = novoNo(2);
	folha->ladoB = novoNo(5);
	folha->ladoA = novoNo(1);
	folha->ladoA->ladoA = novoNo(0);
	folha->ladoA->ladoA->ladoA = novoNo(7);
	folha->ladoB->ladoA = novoNo(5);
	folha->ladoB->ladoA->ladoA = novoNo(8);
	folha->ladoB->ladoA->ladoB = novoNo(1);
	folha->ladoB->ladoA->ladoB->ladoA = novoNo(5);
	exibirArvore(folha, NULL, F);
	//fim do desenho
	
	printf("\n Busca pre-ordem : \n");
	preOrdem(folha);
}


