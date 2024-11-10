#include <stdio.h>
#include <time.h>
#include <string.h>

int main()
{
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