#include <stdio.h>
#include "header/stack.h"

void go_through_expression(char expression[], STACK *numbers, STACK *operators);
void get_strongest_operator(char current, STACK *numbers, STACK *operators);
void get_one_operator(STACK *numbers, STACK *operators);
void calculate_expression_and_push(ITEM n1, ITEM n2, ITEM operator, STACK *numbers, STACK *operators);
void go_through_operators(STACK *numbers, STACK *operators);

int sum(int a, int b);
int subtraction(int a, int b);
int multiplication(int a, int b);
int div(int a, int b);

int is_number(char c);
int compare_strenght(char a, char b);

void create(STACK *stack);
int empty(STACK stack);
int push(ITEM x, STACK *stack);
int pop(ITEM *item, STACK *stack);
char peek(STACK *stack);
int size(STACK stack);

int main(){
	char expression[] = "4/(1+3)+2";

    STACK numbers;
    create(&numbers);

   	STACK operators;
    create(&operators);

    ITEM bottom;
    bottom.key = '$';
    push(bottom, &operators);

    go_through_expression(expression, &numbers, &operators);
    go_through_operators(&numbers, &operators);

	printf("\nA expression %s = %c", &expression, peek(&numbers));

	printf("\n\nPress ENTER key to Continue\n");
	getchar();

    return 0;
}

void go_through_expression(char expression[], STACK *numbers, STACK *operators){
    int i = 0;
    char current = expression[i];
    while(current != '\0'){
		if (current != ' '){ 
			ITEM item;
			item.key = current;
			
			if(is_number(current) == 1)
				push(item, numbers);
			else{
				if(compare_strenght(current, peek(operators)) != 1)
					get_strongest_operator(current, numbers, operators);
            
				if(current != ')')
					push(item, operators);
			}
		}
        current = expression[++i];
    }
}
 
void get_strongest_operator(char current, STACK *numbers, STACK *operators){
    if(current == ')'){
        while(peek(operators) != '(')
            get_one_operator(numbers, operators);

		ITEM abre_paranteses;
		pop(&abre_paranteses, operators);
	}
	else
        get_one_operator(numbers, operators);
}

void get_one_operator(STACK *numbers, STACK *operators){
	ITEM operator;
  	pop(&operator, operators);
  	
    ITEM n1;
    ITEM n2;
    pop(&n2, numbers);
    pop(&n1, numbers);
  
	calculate_expression_and_push(n1, n2, operator, numbers, operators);
}

void calculate_expression_and_push(ITEM n1, ITEM n2, ITEM operator, STACK *numbers, STACK *operators) {

	ITEM result;
	if (operator.key == '+')
		result.key = sum(n1.key - 48, n2.key - 48) + 48;
	else if (operator.key == '-')
		result.key = subtraction(n1.key - 48, n2.key - 48) + 48;
	else if (operator.key == '*')
		result.key = multiplication(n1.key -  48, n2.key - 48) + 48;
	else if (operator.key == '/')
		result.key = div(n1.key - 48, n2.key - 48) + 48;

	push(result, numbers);
}

void go_through_operators(STACK *numbers, STACK *operators) {
	while (peek(operators) != '$')
		get_one_operator(numbers, operators);
}

int sum(int a, int b){
    return a + b;
}

int subtraction(int a, int b){
	return a - b;
}

int multiplication(int a, int b){
	return a * b;
}

int div(int a, int b){
	return a / b;
}

int is_number(char c) {
	int as_int = c;
	if (as_int >= 48 && as_int <= 57)
		return 1;

	return 0;
}

int compare_strenght(char a, char b) {
	if (a == '(' || b == '$' || b == '(')
		return 1;
	else if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;

	return 0;
}

void create(STACK* stack) {
	stack->top = (PONT)malloc(sizeof(CELL));
	stack->bottom = stack->top;
	stack->top->next = 0;
	stack->size = 0;
}

int empty(STACK stack) {
	return (stack.top == stack.bottom);
}

int push(ITEM x, STACK *stack) {
	PONT aux;
	aux = (PONT)malloc(sizeof(CELL));
	stack->top->item = x;
	aux->next = stack->top;
	stack->top = aux;
	stack->size++;
	return 0;
}

int pop(ITEM *item, STACK *stack) {
	PONT q;
	if (empty(*stack))
		return -1;

	q = stack->top;
	stack->top = q->next;
	*item = q->next->item;
	free(q);
	stack->size--;
	return 0;
}

char peek(STACK* stack) {
	ITEM item;
	if (empty(*stack)) return -1;
	item = stack->top->next->item;
	return item.key;
}

int size(STACK stack) {
	return stack.size;
}