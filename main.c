#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
     char opt;

    while(1){
        system("CLS");
        printf("\n\nDigite a opcao que deseja:\n");
        printf("[1] - Produtos\n");
        printf("[2] - Clientes\n");
        printf("[3] - Pedidos\n");
        printf("[4] - Sair\n");
        while(1){
            opt = getch();
            if(opt >= 48 && opt <= 57)
                break;
        }
        switch(opt){
            case '1':
                system("products.exe");
                break;
            case '2':
                system("clients.exe");
                break;
            case '3':
                system("orders.exe");
                break;
            case '4':
                return 0;
                break;
            default:
                printf("Opcao invalida!");
                break;
        }
    }
}