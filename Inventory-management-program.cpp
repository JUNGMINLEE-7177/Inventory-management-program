#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
    struct tm intime; //�ð����屸��ü
} Product;

Product inventory[MAX_PRODUCTS];
int product_count = 0;

int num_or_char(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return 0;  // ���ڰ� �ƴϸ� 0 ��ȯ
    }
    return 1;  // �����̸� 1 ��ȯ
}
void add_file() {
    // Open the file in "w" mode to overwrite its contents
    FILE* file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    for (int i = 0; i < product_count; i++) {
        fprintf(file, "%d %s %d %.2f %04d-%02d-%02d %02d:%02d\n",
            inventory[i].id,
            inventory[i].name,
            inventory[i].quantity,
            inventory[i].price,
            inventory[i].intime.tm_year + 1900,
            inventory[i].intime.tm_mon + 1,
            inventory[i].intime.tm_mday,
            inventory[i].intime.tm_hour,
            inventory[i].intime.tm_min);
    }
    fclose(file);
}

void load_file() {
    FILE* file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("���� ���� ����\n");
        return;
    }

    // ���Ͽ��� ��ǰ ������ �о����
    while (fscanf(file, "%d %s %d %f %d-%d-%d %d:%d",
        &inventory[product_count].id, inventory[product_count].name,
        &inventory[product_count].quantity, &inventory[product_count].price,
        &inventory[product_count].intime.tm_year, &inventory[product_count].intime.tm_mon,
        &inventory[product_count].intime.tm_mday, &inventory[product_count].intime.tm_hour,
        &inventory[product_count].intime.tm_min) != EOF) {
        inventory[product_count].intime.tm_year -= 1900;  // ���� �ʱ�ȭ
        inventory[product_count].intime.tm_mon -= 1;      // �� �ʱ�ȭ
        product_count++;
        if (product_count >= MAX_PRODUCTS) break;  // �ִ� ��ǰ ���� �����ϸ� ����
    }

    fclose(file);
    printf("��ǰ �����Ͱ� ���Ͽ��� �ε�Ǿ����ϴ�.\n");
}
void add_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("��� ������ �����մϴ�!\n");
        return;
    }

    Product new_product;
    new_product.id = product_count + 1;

    printf("��ǰ �̸�: ");
    scanf("%s", new_product.name);
    while (1) {
        printf("����: ");
        if (scanf("%d", &new_product.quantity) == 1) {
            if (new_product.quantity >= 0) break; // ��ȿ�� ����
            else printf("������ 0 �̻��̾�� �մϴ�. �ٽ� �Է��ϼ���.\n");
        }
        else {
            printf("��ȿ���� ���� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            while (getchar() != '\n'); // �Է� ���� ����
        }
    }

    // ���� �Է� ó��
    while (1) {
        printf("����: ");
        if (scanf("%f", &new_product.price) == 1) {
            if (new_product.price >= 0) break; // ��ȿ�� ����
            else printf("������ 0 �̻��̾�� �մϴ�. �ٽ� �Է��ϼ���.\n");
        }
        else {
            printf("��ȿ���� ���� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            while (getchar() != '\n'); // �Է� ���� ����
        }
    }

    time_t now = time(NULL);  // ���� �ð��� ������
    new_product.intime = *localtime(&now);  // ���� �ð��� localtime���� ��ȯ�Ͽ� ����
    inventory[product_count++] = new_product;

    printf("��ǰ�� �߰��Ǿ����ϴ�!\n");
}

void check_low() {
    printf("\n=== ��� ���� ���� ��ǰ ===\n");
    int low = 0;
    for (int i = 0; i < product_count; i++) {
        if (inventory[i].quantity < 3) {
            printf("��ǰ �̸�: %s, ����: %d\n", inventory[i].name, inventory[i].quantity);
            low = 1;
        }
    }
    if (!low) {
        printf("��� ������ ��ǰ�� �����ϴ�.\n");
    }
}

void display_only() {
    char input[50];
    int found = 0;

    printf("��ȸ�ϰ� ���� ��ǰ �̸� �Ǵ� ID�� �Է����ּ���: ");
    scanf("%s", input);

    // �Է°��� �������� Ȯ��
    if (isdigit(input[0])) {
        // ID�� �˻�
        int id = atoi(input);  // ���ڿ��� ������ ��ȯ

        if (id < 1 || id > product_count) {
            printf("��ȿ���� ���� ID�Դϴ�.\n");
            return;
        }

        printf("%d\t%s\t%d\t%.2f\t%04d-%02d-%02d %02d:%02d\n", inventory[id - 1].id, inventory[id - 1].name, inventory[id - 1].quantity, inventory[id - 1].price,
            inventory[id - 1].intime.tm_year + 1900,
            inventory[id - 1].intime.tm_mon + 1,
            inventory[id - 1].intime.tm_mday,
            inventory[id - 1].intime.tm_hour,
            inventory[id - 1].intime.tm_min);
        found = 1;
    }
    else {
        // �̸����� �˻�
        for (int i = 0; i < product_count; i++) {
            if (strcmp(inventory[i].name, input) == 0) {
                printf("%d\t%s\t%d\t%.2f\t%04d-%02d-%02d %02d:%02d\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price,
                    inventory[i].intime.tm_year + 1900,
                    inventory[i].intime.tm_mon + 1,
                    inventory[i].intime.tm_mday,
                    inventory[i].intime.tm_hour,
                    inventory[i].intime.tm_min);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("��ǰ�� ã�� �� �����ϴ�.\n");
    }
}

void display_products() {
    if (product_count == 0) {
        printf("��� ��ǰ�� �����ϴ�.\n");
        return;
    }

    printf("ID\t�̸�\t����\t����\t�ð�\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < product_count; i++) {
        printf("%d\t%s\t%d\t%.2f\t%04d-%02d-%02d %02d:%02d\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price,
            inventory[i].intime.tm_year + 1900,
            inventory[i].intime.tm_mon + 1,
            inventory[i].intime.tm_mday,
            inventory[i].intime.tm_hour,
            inventory[i].intime.tm_min);
    }
}

void update_product() {
    char input[50];
    printf("������ ��ǰ�� ID �Ǵ� �̸��� �Է��ϼ���: ");
    scanf("%s", input);

    int found = 0;

    if (num_or_char(input)) {
        int id = atoi(input);

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
    else {
        for (int i = 0; i < product_count; i++) {
            if (strcmp(inventory[i].name, input) == 0) {
                found = 1;
                printf("���ο� ����: ");
                scanf("%d", &inventory[i].quantity);
                printf("���ο� ����: ");
                scanf("%f", &inventory[i].price);
                printf("��ǰ�� �����Ǿ����ϴ�!\n");
                break;
            }
        }
        if (!found) {
            printf("��ǰ�� ã�� �� �����ϴ�.\n");
        }
    }
}

void delete_product() {
    char input[50];
    printf("������ ��ǰ�� ID �Ǵ� �̸��� �Է��ϼ���: ");
    scanf("%s", input);

    int found = 0;
    if (num_or_char(input)) {
        int id = atoi(input);

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
    else {
        for (int i = 0; i < product_count; i++) {
            if (strcmp(inventory[i].name, input) == 0) {
                found = 1;
                for (int j = i; j < product_count - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                product_count--;
                printf("��ǰ�� �����Ǿ����ϴ�!\n");
                break;
            }
        }
        if (!found) {
            printf("��ǰ�� ã�� �� �����ϴ�.\n");
        }

    }
}

int main() {
    int choice;
    load_file();

    while (1) {
        printf("-----------------------------------\n");
        check_low();
        printf("-----------------------------------\n");
        printf("\n===== ��ǰ ��� ���� ���α׷� =====\n");
        printf("1. ��ǰ �߰�\n");
        printf("2. ��ü��� ��ȸ\n");
        printf("3. Ư������ ��ȸ\n");
        printf("4. ��ǰ ����\n");
        printf("5. ��ǰ ����\n");
        printf("6. ����\n");
        printf("����: ");

        if (scanf("%d", &choice) != 1) {
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            while (getchar() != '\n'); // �Է� ���� ����
            continue; // ó������ ���ư���
        }

        switch (choice) {
        case 1:
            add_product();
            break;
        case 2:
            display_products();
            break;
        case 3:
            display_only();
            break;
        case 4:
            update_product();
            break;
        case 5:
            delete_product();
            break;
        case 6:
            printf("���α׷��� �����մϴ�.\n");
            add_file();
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
    return 0;
}