#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    int id;
    char name[50];
    float price;

    int quantity;
} Item;

void loadProducts(Item products[], int *count) {
    FILE *file = fopen("products.txt", "r");
    if (file==NULL) {
        printf("Error opening products file.\n");
        return;
    }
    while (fscanf(file, "%d %s %f", &products[*count].id, products[*count].name, &products[*count].price) != EOF) {
        products[*count].quantity = 0;
        (*count)++;
    }
    fclose(file);
}

void showProducts(Item products[], int count) {
    printf("\nAvailable Products:\n");
    for (int i = 0; i < count; i++) {
        printf("ID:%d- %s - %.2f\n", products[i].id, products[i].name, products[i].price);
    }
}

void addToCart(Item cart[], int *cartCount, Item products[], int count) {
    int id, quantity;
    printf("Enter product ID: ");
    scanf("%d", &id);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            cart[*cartCount] = products[i];
            cart[*cartCount].quantity = quantity;
            (*cartCount)++;
            printf("Product added to cart.\n");
            return;
        }
    }
    printf("Product not found.\n");
}

void removeFromCart(Item cart[], int *cartCount) {
    int id, found = 0;
    printf("Enter product ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < *cartCount; i++) {
        if (cart[i].id == id) {
            found = 1;
            for (int j = i; j < *cartCount - 1; j++) {
                cart[j] = cart[j + 1];
            }
            (*cartCount)--;
            printf("Product removed from cart.\n");
            break;
        }
    }
    if (!found) {
        printf("Product not found in cart.\n");
    }
}

void showCart(Item cart[], int cartCount,char name[]) {
    float total = 0;
    printf("\nYour Cart:\n");
    if (cartCount == 0) {
        printf("Cart is empty.\n");
        return;
    }
    for (int i = 0; i < cartCount; i++) {
        printf("%s x%d = %.2f\n", cart[i].name, cart[i].quantity, cart[i].quantity * cart[i].price);
        total += cart[i].quantity * cart[i].price;
    }
    printf("Dear %s Sir/Madam Your Total Bill : %.2f\n",name,total);
}

void saveCart(Item cart[], int cartCount) {
    FILE *file = fopen("cart.txt", "w");
    for (int i = 0; i < cartCount; i++) {
        fprintf(file, "%d %s %.2f %d\n", cart[i].id, cart[i].name, cart[i].price, cart[i].quantity);
    }
    fclose(file);
}

void loadCart(Item cart[], int *cartCount) {
    FILE *file = fopen("cart.txt", "r");
    if (file==NULL) {
        return;
    }
    while (fscanf(file, "%d %s %f %d", &cart[*cartCount].id, cart[*cartCount].name, &cart[*cartCount].price, &cart[*cartCount].quantity) != EOF) {
        (*cartCount)++;
    }
    fclose(file);
}

int main() {
    Item products[100];
    Item cart[100];
    char name[30],email[100],contact[20];
    int productCount = 0, cartCount = 0;
    int choice;
    printf("Please Enter Your Name:\n");
    fgets(name,30,stdin);
    printf("Please Enter Your Email Address:\n");
    gets(email);
    printf("Please Enter Your Contact No. :\n");
    gets(contact);

    loadProducts(products, &productCount);
    loadCart(cart, &cartCount);

    do {
        printf("\nMenu:\n");
        printf("1. Show Products\n2. Add to Cart\n3. Remove from Cart\n4. Show Cart\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showProducts(products, productCount);
                break;
            case 2:
                addToCart(cart, &cartCount, products, productCount);
                break;
            case 3:
                removeFromCart(cart, &cartCount);
                break;
            case 4:
                showCart(cart, cartCount,name);
                break;
            case 5:
                saveCart(cart, cartCount);
                printf("Cart saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
