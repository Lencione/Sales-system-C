#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Create Product Struct
 * 
 */
typedef struct{
    int id;
    char name[20];
    int qnt;
    int value;
}Product;

/**
 * @brief Get the Products object
 * 
 * @return FILE* with pointer to Product File
 */
FILE* getProducts();

/**
 * @brief Get the Product object
 * 
 * @return Product 
 */
Product getProduct();

/**
 * @brief Get the Product object count
 * 
 * @param file: pointer to Product file
 * @return count: int
 */
int countProducts(FILE *file);

/**
 * @brief Show Products list
 * 
 * @param file: ponter to Product file
 */
void showProducts(FILE *file);


/**
 * @brief Create Client Struct
 */
typedef struct{
    int id;
    char name[20];
    int age;
}Client;

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
 * @brief Show clients list
 * 
 * @param file: pointer to Client file
 */
void showClients(FILE *file);

/**
 * @brief Get the Client object
 * 
 * @param clientParamId: -1 to show and get Client on file
 *                        id to search Client on file
 * @return Client 
 */
Client getClient(int clientParamId);

/**
 * @brief Create Order struct
 */
typedef struct{
    int id;
    int client_id;
    int product_id;
    int qtt;
}Order;

/**
 * @brief Get the Orders object
 * 
 * @return FILE* 
 */
FILE* getOrders();

/**
 * @brief Get the Orders object count
 * 
 * @param file: pointer to Order file
 * @return count: int
 */
int countOrders(FILE *file);

/**
 * @brief Get the Orders object list
 * 
 * @param file: pointer to Order File
 */
void showOrders(FILE *file);

/**
 * @brief Starts a routine of Order CRUD 
 * 
 * @param file: pointer to Order file
 */
void ordersRoutine(FILE *file);

/**
 * @brief Append new object to Order File
 * 
 * @param file: pointer to Order file
 */
void appendOrder(FILE *file);

/**
 * @brief Get the Last Id of Order File
 * 
 * @param file: pointer to Order file
 * @return last id of Order File + 1
 */
int getLastId(FILE *file);

/**
 * @brief Delete object of a Order File
 * 
 * @param file: pointer to Order file
 * @return FILE* instance of a Order file
 */
FILE *deleteOrder(FILE *file);

// MAIN
int main(int argc, const char * argv[])
{
    FILE *orders = getOrders();
    ordersRoutine(orders);
}

// PRODUTOS
FILE* getProducts(){
    FILE *file;
    file = fopen("Products.dat", "a+");

    if(file == NULL){
        printf("Ocorreu um erro ao criar/ler arquivo.");
        system("PAUSE");
        return NULL;
    }

    return file;
}

Product getProduct(int productParamId){
    FILE *products =  getProducts();
    int productId,i;
    Product product;
    int count = countProducts(products);
    productId = productParamId;
    if(productParamId == -1){
        showProducts(products);
        printf("\nDigite o ID do Produto:");
        scanf("%d", &productId);
    }
    fseek(products,0,SEEK_SET);
    for(i = 0; i < count; i++){
        fread(&product,sizeof(Product),1,products);
        if(product.id == productId){
            return product;
        }
    }
    fclose(products);
    product.id = -1;
    return product;
}
int countProducts(FILE *file){
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(Product);
}

void showProducts(FILE *file){
    system("CLS");
    Product product;
    int count = countProducts(file);
    int i;
    fseek(file,0,SEEK_SET);
    for( i = 0; i < count; i++){
        fread(&product,sizeof(Product),1,file);
        printf("[%d] - PRODUTO: %s - QUANTIDADE: %d - VALOR: R$ %.2f\n", product.id, product.name, product.qnt, (float)product.value / 10);
    }
}

// CLIENTES
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

Client getClient(int clientParamId){
    FILE *clients =  getClients();
    int clientId,i;
    Client client;
    int count = countClients(clients);
    clientId = clientParamId;
    if(clientParamId == -1){
        showClients(clients);
        printf("\nDigite o ID do CLIENTE:");
        scanf("%d", &clientId);
    }
    fseek(clients,0,SEEK_SET);
    for(i = 0; i < count; i++){
        fread(&client,sizeof(Client),1,clients);
        if(client.id == clientId){
            return client;
        }
    }
    fclose(clients);
    client.id = -1;
    return client;
}

int countClients(FILE *file){
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(Client);
}

void showClients(FILE *file){
    system("CLS");
    Client client;
    int count = countClients(file);
    int i;
    fseek(file,0,SEEK_SET);
    for( i = 0; i < count; i++){
        fread(&client,sizeof(Client),1,file);
        printf("[%d] - Cliente: %s - IDADE: %d\n", client.id, client.name, client.age);
    }
}

// PEDIDOS
FILE* getOrders(){
    FILE *file;
    file = fopen("Orders.dat", "a+");

    if(file == NULL){
        printf("Ocorreu um erro ao criar/ler arquivo.");
        system("PAUSE");
        return NULL;
    }

    return file;
}
int countOrders(FILE *file){
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(Order);
}
void showOrders(FILE *file){
    system("CLS");
    Order order;
    Client client;
    Product product;
    int count = countOrders(file);
    int i;
    float total;
    fseek(file,0,SEEK_SET);
    for( i = 0; i < count; i++){
        fread(&order,sizeof(Order),1,file);
        client = getClient(order.client_id);
        product = getProduct(order.product_id);
        total = (order.qtt * product.value) / 10;
        printf("Pedido: [%d] - CLIENTE: %s - PRODUTO: %s - Quant: %d - Total: R$%.2f\n", order.id, client.name, product.name, order.qtt, total );
    }
}

void ordersRoutine(FILE *file){
    char opt = 0;
    char verify = 0;
    FILE *clients = getClients();
    FILE *products = getProducts();
    int clientsCount = countClients(clients);
    int productsCount = countProducts(products);


    while(1){
        system("CLS");
        printf("-----PEDIDOS-----\n");
        printf("\nSelecione a opcao desejada:\n");
        if(clientsCount > 0 &&  productsCount > 0){
             printf("[1] Adicionar registro:\n");
        }else{
            printf("\n\nATENCAO: Nao existem Produtos ou Clientes cadastrados\nCadastre um e tente novamente:\n\n");
        }

        if(countOrders(file) > 0){
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
                if(countClients(clients) > 0 && countProducts(products) > 0){
                    appendOrder(file);
                    fclose(clients);
                    fclose(products);
                }
                break;
            case '2':
                if(countOrders(file) > 0){
                   showOrders(file);
                }
                break;
            case '3':
                if(countOrders(file) > 0){
                    file = deleteOrder(file);
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

void appendOrder(FILE* file){
    Order order;
    Client client;
    Product product;

    printf("Adicionando elemento ao arquivo:\n\n");
    printf("Digite o id do cliente: ");
    do{
        client = getClient(-1);
        if(client.id == -1){
            printf("\n\nCliente invalido!\n");
            Sleep(2000);
        }
    }while(client.id == -1);

    do{
        product = getProduct(-1);
        if(product.id == -1){
            printf("\n\nProduto invalido!\n");
            Sleep(2000);
        }
    }while(product.id == -1);

    system("CLS");
    printf("\nDigite a quantidade de produtos: ");
    scanf("%d", &order.qtt);
    order.client_id = client.id;
    order.product_id = product.id;
    order.id = getLastId(file);
    fseek(file,0,SEEK_SET);
    fwrite(&order,sizeof(Order),sizeof(order)/sizeof(Order),file);    
}

int getLastId(FILE *file){
    if(countOrders(file) > 0){
        fseek(file,-1 * sizeof(Order),SEEK_END);
        Order order;
        fread(&order,sizeof(Order),1,file);
        return order.id+1;
    }
    return 0;
}

FILE *deleteOrder(FILE *file){
    int qtt = countOrders(file);
    Order orders[qtt];
    int i;
    int orderId,found;
    char confirm;
    fseek(file,0,SEEK_SET);
    for(i = 0; i < qtt; i++){
        fread(&orders[i],sizeof(Order),1,file);
    }
    while(1){
        found = -1;
        system("CLS");
        showOrders(file);
        printf("Digite o ID para excluir:\n");
        scanf("%d",&orderId);
        for(i = 0; i < qtt; i++){
            if(orders[i].id == orderId){
                found = i;
                break;
            }
        }
        if(found != -1){
            printf("Tem certeza que deseja excluir esse registro?(S/N)");
            while(1){
                confirm = getch();
                if(confirm == 's' || confirm == 'S' || confirm == 'N' || confirm == 'n')
                    break;
            }
            if(confirm == 's' || confirm == 'S'){
                for(i = found; i < qtt-1; i++){
                    orders[i] = orders[i+1];
                }
                qtt--;
                fclose(file);
                file = fopen("Orders.dat","w");
                fwrite(&orders,sizeof(Order),qtt,file);
                fclose(file);
                printf("\n\nRegistro deletado com sucesso!\n");
                return getOrders();
            }

        }else{
            printf("\n\nRegistro nao encontrado...\nDeseja realmente excluir um registro? (S/N)");
             while(1){
                confirm = getch();
                if(confirm == 's' || confirm == 'S' || confirm == 'N' || confirm == 'n'){
                    if(confirm == 'n' || confirm == 'N'){
                        return getOrders();
                    }
                    break;
                }
            }
        }
    }
}