#include<iostream>
#include<stdio.h>
void Add(int *a[2]);

int main(){
int a[2][2] = {{1,2},{3,4}};
Add(a);

return 0;
}


void Add(int *a[2]){

    printf("the sum of a[1][1] + a[0][0] is %d",a[1][1]+a[0][0]);

}
