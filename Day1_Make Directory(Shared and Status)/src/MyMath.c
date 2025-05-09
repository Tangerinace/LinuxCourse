#include <stdio.h>
#include <stdlib.h>
#include "MyMath.h"   // <-- sửa lại từ <MyMath.h> thành "MyMath.h"

double add(double a, double b){
    return  a + b;
}

double subtract(double a, double b){
    return  a - b;
}

double multiply(double a, double b){
    return a * b;
}

double divide(double a, double b){
    if(b == 0){
        printf("Error: Division by zero\n");
        return 0;
    }
    return a / b;
}
