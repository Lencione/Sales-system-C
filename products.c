#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

// PRODUTO
typedef struct{
    int id;
    char name[20];
    int qnt;
    int value;
}Product;

// PEDIDOS
typedef struct{
    int id;
    int client_id;
    int product_id;
    int qtt;
}Order;

FILE* getProducts();
int countProducts(FILE *file);
void appendProduct(FILE *file);
void showProducts(FILE *file);
int getLastId(FILE *file);
void productRoutine(FILE *file);
FILE *deleteProduct(FILE *file);
int countOrders(FILE *file);
// FIM PRODUTO

int main(int argc, const char * argv[])
{
    FILE *productsFile = getProducts();
    productRoutine(productsFile);      
}

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
int countProducts(FILE *file){
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(Product);
}
void appendProduct(FILE *file){
    Product product;
    printf("Adicionando elemento ao arquivo:\n\n");
    printf("Digite o nome do produto: ");
    scanf("%s", product.name);
    printf("\n\nDigite quantos produtos tem no estoque: ");
    scanf("%d",&product.qnt);
    printf("\n\nDigite o preco do produto (sem virgula ex: R$10,00 = 1000): ");
    scanf("%d",&product.value);
    product.id = getLastId(file);
    fseek(file,0,SEEK_SET);
    fwrite(&product,sizeof(Product),sizeof(product)/sizeof(Product),file);
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
int getLastId(FILE *file){
    if(countProducts(file) > 0){
        fseek(file,-1 * sizeof(Product),SEEK_END);
        Product product;
        fread(&product,sizeof(Product),1,file);
        return product.id+1;
    }
    return 0;
}

void productRoutine(FILE *file){
    Product products;
    char opt = 0;
    char verify = 0;

    while(1){
        system("CLS");
        printf("-----PRODUTOS-----\n");
        printf("\nSelecione a opcao desejada:\n");
        printf("[1] Adicionar registro:\n");
        if(countProducts(file) > 0){
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
                appendProduct(file);
                break;
            case '2':
                if(countProducts(file) > 0){
                   showProducts(file);
                }
                break;
            case '3':
                if(countProducts(file) > 0){
                    file = deleteProduct(file);
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
FILE *deleteProduct(FILE *file){

    int qtt = countProducts(file);
    Product products[qtt];
    int i, error;
    int productId,found;
    char confirm;
    fseek(file,0,SEEK_SET);
    for(i = 0; i < qtt; i++){
        fread(&products[i],sizeof(Product),1,file);
    }
    while(1){
        found = -1;
        error = -1;
        system("CLS");
        showProducts(file);
        printf("Digite o ID para excluir:\n");
        scanf("%d",&productId);
        for(i = 0; i < qtt; i++){
            if(products[i].id == productId){
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
            if(productId == order.product_id){
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
                        products[i] = products[i+1];
                    }
                    qtt--;
                    fclose(file);
                    file = fopen("Products.dat","w");
                    fwrite(&products,sizeof(Product),qtt,file);
                    fclose(file);
                    printf("\n\nRegistro deletado com sucesso!\n");
                    return getProducts();
                }

            }else{
                printf("\n\nRegistro nao encontrado...\nDeseja realmente excluir um registro? (S/N)");
                while(1){
                    confirm = getch();
                    if(confirm == 's' || confirm == 'S' || confirm == 'N' || confirm == 'n'){
                        if(confirm == 'n' || confirm == 'N'){
                            return getProducts();
                        }
                        break;
                    }
                }
            }
        }
        return getProducts();
    }
}

int countOrders(FILE *file){
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(Order);
}