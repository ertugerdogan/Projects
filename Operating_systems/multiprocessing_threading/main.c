#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX_ITEMS 10
#define MAX_ORDERS 100

int ID = 1;
int Product_ID = 1;
int ordered_Items_counter = 0;

typedef struct {
    int product_ID;
    double product_Price;
    int product_Quantity;
    int initial_quantity;
} Product;

Product createProduct() {
    Product product;
    product.product_ID = Product_ID;
    Product_ID++;
    double dollar=(rand() % 201);
    double cent=(rand() % 100);
    product.product_Price = dollar+cent/100.00 ;
    product.product_Quantity = (rand() % 11); 
    product.initial_quantity = product.product_Quantity;
    return product;
}

Product productss[5];

typedef struct {
    int customer_ID;
    double customer_Balance;
    double initial_balance;
    Product ordered_Items[MAX_ITEMS];
    Product purchased_Items[MAX_ITEMS];
    int ordered_items;
} Customer;

Customer createCustomer() {
    Customer customer;
    customer.customer_ID = ID;
    ID++;
    customer.customer_Balance = (double)(rand() % 201); 
    customer.initial_balance = customer.customer_Balance;
    customer.ordered_items = ordered_Items_counter;
    return customer;
}

typedef struct {
    int customer_ID;
    int product_ID;
    int quantity;
} OrderInfo;

OrderInfo all_orders[MAX_ORDERS];
int num_orders = 0;

OrderInfo all_purchases[MAX_ORDERS];
int num_purchases = 0;

void order_product(Customer* customer, Product* product, int quantity) {
    // Order
    OrderInfo order;
    order.customer_ID = customer->customer_ID;
    order.product_ID = product->product_ID;
    order.quantity = quantity;
    all_orders[num_orders++] = order;

    if (quantity <= product->product_Quantity && customer->customer_Balance >= product->product_Price * quantity) {
        // Buy
        customer->ordered_Items[customer->ordered_items++] = *product;
        product->product_Quantity -= quantity;
        customer->customer_Balance -= product->product_Price * quantity;

        OrderInfo purchase;
        purchase.customer_ID = customer->customer_ID;
        purchase.product_ID = product->product_ID;
        purchase.quantity = quantity;
        all_purchases[num_purchases++] = purchase;

        printf("Success! Customer%d(%d,%d) paid $%.2f for each.\n", customer->customer_ID,product->product_ID, quantity, product->product_Price);
    } else {
           if (quantity > product->product_Quantity) {
            printf("Customer%d(%d,%d) fail! Only %d left in stock.\n",customer->customer_ID,product->product_ID, quantity,  product->product_Quantity);
          }
         else if (customer->customer_Balance < product->product_Price * quantity) {
            printf("Customer%d(%d,%d) fail! Insufficient funds.\n",customer->customer_ID,product->product_ID, quantity);
    }
    }
}

void* customer_thread(void* arg) {
    Customer* customer = (Customer*)arg;
    
    int i = rand() % 5; 
    int j = rand() % 4;
    j++; 
    for(int k=0;k<j;k++){
    int quantity = rand() % 11;
    if(quantity==0){
        quantity++;
    }
    order_product(customer, &productss[k], quantity);
    }
    return NULL;
}

void print_products(int count) {
    printf("Initial products:\n");
    printf("Product ID   Quantity   Price\n");
    for (int i = 0; i < count; i++) {
        Product product = productss[i];
        printf("%d %d %.2f\n", product.product_ID, product.initial_quantity, product.product_Price);
    }
 
    printf("Updated Products:\n");
    printf("Product ID   Quantity    Price\n");
    for (int i = 0; i < count; i++) {
        Product product = productss[i];
        printf("%d %d %.2f\n", product.product_ID, product.product_Quantity, product.product_Price);
    }
}

int main() {
    srand(time(0)); 

    pthread_t customer_threads[3]; 
    Customer customers[3];
    productss[0] = createProduct();
    productss[1] = createProduct();
    productss[2] = createProduct();
    productss[3] = createProduct();
    productss[4] = createProduct();

    for (int i = 0; i < 3; i++) {
        customers[i] = createCustomer();
        pthread_create(&customer_threads[i], NULL, customer_thread, (void*)&customers[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    for (int i = 0; i < 3; i++) {
        Customer customer = customers[i];
        printf("\nCustomer %d ------- \n Initial Balance: %.2f$\n  Updated Balance: %.2f$\n", i + 1, customer.initial_balance, customer.customer_Balance);

        for (int j = 0; j < num_orders; j++) {
            OrderInfo order = all_orders[j];

            if (order.customer_ID == i + 1) {
                printf("Ordered products:");
                printf("Customer ID: %d, Product ID: %d, Quantity: %d\n", order.customer_ID, order.product_ID, order.quantity);
            }
        }

        for (int j = 0; j < num_orders; j++) {
            OrderInfo purchase = all_purchases[j];
            if (purchase.customer_ID == i + 1) {
                printf("Purchased products:");
                printf("Customer ID: %d, Product ID: %d, Quantity: %d\n", purchase.customer_ID, purchase.product_ID, purchase.quantity);
            }
        }
    }

    print_products(5);

    return 0;
}
