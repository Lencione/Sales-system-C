#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief   Projeto Vendas, utilizando arquivos.
 *          PT-BR: 
 *          Programa que através de arquivo realiza um CRUD (Create, Read, Update, Delete)
 *          em arquivos com dados referente a simulação de uma venda de um produto.
 *          Nesse arquivo chamado "main", o programa simplesmente realiza a chamada de outros
 *          programas já compilados.
 *          Demais documentações encontram-se antes do prototipo das funções nos arquivos de cada programa.
 * 
 * @authors: 
 *          Wesley Lencione de Oliveira     RA 12225140
 *          Lucas Pianelli Andreotti        RA 12225225
 *          Vinicius Campos Ferreira        RA 12224916
 * 
 * @github: https://github.com/Lencione/Sales-system-C      
 */
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