#include<stdio.h>
#include "header1.h"
int main()
{
    printf("\t\t\t********************************************\n");
    printf("\t\t\t*****");
    printf("\t\t*TYPING TUTOR*");
    printf("\t\t****\n");
    printf("\t\t\t********************************************\n");
    char name[20];
    int choice;
    printf("Enter your name: ");
    gets(name);
    menu(name);
    return 0;
}




