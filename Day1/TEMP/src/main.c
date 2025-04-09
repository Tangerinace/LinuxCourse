#include <stdio.h>
#include <MyMath.h>

int main(){
    printf("Addition : 5+3 = %.2f\n",add(5, 3));
    printf("Subtraction : 5-3 = %.2f\n",subtract(5, 3));
    printf("Multiplication: 5*3 = %.2f\n",multiply(5, 3));
    printf("Division : 5/3 = %.2f\n",divide(5, 3));

    return 0;
    
}
