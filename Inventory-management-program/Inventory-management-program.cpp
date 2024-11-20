#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
    struct tm intime; //t시간저장구조체
} Product;

Product inventory[MAX_PRODUCTS];
int product_count = 0;

void add_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("재고 공간이 부족합니다!\n");
        return;
    }

    Product new_product;
    new_product.id = product_count + 1;

    printf("상품 이름: ");
    scanf("%s", new_product.name);
    printf("수량: ");
    scanf("%d", &new_product.quantity);
    printf("가격: ");
    scanf("%f", &new_product.price);

    time_t now = time(NULL);  // 현재 시간을 가져옴
    new_product.intime = *localtime(&now);  // 현재 시간을 localtime으로 변환하여 저장
    inventory[product_count++] = new_product;

    printf("상품이 추가되었습니다!\n");
}

void display_only() {
    int id;
    printf("조회하고 싶은 상품 ID를 입력해주세요");
    scanf("%d", &id);

    if (id < 1 || id > product_count) {
        printf("유효하지 않은 상품 ID입니다.\n");
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
        printf("재고에 상품이 없습니다.\n");
        return;
    }

    printf("ID\t이름\t수량\t가격\t시간\n");
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
    printf("수정할 상품의 ID: ");
    scanf("%d", &id);

    if (id < 1 || id > product_count) {
        printf("유효하지 않은 ID입니다.\n");
        return;
    }

    printf("새로운 수량: ");
    scanf("%d", &inventory[id - 1].quantity);
    printf("새로운 가격: ");
    scanf("%f", &inventory[id - 1].price);

    printf("상품이 수정되었습니다!\n");
}

void delete_product() {
    int id;
    printf("삭제할 상품의 ID: ");
    scanf("%d", &id);

    if (id < 1 || id > product_count) {
        printf("유효하지 않은 ID입니다.\n");
        return;
    }

    for (int i = id - 1; i < product_count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    product_count--;
    printf("상품이 삭제되었습니다!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== 상품 재고 관리 프로그램 =====\n");
        printf("1. 상품 추가\n");
        printf("2. 재고 조회\n");
        printf("3. 상품 수정\n");
        printf("4. 상품 삭제\n");
        printf("5. 종료\n");
        printf("선택: ");
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
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}