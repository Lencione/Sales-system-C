#include <stdio.h>
#include <stdlib.h>

typedef struct{
    unsigned int id;
    char name[20];
    int qnt;
    int value;
}Product;

typedef struct{
    unsigned int id;
    char name[50];
}Client;

typedef struct{
    unsigned int id;
    unsigned int client_id;
    unsigned int product_id;
}Order;

FILE* getClients();
FILE* getProducts();

int main(int argc, const char * argv[])
{
    FILE *clients = getClients();
    FILE *products = getProducts();
}

FILE* getClients(){
    FILE *file;
    file = fopen("Clients.txt", "rb");

    if(file == NULL){
        printf("Arquivo Clients.txt nao existente, crie-o e tente novamente!");
        system("PAUSE");
        return 1;
    }
}

FILE* getProducts(){
    FILE *file;
    file = fopen("Products.txt", "rb");

    if(file == NULL){
        printf("Arquivo Products.txt nao existente, crie-o e tente novamente!");
        system("PAUSE");
        return 1;
    }
}