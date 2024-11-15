#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
    struct tm intime; //t�ð����屸��ü
} Product;

Product inventory[MAX_PRODUCTS];
int product_count = 0;

void add_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("��� ������ �����մϴ�!\n");
        return;
    }

    Product new_product;
    new_product.id = product_count + 1;

    printf("��ǰ �̸�: ");
    scanf("%s", new_product.name);
    printf("����: ");
    scanf("%d", &new_product.quantity);
    printf("����: ");
    scanf("%f", &new_product.price);

    time_t now = time(NULL);  // ���� �ð��� ������
    new_product.intime = *localtime(&now);  // ���� �ð��� localtime���� ��ȯ�Ͽ� ����
    inventory[product_count++] = new_product;

    printf("��ǰ�� �߰��Ǿ����ϴ�!\n");
}

void display_only() {
    int id;
    printf("��ȸ�ϰ� ���� ��ǰ ID�� �Է����ּ���");
    scanf("%d", &id);

    if (id < 1 || id > product_count) {
        printf("��ȿ���� ���� ��ǰ ID�Դϴ�.\n");
        return;
    }

    printf("%d\t%s\t\t%d\t%.2f\t%04d-%02d-%02d %02d:%02d:%02d\n", inventory[id - 1].id, inventory[id - 1].name, inventory[id - 1].quantity, inventory[id - 1].price,
        inventory[id - 1].intime.tm_year + 1900,
        inventory[id - 1].intime.tm_mon + 1,
        inventory[id - 1].intime.tm_mday,
        inventory[id - 1].intime.tm_hour,
        inventory[id - 1].intime.tm_min);
    printf("-----------------------------------\n");
}

void display_products() {
    if (product_count == 0) {
        printf("��� ��ǰ�� �����ϴ�.\n");
        return;
    }

    printf("ID\t�̸�\t����\t����\t�ð�\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < product_count; i++) {
        printf("%d\t%s\t\t%d\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price, inventory[i].intime.tm_year + 1900,
            inventory[i].intime.tm_mon + 1,
            inventory[i].intime.tm_mday,
            inventory[i].intime.tm_hour,
            inventory[i].intime.tm_min);
    }
}

void update_product() {
    int id;
    printf("������ ��ǰ�� ID: ");
    scanf("%d", &id);

    if (id < 1 || id > product_count) {
        printf("��ȿ���� ���� ID�Դϴ�.\n");
        return;
    }

    printf("���ο� ����: ");
    scanf("%d", &inventory[id - 1].quantity);
    printf("���ο� ����: ");
    scanf("%f", &inventory[id - 1].price);

    printf("��ǰ�� �����Ǿ����ϴ�!\n");
}

void delete_product() {
    int id;
    printf("������ ��ǰ�� ID: ");
    scanf("%d", &id);

    if (id < 1 || id > product_count) {
        printf("��ȿ���� ���� ID�Դϴ�.\n");
        return;
    }

    for (int i = id - 1; i < product_count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    product_count--;
    printf("��ǰ�� �����Ǿ����ϴ�!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== ��ǰ ��� ���� ���α׷� =====\n");
        printf("1. ��ǰ �߰�\n");
        printf("2. ��� ��ȸ\n");
        printf("3. ��ǰ ����\n");
        printf("4. ��ǰ ����\n");
        printf("5. ����\n");
        printf("����: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add_product();
            break;
        case 2:
            display_products();
            break;
        case 3:
            update_product();
            break;
        case 4:
            delete_product();
            break;
        case 5:
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
    return 0;
}