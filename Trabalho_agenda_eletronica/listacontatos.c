Nomes: Anttonio Maccagnini e Gabriel Guedes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXIMO_CONTATOS 150
#define MAXIMO_NOME 70
#define MAXIMO_TELEFONE 35
#define ARQUIVO_CONTATOS "lista.contatos"
typedef struct {
   char nome[MAXIMO_NOME];
   char telefone[MAXIMO_TELEFONE];
} Contato;
typedef struct {
   Contato contatos[MAXIMO_CONTATOS];
   int total;
} Catalogo;
void adicionar_contato(Catalogo *catalogo, char *nome, char *telefone) {
   if (catalogo->total < MAXIMO_CONTATOS) { 
       strncpy(catalogo->contatos[catalogo->total].nome, nome, MAXIMO_NOME); 
       strncpy(catalogo->contatos[catalogo->total].telefone, telefone, MAXIMO_TELEFONE);
       printf("O contato foi adicionado com sucesso!\n");
   } else {
       printf("Catalogo cheio, nao foi possivel adicionar o contato!\n");
   }
}
void pesquisar_contato(Catalogo *catalogo, char *nome) { 
   for (int i = 0; i < catalogo->total; i++) { 
       if (strcmp(catalogo->contatos[i].nome, nome) == 0) { 
           printf("Contato encontrado: %s - %s\n", catalogo->contatos[i].nome, catalogo->contatos[i].telefone);
           return;
       }
   }
   printf("O contato nao foi encontrado!\n");
}
void excluir_contato(Catalogo *catalogo, char *nome) {
   for (int i = 0; i < catalogo->total; i++) { 
       if (strcmp(catalogo->contatos[i].nome, nome) == 0) {
           for (int j = i; j < catalogo->total - 1; j++) { 
               catalogo->contatos[j] = catalogo->contatos[j + 1]; 
           }
           catalogo->total--;
           printf("O contato foi excluido com sucesso!\n");
           return;
       }
   }
   printf("O contato nao foi encontrado.\n");
}
void salvar_contatos(Catalogo *catalogo) {
   FILE *arquivo = fopen(ARQUIVO_CONTATOS, "wb"); 
   if (arquivo != NULL) { 
       fwrite(catalogo, sizeof(Catalogo), 1, arquivo); 
       fclose(arquivo); 
       printf("Seus contatos foram salvos com sucesso!\n");
   } else {
       printf("Ocorreu um erro ao salvar os contatos.\n");
   }
}
void carregar_contatos(Catalogo *catalogo) {
   FILE *arquivo = fopen(ARQUIVO_CONTATOS, "rb"); 
   if (arquivo != NULL) {
       fread(catalogo, sizeof(Catalogo), 1, arquivo); 
       fclose(arquivo);
       printf("Contatos carregados com sucesso!\n");
   } else {
       catalogo->total = 0; 
       printf("Nenhum contato disponivel para carregar.\n");
   }
}
int main() {
   Catalogo catalogo;
   catalogo.total = 0;
   carregar_contatos(&catalogo);
   int opcao;
   char nome[MAXIMO_NOME];
   char telefone[MAXIMO_TELEFONE];
   do {
       printf("\nCatalogo de Contatos\n");
       printf("[1] Adicionar um contato\n");
       printf("[2] Consultar um contato\n");
       printf("[3] Excluir um contato\n");
       printf("[4] Salvar contatos\n");
       printf("[5] Carregar contatos\n");
       printf("[6] Sair\n");
       printf("Escolha uma opcao: ");
       scanf("%d", &opcao);
       getchar();  
       switch (opcao) {
           case 1:
               printf("Digite o nome: ");
               fgets(nome, MAXIMO_NOME, stdin);
               nome[strcspn(nome, "\n")] = '\0'; 
               printf("Digite o telefone: ");
               fgets(telefone, MAXIMO_TELEFONE, stdin);
               telefone[strcspn(telefone, "\n")] = '\0'; 
               adicionar_contato(&catalogo, nome, telefone);
               break;
           case 2:
               printf("Digite o nome: ");
               fgets(nome, MAXIMO_NOME, stdin);
               nome[strcspn(nome, "\n")] = '\0';  
               pesquisar_contato(&catalogo, nome);
               break;
           case 3:
               printf("Digite o nome: ");
               fgets(nome, MAXIMO_NOME, stdin);
               nome[strcspn(nome, "\n")] = '\0'; 
               excluir_contato(&catalogo, nome);
               break;
           case 4:
               salvar_contatos(&catalogo);
               break;
           case 5:
               carregar_contatos(&catalogo);
               break;
           case 6:
               salvar_contatos(&catalogo);
               printf("Saindo...\n");
               break;
           default:
               printf("Opcao invalida.\n");
               break;
       }
   } while (opcao != 6);
   return 0;
}
