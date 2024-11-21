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
    struct tm intime; //시간저장구조체
} Product;

Product inventory[MAX_PRODUCTS];
int product_count = 0;

int num_or_char(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return 0;  // 숫자가 아니면 0 반환
    }
    return 1;  // 숫자이면 1 반환
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
        printf("파일 열기 실패\n");
        return;
    }

    // 파일에서 상품 정보를 읽어오기
    while (fscanf(file, "%d %s %d %f %d-%d-%d %d:%d",
        &inventory[product_count].id, inventory[product_count].name,
        &inventory[product_count].quantity, &inventory[product_count].price,
        &inventory[product_count].intime.tm_year, &inventory[product_count].intime.tm_mon,
        &inventory[product_count].intime.tm_mday, &inventory[product_count].intime.tm_hour,
        &inventory[product_count].intime.tm_min) != EOF) {
        inventory[product_count].intime.tm_year -= 1900;  // 연도 초기화
        inventory[product_count].intime.tm_mon -= 1;      // 월 초기화
        product_count++;
        if (product_count >= MAX_PRODUCTS) break;  // 최대 상품 수에 도달하면 종료
    }

    fclose(file);
    printf("상품 데이터가 파일에서 로드되었습니다.\n");
}
void add_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("재고 공간이 부족합니다!\n");
        return;
    }

    Product new_product;
    new_product.id = product_count + 1;

    printf("상품 이름: ");
    scanf("%s", new_product.name);
    while (1) {
        printf("수량: ");
        if (scanf("%d", &new_product.quantity) == 1) {
            if (new_product.quantity >= 0) break; // 유효한 수량
            else printf("수량은 0 이상이어야 합니다. 다시 입력하세요.\n");
        }
        else {
            printf("유효하지 않은 입력입니다. 숫자를 입력하세요.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
        }
    }

    // 가격 입력 처리
    while (1) {
        printf("가격: ");
        if (scanf("%f", &new_product.price) == 1) {
            if (new_product.price >= 0) break; // 유효한 가격
            else printf("가격은 0 이상이어야 합니다. 다시 입력하세요.\n");
        }
        else {
            printf("유효하지 않은 입력입니다. 숫자를 입력하세요.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
        }
    }

    time_t now = time(NULL);  // 현재 시간을 가져옴
    new_product.intime = *localtime(&now);  // 현재 시간을 localtime으로 변환하여 저장
    inventory[product_count++] = new_product;

    printf("상품이 추가되었습니다!\n");
}

void check_low() {
    printf("\n=== 재고 부족 예상 상품 ===\n");
    int low = 0;
    for (int i = 0; i < product_count; i++) {
        if (inventory[i].quantity < 3) {
            printf("상품 이름: %s, 수량: %d\n", inventory[i].name, inventory[i].quantity);
            low = 1;
        }
    }
    if (!low) {
        printf("재고가 부족할 상품이 없습니다.\n");
    }
}

void display_only() {
    char input[50];
    int found = 0;

    printf("조회하고 싶은 상품 이름 또는 ID를 입력해주세요: ");
    scanf("%s", input);

    // 입력값이 숫자인지 확인
    if (isdigit(input[0])) {
        // ID로 검색
        int id = atoi(input);  // 문자열을 정수로 변환

        if (id < 1 || id > product_count) {
            printf("유효하지 않은 ID입니다.\n");
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
        // 이름으로 검색
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
        printf("상품을 찾을 수 없습니다.\n");
    }
}

void display_products() {
    if (product_count == 0) {
        printf("재고에 상품이 없습니다.\n");
        return;
    }

    printf("ID\t이름\t수량\t가격\t시간\n");
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
    printf("수정할 상품의 ID 또는 이름을 입력하세요: ");
    scanf("%s", input);

    int found = 0;

    if (num_or_char(input)) {
        int id = atoi(input);

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
    else {
        for (int i = 0; i < product_count; i++) {
            if (strcmp(inventory[i].name, input) == 0) {
                found = 1;
                printf("새로운 수량: ");
                scanf("%d", &inventory[i].quantity);
                printf("새로운 가격: ");
                scanf("%f", &inventory[i].price);
                printf("상품이 수정되었습니다!\n");
                break;
            }
        }
        if (!found) {
            printf("상품을 찾을 수 없습니다.\n");
        }
    }
}

void delete_product() {
    char input[50];
    printf("삭제할 상품의 ID 또는 이름을 입력하세요: ");
    scanf("%s", input);

    int found = 0;
    if (num_or_char(input)) {
        int id = atoi(input);

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
    else {
        for (int i = 0; i < product_count; i++) {
            if (strcmp(inventory[i].name, input) == 0) {
                found = 1;
                for (int j = i; j < product_count - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                product_count--;
                printf("상품이 삭제되었습니다!\n");
                break;
            }
        }
        if (!found) {
            printf("상품을 찾을 수 없습니다.\n");
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
        printf("\n===== 상품 재고 관리 프로그램 =====\n");
        printf("1. 상품 추가\n");
        printf("2. 전체재고 조회\n");
        printf("3. 특정으로 조회\n");
        printf("4. 상품 수정\n");
        printf("5. 상품 삭제\n");
        printf("6. 종료\n");
        printf("선택: ");

        if (scanf("%d", &choice) != 1) {
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
            continue; // 처음으로 돌아가기
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
            printf("프로그램을 종료합니다.\n");
            add_file();
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}