#include <stdio.h>
#include <time.h>
#include <string.h>

int main()
{
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