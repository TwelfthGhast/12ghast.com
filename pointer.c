#include <stdio.h>

int main(void){
    int number = 1;
    int *ptrtonumber = &number;
    while(1==1){
        printf("Value of the integer 'number' as type integer\t\t=\t%d\n\n",number);
        printf("Address of the integer 'number' as type pointer\t\t=\t0x%p\n",&number);
        printf("Address of the integer 'number' as type integer\t\t=\t%d\n\n",&number);
        printf("Value of the pointer 'ptrtonumber' as type pointer\t=\t0x%p\n",ptrtonumber);
        printf("Value of the pointer 'ptrtonumber' as type integer\t=\t%d\n\n",ptrtonumber);
        printf("Address of the pointer 'ptrtonumber' as type pointer\t=\t0x%p\n",&ptrtonumber);
        printf("Address of the pointer 'ptrtonumber' as type integer\t=\t%d\n\n",&ptrtonumber);
        printf("-------------------------------------\n");
        printf("Press ENTER to print again.\n");
        getchar();
        int temp;
        scanf("%d",&temp);
        scanf("%d", temp);
        printf("-------------------------------------\n");
    }
    return 0;
}
