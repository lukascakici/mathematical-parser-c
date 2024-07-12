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


Stack *createStack(double capacity);
int isEmpty(Stack *stack);
double pop(Stack *stack);
void push(Stack *stack, double new);
void delete(Stack *stack);
opStack *createOpStack(double capacity);
int isEmptyOpStack(opStack *stack);
char peekOpStack(opStack *stack);
char popOpStack(opStack *stack);
void pushOpStack(opStack *stack, char c);
void deleteOpStack(opStack *stack);
int getPrecedence(char operator);
char *shuntingYard(char *input);
double function(char *input, double x);



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


char *shuntingYard(char *input) {
    double length = strlen(input);
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
            case '0' ... '9':{

                char number[200] = "";
                int j = i;

                do{
                    char digit[3];
                    digit[0] = input[j];
                    digit[1] = '\0';
                    strcat(number, digit);
                    j++;

                }while(isdigit(input[j]) && j < length);
                

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
            case 'x':{

                char number[200] = "";

                if(input[i] == 'x'){

                    strcpy(number, "x");

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
            case 'e':{
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
            case 's':{
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
                    pushOpStack(opStack, 'a');
                }
            }
                break;
            case 'c':{
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
                    pushOpStack(opStack, 'b');

                }else if (strcmp(trigo3, "cot") == 0){
                    pushOpStack(opStack, 'd');

                }
            }
                break;
            case 't':{
                char trigo3[4] = "";
                int j;

                for(j = i; j < (i + 3); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(trigo3, letter);
                }

                i = j - 1;

                if (strcmp(trigo3, "tan") == 0){
                    pushOpStack(opStack, 'c');

                }
            }
                break;
            case 'a':{
                char trigo6[7] = "";
                int j;

                for(j = i; j < (i + 6); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(trigo6, letter);
                }

                i = j - 1;

                if(strcmp(trigo6, "arcsin") == 0){
                    pushOpStack(opStack, 'e');

                }else if(strcmp(trigo6, "arccos") == 0){
                    pushOpStack(opStack, 'f');

                }else if(strcmp(trigo6, "arctan") == 0){
                    pushOpStack(opStack, 'g');

                }else if(strcmp(trigo6, "arccot") == 0){
                    pushOpStack(opStack, 'h');

                }
            }
                break;
            case 'l':{
                char log[4] = "";
                int j;

                for(j = i; j < (i + 3); j++){

                    char letter[3];
                    letter[0] = input[j];
                    letter[1] = '\0';
                    strcat(log, letter);
                }

                i = j - 1;

                if (strcmp(log, "log") == 0){

                    pushOpStack(opStack, 'l');

                }
            }
                break;
            case '^':{
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
            case '+':{
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
            case '-':{
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
            case '*':{
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
            case '/':{
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
            case '(':
                pushOpStack(opStack, input[i]);
                break;
            case ')':{
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

        }else if(input[i] == 'x'){

            double x_result =  sign * x;
            push(stack, x_result);
            sign = 1;

        }else if(input[i] == 'j'){

            double e_result =  sign * 2.7182818284;
            push(stack, e_result);
            sign = 1;

        }else if(input[i] == 'a' || input[i] == 'b' || input[i] == 'c' || input[i] == 'd' || input[i] == 'e' || input[i] == 'f' || input[i] == 'g' || input[i] == 'h'){

            const double PI = 3.14159265;
            double radian = pop(stack);
            char operator = input[i];


            if(operator == 'a'){

                push(stack, sin(radian));

            }else if(operator == 'b'){

                push(stack, cos(radian));

            }else if(operator == 'c'){

                push(stack, tan(radian));

            }else if(operator == 'd'){

                push(stack, 1/tan(radian));

            }else if(operator == 'e'){

                push(stack, asin(radian));

            }else if(operator == 'f'){

                push(stack, acos(radian));

            }else if(operator == 'g'){

                push(stack, atan(radian));

            }else if(operator == 'h'){

                push(stack, atan(1/radian));

            }

        }else if(input[i] == 'l'){

            double parameter = pop(stack);
            double base = pop(stack);
            double result = log(parameter) / log(base);
            push(stack, result);

        }else if(input[i] == '-' && input[i + 1] != ' '){

            sign = -1;

        }else{
            
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

int main(){

    char arr[100] = "x*log_10(x)-6/5";
    double result = function(shuntingYard(arr), 2);
    printf("%lf", result);

    return 0;
}
