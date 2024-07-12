#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

typedef struct STACK{
    int top;
    double *array;
    double capacity;
}Stack;

typedef struct OPERATORSTACK{
    int top;
    char *array;
    double capacity;
}opStack;


Stack *createStack(double capacity);//stack oluşturan fonksiyon
int isEmpty(Stack *stack);//stack'in boş olup olmadığını kontrol eden fonksiyon
double pop(Stack *stack);//stack'in tepesindeki elemanı döndüren ve silen fonksiyon
void push(Stack *stack, double new);//stack'e eleman ekleyen fonksiyon
void delete(Stack *stack);//stack'i temizleyen fonksiyon
opStack *createOpStack(double capacity);//fonksiyonları temsil eden karakterlerin tutulacağı stack'i olusturan fonksiyon
int isEmptyOpStack(opStack *stack);//stack'in boş olup olmadığını kontrol eden fonksiyon
char peekOpStack(opStack *stack);//stack'in tepesindeki elemanı döndüren fonksiyon
char popOpStack(opStack *stack);//stack'in tepesindeki elemanı döndüren ve silen fonksiyon
void pushOpStack(opStack *stack, char c);//stack'e eleman ekleyen fonksiyon
void deleteOpStack(opStack *stack);//stack'i temizleyen fonksiyon
int getPrecedence(char operator);//aritmetik isaretlerin onceligini donduren fonksiyon
char *shuntingYard(char *input);//girilen string inputu parse eden algoritma fonksiyonu
double function(char *input, double x);//parse edilen inputu ve girdi olan x'i alarak f(x) islevi goren fonksiyon



Stack* createStack(double capacity){
    Stack * stack = (Stack *) malloc(sizeof(Stack));

    if (stack == NULL){
        return NULL;
    }

    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (double *) malloc(capacity * sizeof(double));

    if (stack->array == NULL){
        return NULL;
    }

    return stack;
}

int isEmpty(Stack *stack){
    if(stack->top == -1){

        return 1;
    }else{

        return 0;
    }
}

double pop(Stack *stack){

    if (!isEmpty(stack)){
        double c = stack->array[stack->top];
        stack->top -= 1;
        return c;
    }
}

void push(Stack *stack, double new){
    stack->top = stack->top + 1;
    stack->array[stack->top] = new;
}

void delete(Stack *stack){

    while(!isEmpty(stack)){

        pop(stack);
    }
    free(stack->array);
    free(stack);
}

opStack* createOpStack(double capacity){

    opStack * stack = (opStack *) malloc(sizeof(opStack));

    if (stack == NULL){
        return NULL;
    }

    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char *) malloc(capacity * sizeof(char));

    if (stack->array == NULL){
        return NULL;
    }
    return stack;

}

int isEmptyOpStack(opStack *stack){
    if(stack->top == -1){
        return 1;
    }else{
        return 0;
    }
}

char peekOpStack(opStack *stack){
    return stack->array[stack->top];
}

char popOpStack(opStack *stack){

    if (!isEmptyOpStack(stack)){

        char c = stack->array[stack->top];
        stack->top -= 1;
        return c;
    }
}

void pushOpStack(opStack *stack, char c){

    stack->top = stack->top + 1;
    stack->array[stack->top] = c;

}

void deleteOpStack(opStack *stack){

    while(!isEmptyOpStack(stack)){

        popOpStack(stack);
    }
    free(stack->array);
    free(stack);
}

//push ederken oncelik belirlemek icin kullanicagimiz degerleri return eden fonksiyon
int getPrecedence(char operator){

    if (operator == '^') {
        return 3;
    } else if (operator == '*' || operator == '/') {
        return 2;
    } else if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '(') {
        return 0;
    } else {
        printf("precedence error\n");
        exit(0);
    }

}

//parse etme kısmı
//pushlanan harfler tamamen rastgele
char *shuntingYard(char *input) {
    double length = strlen(input); //girilen stringin uzunlugunu tutma.
    char *output = (char *) malloc(200 * sizeof(char));
    if (output == NULL) {
        printf("memory error\n");
        exit(1);
    }

    opStack *opStack = createOpStack(length);
    if (opStack == NULL) {
        printf("memory error\n");
        exit(1);
    }

    int i;
    int negativeSign = 1;
    for (i = 0; i < length; i++) {

        switch(input[i]) {
            case '0' ... '9':{ //eger karsilasilan ifade bir sayiysa:

                char number[200] = "";
                int j = i;

                do{
                    char digit[3];
                    digit[0] = input[j];
                    digit[1] = '\0';
                    strcat(number, digit);
                    j++;

                }while(isdigit(input[j]) && j < length);
                //girilen sayinin basamagini bilmedigimizden sayi haric bir sey gelene kadar devam

                i = j - 1;

                if(negativeSign == -1){

                    char tmp[200] = "-";
                    char tmp2[200] = "";
                    strcpy(tmp2, number);
                    strcat(tmp, tmp2);
                    strcpy(number, tmp);
                    negativeSign = 1;
                }
                strcat(output, number);
                strcat(output, " ");
            }
                break;
            case 'x':{ //karsilasilan ifade x ise x pushlanir. Evaluate edilirken yerine konulacak

                char number[200] = "";

                if(input[i] == 'x'){

                    strcpy(number, "x");

                }

                //negatifse
                if(negativeSign == -1){

                    char tmp[200] = "-";
                    char tmp2[200] = "";
                    strcpy(tmp2, number);
                    strcat(tmp, tmp2);
                    strcpy(number, tmp);
                    negativeSign = 1;
                }
                strcat(output, number);
                strcat(output, " ");
            }
                break;
            case 'e':{ //e karakteriyle karsilasirsa j harfi pushlanir.
                char number[200] = "";

                if(input[i] == 'e'){

                    strcpy(number, "j");
                }

                if(negativeSign == -1){

                    char tmp[200] = "-";
                    char tmp2[200] = "";
                    strcpy(tmp2, number);
                    strcat(tmp, tmp2);
                    strcpy(number, tmp);
                    negativeSign = 1;
                }
                strcat(output, number);
                strcat(output, " ");
            }
                break;
            case 's':{ //eger s harfi ile karsilasilirsa devamindaki 2 harfe bakilir. eger sin kelimesi olusursa
                char trigo3[4] = "";
                int j;

                for(j = i; j < (i + 3); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(trigo3, letter);
                }

                i = j - 1;

                if (strcmp(trigo3, "sin") == 0){
                    pushOpStack(opStack, 'a'); // a harfi push edilir.
                }
            }
                break;
            case 'c':{ //eger c harfi ile karsilasilirsa devamindaki 2 harfe bakilir.
                char trigo3[4] = "";
                int j;

                for(j = i; j < (i + 3); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(trigo3, letter);
                }

                i = j - 1;

                if (strcmp(trigo3, "cos") == 0){
                    pushOpStack(opStack, 'b'); //cos olusursa b

                }else if (strcmp(trigo3, "cot") == 0){
                    pushOpStack(opStack, 'd'); //cot olusursa d pushlanır

                }
            }
                break;
            case 't':{ //eger s harfi ile karsilasilirsa devamindaki 2 harfe bakilir.
                char trigo3[4] = "";
                int j;

                for(j = i; j < (i + 3); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(trigo3, letter);
                }

                i = j - 1;

                if (strcmp(trigo3, "tan") == 0){ //tan olusursa c pushlanır
                    pushOpStack(opStack, 'c');

                }
            }
                break;
            case 'a':{ //eger a harfi ile karsilasilirsa devamindaki 5 harfe bakilir.
                char trigo6[7] = "";
                int j;

                for(j = i; j < (i + 6); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(trigo6, letter);
                }

                i = j - 1;

                if(strcmp(trigo6, "arcsin") == 0){ //arcsin olusursa e pushlanır
                    pushOpStack(opStack, 'e');

                }else if(strcmp(trigo6, "arccos") == 0){ //arccos olusursa f pushlanır
                    pushOpStack(opStack, 'f');

                }else if(strcmp(trigo6, "arctan") == 0){ //arctan olusursa g pushlanır
                    pushOpStack(opStack, 'g');

                }else if(strcmp(trigo6, "arccot") == 0){ //arccot olusursa h pushlanır
                    pushOpStack(opStack, 'h');

                }
            }
                break;
            case 'l':{ //eger a harfi ile karsilasilirsa devamindaki 5 harfe bakilir.
                char log[4] = "";
                int j;

                for(j = i; j < (i + 3); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(log, letter);
                }

                i = j - 1;

                if (strcmp(log, "log") == 0){ //log olusursa l pushlanır

                    pushOpStack(opStack, 'l');

                }
            }
                break;
            case '^':{ //exp isareti
                if(isEmptyOpStack(opStack) || (getPrecedence(input[i]) > getPrecedence(peekOpStack(opStack)))){

                    pushOpStack(opStack, input[i]);

                }else{
                    while((!isEmptyOpStack(opStack) && getPrecedence(input[i]) <= getPrecedence(peekOpStack(opStack))) && peekOpStack(opStack) != '('){

                        char popped[3];
                        popped[0] = popOpStack(opStack);
                        popped[1] = ' ';
                        popped[2] = '\0';
                        strcat(output, popped);

                    }
                    pushOpStack(opStack, input[i]);
                }
            }
                break;
            case '+':{ //toplam sembolu
                if(isEmptyOpStack(opStack) || (getPrecedence(input[i]) > getPrecedence(peekOpStack(opStack)))){

                    pushOpStack(opStack, input[i]);

                }else{
                    while((!isEmptyOpStack(opStack) && getPrecedence(input[i]) <= getPrecedence(peekOpStack(opStack))) && peekOpStack(opStack) != '('){

                        char popped[3];
                        popped[0] = popOpStack(opStack);
                        popped[1] = ' ';
                        popped[2] = '\0';
                        strcat(output, popped);

                    }
                    pushOpStack(opStack, input[i]);
                }
            }
                break;
            case '-':{ //cikarma islemi
                if(input[i-1] == '('){
                    negativeSign = -1;

                }else if(isEmptyOpStack(opStack) || (getPrecedence(input[i]) > getPrecedence(peekOpStack(opStack)))){

                    pushOpStack(opStack, input[i]);

                }else{
                    while((!isEmptyOpStack(opStack) && getPrecedence(input[i]) <= getPrecedence(peekOpStack(opStack))) && peekOpStack(opStack) != '('){

                        char popped[3];
                        popped[0] = popOpStack(opStack);
                        popped[1] = ' ';
                        popped[2] = '\0';
                        strcat(output, popped);

                    }
                    pushOpStack(opStack, input[i]);
                }
            }
                break;
            case '*':{ //carpma islemi
                if(isEmptyOpStack(opStack) || (getPrecedence(input[i]) > getPrecedence(peekOpStack(opStack)))){

                    pushOpStack(opStack, input[i]);

                }else{
                    while((!isEmptyOpStack(opStack) && getPrecedence(input[i]) <= getPrecedence(peekOpStack(opStack))) && peekOpStack(opStack) != '('){

                        char popped[3];
                        popped[0] = popOpStack(opStack);
                        popped[1] = ' ';
                        popped[2] = '\0';
                        strcat(output, popped);

                    }
                    pushOpStack(opStack, input[i]);
                }
            }
                break;
            case '/':{ //bolme islemi
                if(isEmptyOpStack(opStack) || (getPrecedence(input[i]) > getPrecedence(peekOpStack(opStack)))){

                    pushOpStack(opStack, input[i]);

                }else{
                    while((!isEmptyOpStack(opStack) && getPrecedence(input[i]) <= getPrecedence(peekOpStack(opStack))) && peekOpStack(opStack) != '('){

                        char popped[3];
                        popped[0] = popOpStack(opStack);
                        popped[1] = ' ';
                        popped[2] = '\0';
                        strcat(output, popped);

                    }
                    pushOpStack(opStack, input[i]);
                }
            }
                break;
            case '(': //ac parantez, her zaman pushlanir
                pushOpStack(opStack, input[i]);
                break;
            case ')':{ //kapa parantez
                while(peekOpStack(opStack) != '('){

                    char popped[3];
                    popped[0] = popOpStack(opStack);
                    popped[1] = ' ';
                    popped[2] = '\0';
                    strcat(output, popped);
                }
                popOpStack(opStack);

                char p = peekOpStack(opStack);
                if(p == 'a' || p == 'b' || p == 'c' || p == 'd' || p == 'e' || p == 'f' || p == 'g' || p == 'h' || p == 'l'){

                    char popped[3];
                    popped[0] = popOpStack(opStack);
                    popped[1] = ' ';
                    popped[2] = '\0';
                    strcat(output, popped);
                }
            }
                break;
        }
    }

    while(!isEmptyOpStack(opStack)){

        char popped[3];
        popped[0] = popOpStack(opStack);
        popped[1] = ' ';
        popped[2] = '\0';
        strcat(output, popped);
    }
    deleteOpStack(opStack);

    return output;
}

//postfix ifadeyi evaluate eden fonksiyon
double function(char *input, double x){

    double sign = 1;
    double length = strlen(input);
    Stack * stack = createStack(200);

    if (stack == NULL){
        printf("memory error\n");
        exit(0);
    }

    int i;
    for (i = 0; i < length; i++){
        if(input[i] == ' '){
            //bosluklarda islem yapma
        }else if(isdigit(input[i])){

            char number[100] = "";
            int j = i;
            do{
                strncat(number, &input[j], 1);
                j++;
            }while(isdigit(input[j]) && j < length);

            i = j;
            double tmp = sign * atoi(number);
            push(stack, tmp);
            sign = 1;

        }else if(input[i] == 'x'){ //x gelirse girdi olarak verilen degeri pushla

            double x_result =  sign * x;
            push(stack, x_result);
            sign = 1;

        }else if(input[i] == 'j'){ //j gelirse euler sayisi degerini pushla

            double e_result =  sign * 2.7182818284;
            push(stack, e_result);
            sign = 1;

        }else if(input[i] == 'a' || input[i] == 'b' || input[i] == 'c' || input[i] == 'd' || input[i] == 'e' || input[i] == 'f' || input[i] == 'g' || input[i] == 'h'){

            const double PI = 3.14159265;
            double radian = pop(stack);
            char operator = input[i];


            if(operator == 'a'){ //a gelirse sin

                push(stack, sin(radian));

            }else if(operator == 'b'){ //b gelirse cos

                push(stack, cos(radian));

            }else if(operator == 'c'){ //c gelirse tan

                push(stack, tan(radian));

            }else if(operator == 'd'){ // d gelirse 1/tan

                push(stack, 1/tan(radian));

            }else if(operator == 'e'){ //e gelirse arcsin

                push(stack, asin(radian));

            }else if(operator == 'f'){ //f gelirse arccos

                push(stack, acos(radian));

            }else if(operator == 'g'){ //g gelirse arctan

                push(stack, atan(radian));

            }else if(operator == 'h'){ //h gelirse arccot

                push(stack, atan(1/radian));

            }//pop edilen sayisal degerle hesaplanıp push edilir.

        }else if(input[i] == 'l'){ // l gelirse logaritma hesabi yapabilmek icin 2 tane deger pop edilir

            double parameter = pop(stack); //ilk pop edilen deger daha sonra konan deger olacagi icin pay kismina
            double base = pop(stack); //ikinci pop edilen deger once koyulan deger olup paydaya yazilir
            double result = log(parameter) / log(base);
            push(stack, result);

        }else if(input[i] == '-' && input[i + 1] != ' '){

            sign = -1;

        }else{
            //aritmetik islemler
            double operand1 = pop(stack);
            double operand2 = pop(stack);
            char operator = input[i];

            if(operator == '+'){

                push(stack, operand2 + operand1);

            }else if(operator == '-'){

                push(stack, operand2 - operand1);

            }else if(operator == '*'){

                push(stack, operand2 * operand1);

            }else if(operator == '/'){

                push(stack, operand2 / operand1);

            }else if(operator == '^'){

                push(stack, pow(operand2, operand1));

            }
        }
    }

    double ret = pop(stack);
    delete(stack);
    free(input);
    return ret;
}

int bisection(){

    char arr[100];

    printf("Enter the expression: ");
    scanf("%s", arr);

    double a = 0;
    double b = 0;
    double error = 0;
    double c, cOld;
    int i = 0;

    printf("Input Interval(a b): ");
    scanf("%lf %lf",&a,&b);

    double epsilon;
    printf("Enter the value of epsilon: ");
    scanf("%lf", &epsilon);

    if((function(shuntingYard(arr), a) * function(shuntingYard(arr), b)) > 0){
        printf("Invalid Interval Exit!");
        exit(1);

    }else if(function(shuntingYard(arr), a) == 0 || function(shuntingYard(arr), b) == 0){

        printf("Root is one of interval values. Root is %lf\n",function(shuntingYard(arr), a) == 0 ? a:b);
        exit(0);

    }
    printf("Ite\ta\t\t\tb\t\t\tc\t\t\tf(c)\t\terror\n");

    do{
        cOld = c;
        c = (a + b) / 2; //yariya bolme methodu icin iki nokta toplanip yariya bolunur
        printf("%2d\t%4.6lf\t%4.6lf\t%4.6lf\t%4.6lf\t", i++, a, b, c, function(shuntingYard(arr), c));
        if(function(shuntingYard(arr), c) == 0){
            printf("Root is %4.6lf\n",c);

        }else if ((function(shuntingYard(arr), a) * function(shuntingYard(arr), c)) < 0){
            b = c; //yeni uretilen deger b ile ayni isaretliyse b'nin yerine yazilir.

        }else{
            a = c; //yeni uretilen deger b ile ayni isaretli degilse a'nin yerine yazilir.
        }
        error = fabs(c - cOld); //c degerleri arasindaki fark error olarak hesaplanır

        if(i == 1){
            printf("----\n");

        }else{
            printf("%4.6lf\n", error);
        }
    } while(error > epsilon);
    printf("Approximate Root is %4.6lf\n", c);
    return 0;
}


int main(){

    char arr[100] = "x*log_10(x)-6/5";
    double result = function(shuntingYard(arr), 2);
    printf("%lf", result);

    return 0;
}