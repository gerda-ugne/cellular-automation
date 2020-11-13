#include <math.h>
#include <stdio.h>

void decimalToBinary();
int binaryToDecimal();

int main(){
    decimalToBinary();
    binaryToDecimal();
}

void decimalToBinary() {
    int dec;

    printf("Please enter a decimal number to convert: ");
    scanf("%dec", &dec);

    long bin=0;
    long remainder;
    long f =1;

    while(dec !=0)
    {
        remainder = dec%2;
        bin = bin + remainder * f;
        f = f *10;
        dec = dec/2;

    }

    printf("\nThe binary number is: %ld\n\n", bin);
}

int binaryToDecimal(){
    long bin;
    printf("Enter a binary number to convert: ");
    scanf("%ld", &bin);

    long dec = 0, i = 1, remainder;
    while (bin!=0)
    {
        remainder = bin%10;
        dec = dec+remainder*i;
        i=i*2;
        bin=bin/10;


    }

    printf("\n The decimal value is : %ld\n\n",dec);

    return dec;

}
