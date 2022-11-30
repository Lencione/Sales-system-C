#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/**
 * @brief Creating Cient struct
 */
typedef struct{
    int id;
    char name[20];
    int age;
}Client;

/**
 * @brief Creating Order struct
 */
typedef struct{
    int id;
    int client_id;
    int product_id;
    int qtt;
}Order;

/**
 * @brief Get the Clients object
 * 
 * @return FILE*
 */
FILE* getClients();

/**
 * @brief Get the Clients object count
 * 
 * @param file: pointer to Client file
 * @return count: int
 */
int countClients(FILE *file);

/**
 * @brief Append new object to Client File
 * 
 * @param file: pointer to Client file
 */
void appendClient(FILE *file);

/**
 * @brief Show clients list
 * 
 * @param file: pointer to Client file
 */
void showClients(FILE *file);

/**
 * @brief Get the Last Id of Client File
 * 
 * @param file: pointer to Client file
 * @return last id of Client File + 1
 */
int getLastId(FILE *file);

/**
 * @brief Starts a routine of CRUD 
 * 
 * @param file: pointer to Client file
 */
void clientRoutine(FILE *file);

/**
 * @brief Delete object of a Client File
 * 
 * @param file: pointer to Client file
 * @return FILE* instance of a Client file
 */
FILE *deleteClient(FILE *file);

/**
 * @brief Get the Orders object count
 * 
 * @param file: pointer to Orders file
 * @return int 
 */
int countOrders(FILE *file);

/**
 * @brief Main function
 */
int main(int argc, const char * argv[])
{
    FILE *clientFile = getClients();
    clientRoutine(clientFile);      
}

FILE* getClients(){
    FILE *file;
    file = fopen("Clients.dat", "a+");

    if(file == NULL){
        printf("Ocorreu um erro ao criar/ler arquivo.");
        system("PAUSE");
        return NULL;
    }

    return file;
}
int countClients(FILE *file){
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(Client);
}
void appendClient(FILE *file){
    Client client;
    printf("Adicionando elemento ao arquivo:\n\n");
    printf("Digite o nome do cliente: ");
    scanf("%s", client.name);
    printf("\n\nDigite quantos anos o cliente tem: ");
    scanf("%d",&client.age);
    client.id = getLastId(file);
    fseek(file,0,SEEK_SET);
    fwrite(&client,sizeof(Client),sizeof(client)/sizeof(Client),file);
}

void showClients(FILE *file){
    system("CLS");
    Client client;
    int count = countClients(file);
    int i;
    fseek(file,0,SEEK_SET);
    for( i = 0; i < count; i++){
        fread(&client,sizeof(Client),1,file);
        printf("[%d] - PRODUTO: %s - IDADE: %d\n", client.id, client.name, client.age);
    }
}
int getLastId(FILE *file){
    if(countClients(file) > 0){
        fseek(file,-1 * sizeof(Client),SEEK_END);
        Client client;
        fread(&client,sizeof(Client),1,file);
        return client.id+1;
    }
    return 0;
}

void clientRoutine(FILE *file){
    Client clients;
    char opt = 0;
    char verify = 0;

    while(1){
        system("CLS");
        printf("-----CLIENTES-----\n");
        printf("\nSelecione a opcao desejada:\n");
        printf("[1] Adicionar registro:\n");
        if(countClients(file) > 0){
            printf("[2] Ler arquivo:\n");
            printf("[3] Remover registro:\n");
        }
        printf("[4] Sair:\n");
        while(1){
            opt = getch();
            if(opt >= 48 && opt <= 57)
                break;
        }
        system("CLS");
        switch (opt)
        {
            case '1':
                appendClient(file);
                break;
            case '2':
                if(countClients(file) > 0){
                   showClients(file);
                }
                break;
            case '3':
                if(countClients(file) > 0){
                    file = deleteClient(file);
                }
                break;
            case '4':
                return;
                break;
            default:
                printf("\n\nOpcao invalida!\n\n");
                break;
        }
        printf("\n\nPressione ENTER para continuar");
        while(1){
            verify = getch();
            if(verify == 13){
                break;
            }
        }
    }  
}
FILE *deleteClient(FILE *file){
    int qtt = countClients(file);
    Client clients[qtt];
    int i,error;
    int clientId,found;
    char confirm;
    fseek(file,0,SEEK_SET);
    for(i = 0; i < qtt; i++){
        fread(&clients[i],sizeof(Client),1,file);
    }
    while(1){
        found = -1;
        error = -1;
        system("CLS");
        showClients(file);
        printf("Digite o ID para excluir:\n");
        scanf("%d",&clientId);
        for(i = 0; i < qtt; i++){
            if(clients[i].id == clientId){
                found = i;
                break;
            }
        }

        FILE *orders;
        orders = fopen("Orders.dat", "r");
        Order order;
        int count = countOrders(orders);
        if(orders == NULL){
            error = 1;
        }
        
        fseek(orders,0,SEEK_SET);
        for( i = 0; i < count; i++){
            fread(&order,sizeof(Order),1,orders);
            if(clientId == order.client_id){
                error = 1;
            }
        }
        if(error == 1){
            printf("\n\nImpossivel deletar, ja existe um pedido com esse Produto.\nPrimeiro exclua esse pedido! ");
        }else{
            if(found != -1){
                printf("Tem certeza que deseja excluir esse registro?(S/N)");
                while(1){
                    confirm = getch();
                    if(confirm == 's' || confirm == 'S' || confirm == 'N' || confirm == 'n')
                        break;
                }
                if(confirm == 's' || confirm == 'S'){
                    for(i = found; i < qtt-1; i++){
                        clients[i] = clients[i+1];
                    }
                    qtt--;
                    fclose(file);
                    file = fopen("Clients.dat","w");
                    fwrite(&clients,sizeof(Client),qtt,file);
                    fclose(file);
                    printf("\n\nRegistro deletado com sucesso!\n");
                    return getClients();
                }

            }else{
                printf("\n\nRegistro nao encontrado...\nDeseja realmente excluir um registro? (S/N)");
                while(1){
                    confirm = getch();
                    if(confirm == 's' || confirm == 'S' || confirm == 'N' || confirm == 'n'){
                        if(confirm == 'n' || confirm == 'N'){
                            return getClients();
                        }
                        break;
                    }
                }
            }
        }
        return getClients();
    }
}
int countOrders(FILE *file){
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(Order);
}