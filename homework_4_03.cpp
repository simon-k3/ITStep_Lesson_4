#include <cstdio>
#include <cstring>

const int SIZE = 10;

int stack1[SIZE], stack2[SIZE], max1[SIZE], max2[SIZE];
int head1 = 0, head2 = 0;


int top(int stack[], int* head) {
	if (*head <= 0) {
		printf("Stack underflow!!!\n");
	} 
	return stack[*head - 1];
}

void push(int stack[], int max[], int* head, int x) {
	if (*head >= SIZE) {
		printf("Stack overflow!!!\n");
		return;
	}
	stack[*head] = x;
	if (x > max[*head - 1]) {
		max[*head] = x;
	} else {
		max[*head] = max[*head - 1];
	}
	++*head;
}

int pop(int stack[], int* head) {
	if (*head <= 0) {
		printf("Stack underflow!!!\n");
		return 0;
	}
	return stack[(*head)-- - 1];
}

void enqueue(int x) {
	push(stack1, max1, &head1, x);
}

int dequeue() {
	if (head2 <= 0) {
		if (head1 <= 0) {
			printf("The queue is empty!!!\n");
		} else {
			while (head1 > 0) {
				push(stack2, max2, &head2, pop(stack1, &head1));
			}
		}
	}
	return pop(stack2, &head2);
}

int head() {
	if (head2 <= 0) {
		if (head1 <= 0) {
			printf("The queue is empty!!!\n");
		} else {
			while (head1 > 0) {
				push(stack2, max2, &head2, pop(stack1, &head1));
			}
		}
	}
	return top(stack2, &head2);
}

int tail() {
	if (head1 <= 0) {
		if (head2 <= 0) {
			printf("The queue is empty!!!\n");
		} else {
			while (head2 > 0) {
				push(stack1, max1, &head1, pop(stack2, &head2));
			}
		}
	}
	return top(stack1, &head1);
}

void print(int stack[], int* head) {
	for (int i = 0; i < *head; ++i) {
		printf("%i ", stack[i]);
	}
	printf("\n");
}

int getMax() {
	if (head1 <= 0 && head2 <= 0) {
		printf("Stack underflow!!!\n");
	} else if (head1 > SIZE && head2 > SIZE) {
		printf("Stack overflow!!!\n");
	} else if (head1 <= 0 || head1 > SIZE) {
		return max2[head2 - 1];
	} else if (head2 <= 0 || head2 > SIZE) {
		return max1[head1 - 1];
	} else if (max1[head1 - 1] > max2[head2 - 1]) {
		return max1[head1 - 1];
	} else {
		return max2[head2 - 1];
	}
}

enum Command {
	HEAD = 0, TAIL = 1, ENQUEUE = 2, DEQUEUE = 3, 
	EXIT = 4, GETMAX = 5, PRINT1 = 6, PRINT2 = 7, UNKNOWN = -1
};


int main(int argc, char** argv) {
	printf("Use the following commands:\n");
	printf("\"0\" or \"head\" to return the first element in the queue\n");
	printf("\"1\" or \"tail\" to return the last element in the queue\n");
	printf("\"2\" or \"enqueue\" followed by an integer to place an element in the queue\n");
	printf("\"3\" or \"dequeue\" to remove the first element from the queue and return its value\n");
	printf("\"4\" or \"exit\" to exit\n");
	printf("\"5\" or \"max\" to get max\n");

	while (true) {
		char input[8];
		scanf("%s", input);
		
		Command c;
		if (strcmp(input, "head") == 0 || strcmp(input, "0") == 0) {
			c = HEAD;
		} else if (strcmp(input, "tail") == 0 || strcmp(input, "1") == 0) {
			c = TAIL;
		} else if (strcmp(input, "enqueue") == 0 || strcmp(input, "2") == 0) {
			c = ENQUEUE;
		} else if (strcmp(input, "dequeue") == 0 || strcmp(input, "3") == 0) {
			c = DEQUEUE;
		} else if (strcmp(input, "exit") == 0 || strcmp(input, "4") == 0) {
			c = EXIT;
		} else if (strcmp(input, "print1") == 0 || strcmp(input, "6") == 0) {
			c = PRINT1;
		} else if (strcmp(input, "print2") == 0 || strcmp(input, "7") == 0) {
			c = PRINT2;
		} else if (strcmp(input, "max") == 0 || strcmp(input, "5") == 0) {
			c = GETMAX;
		} else {
			c = UNKNOWN;
		}
		
		switch (c) {
			case HEAD:
				printf("%i\n", head());
				break;
			case TAIL:
				printf("%i\n", tail());
				break;
			case ENQUEUE:
				int value;
				scanf("%i", &value);
				enqueue(value);
				break;
			case DEQUEUE:
				printf("%i\n", dequeue());
				break;
			case GETMAX:
				printf("%i\n", getMax());
				break;
			case PRINT1:
				print(stack1, &head1);
				break;
			case PRINT2:
				print(stack2, &head2);
				break;
			case EXIT:
				return 0;
			case UNKNOWN:
			default:
				printf("Wrong command!\n");
				break;
		}
	}
	
	return 0;
}