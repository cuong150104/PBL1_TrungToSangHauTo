#include <unistd.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <unistd.h>

#include <windows.h>

#include <iomanip>

#define pi 3.14159265
#define e 2.718281828
using namespace std;
// Định nghĩa cấu trúc của một nút trong danh sách liên kết
struct Node {
    double data;
    struct Node * next;
};
typedef struct Node node;

int isOperator(char ch); // Hàm kiểm tra xem một ký tự có phải là toán tử hay không
int isOperand(char ch); // Hàm kiểm tra xem một ký tự có phải là chữ số hay không
int isOperand1(char ch);
void table(char * infixExpression, char * postfixExpression, Node * stack, int i, int j); // Hàm làm bảng trình bày
void infixToPostfix1(char * infixExpression, char * postfixExpression); // Hàm chuyển Trung Tố sang Hậu Tố 
double evaluatePostfix(char * postfixExpression); // Hàm tinh Giá trị biểu thưc
//void setConsoleWindowSize(int width1, int height1); // thay doi man hinh mo rong
void gotoxy(int x, int y);//hàm tọa độ
int isNegativeOperand(char* infixExpression, int index) {
    // Kiểm tra nếu ký tự đầu tiên là dấu trừ và ký tự thứ hai là một chữ số
    return (infixExpression[index] == '-' && isOperand(infixExpression[index + 1]));
}

void display(int k,int size);
bool isMinusOperator(char * infixExpression, int index);

double calculate_sin(double x) {
   double val = pi / 180;
   return sin(x * val);
}

double calculate_cos(double x) {
   double val = pi / 180;
   return cos(x * val);
}

double calculate_tan(double x) {
   double val = pi / 180;
   return tan(x * val);
}

double calculate_cot(double x) {
   double val = pi / 180;
   return 1 / tan(x * val);
}

double calculate_ln(double x) {
   return log(x)/log(e);
}

double calculate_log(double x) {
   return log10(x);
}

double calculate_e() {
   return exp(1.0);
}


int main() {
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    int width1 = 800; // Chiều rộng mới
    int height1 = 400; // Chiều cao mới
    //setConsoleWindowSize(width1, height1);

    int luachon = 1;
    do {
        char infixExpression[1000000];
        char postfixExpression[1000000];
        int size;

        printf("\n");

        int t = 1;
        int k = 5;
        do {
            t = 0;
            printf("Nhap bieu thuc trung to: ");
            gets(infixExpression);
            infixExpression[strcspn(infixExpression, "\n")] = '\0'; // Loại bỏ ký tự '\n' thừa từ fgets
            size = strlen(infixExpression);
//            for (int i = 0; i < size; i++) {
//                char c = infixExpression[i];
//
//                // Nếu ký tự không phải là toán tử hoặc ký tự số
//                if (!isOperator(c) && !isOperand(c)) {
//                    t = 1; // Chuỗi không hợp lệ
//                    k++;
//                    printf("nhap khong hop le! nhap lai di\n");
//                    break;	
//                }
//            }
        } while (t);
        printf("\n\n");
        display(k,size);

        infixToPostfix1(infixExpression, postfixExpression);

        printf("\nBieu thuc hau to: %s\n", postfixExpression);

        double result = evaluatePostfix(postfixExpression);
        printf("Ket qua: %.2f\n", result);
        printf("\nNhan 0 de het thuc, nhan 1 de tiep tuc\n");
        scanf("%d", & luachon);
        system("cls");
        fflush(stdin);
	} while (luachon);
    return 0;
}



int isOperand(char ch) {
    return ch >= '0' && ch <= '9';
}
int isOperand1(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%';
}

// Hàm kiểm tra xem một toán tử có độ ưu tiên cao hơn toán tử khác hay không
int isHigherPrecedence(char op1, char op2) {
    int precedence1, precedence2;

    switch (op1) {
    case '+':
    case '-':
        precedence1 = 1;
        break;
    case '*':
    case '%':
    case '/':
        precedence1 = 2;
        break;
    case '^':
        precedence1 = 3;
        break;
    default:
        precedence1 = 0;
        break;
    }

    switch (op2) {
    case '+':
    case '-':
        precedence2 = 1;
        break;
    case '*':
    case '%':
    case '/':
        precedence2 = 2;
        break;
    case '^':
        precedence2 = 3;
        break;
    default:
        precedence2 = 0;
        break;
    }

    return precedence1 >= precedence2;
}
void gotoxy(int x, int y) {
    HANDLE hConsoleOutput;
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, cursorPosition);
}
// lam bang trình bày
void table(char * infixExpression, char * postfixExpression, Node * stack, int i, int j) {
    int len;
    len = strlen(infixExpression);
    char * temp;
    temp = (char * ) malloc((len - i) * sizeof(char));
    for (int k = i; infixExpression[k] != '\0'; k++) {
        temp[k - i - 1] = infixExpression[k];
    }
    temp[len - i - 1] = '\0';

    int count = 0;
    char temp1[10000];
    struct Node * stack1 = stack;
    while (stack1 != NULL) {
        temp1[count] = stack1 -> data;
        count++;
        stack1 = stack1 -> next;
    }

    char reversedTemp1[10000];
    int m, n;
    for (m = count - 1, n = 0; m >= 0; m--, n++) {
        reversedTemp1[n] = temp1[m];
    }
    reversedTemp1[n] = '\0';
    postfixExpression[j] = '\0';
    printf("     ");
    printf("%*s", len * 1, temp);
    // sleep(1);
    printf("       ");
    printf("%*s", len * 2, postfixExpression);
    // sleep(1);
    printf("          %-3s\n", reversedTemp1);
    //sleep(1);

    free(temp);
}

// ham chuyển Trung Tố sang Hậu Tố
void infixToPostfix1(char *infixExpression, char *postfixExpression) {
    struct Node *stack = NULL; // Ngăn xếp để lưu trữ các toán tử
    int i, j;
    int len = strlen(infixExpression);

    // Duyệt qua từng ký tự trong biểu thức trung tố
    for (i = 0, j = 0; infixExpression[i] != '\0'; i++) {
        char ch = infixExpression[i];

        if ((isNegativeOperand(infixExpression, i) && infixExpression[i - 1] == ' ') ||
            (isNegativeOperand(infixExpression, i) && i == 0) ||
            (isNegativeOperand(infixExpression, i) && isOperator(infixExpression[i - 1]))) {
            // Thêm dấu trừ vào biểu thức hậu tố trước toán hạng âm
            postfixExpression[j++] = '-';
            i++;
            while (isOperand(infixExpression[i])) {
                postfixExpression[j++] = infixExpression[i++];
            }
            i--;
            postfixExpression[j++] = ' ';
            continue;
        }

        if ((infixExpression[i - 1] == '-' && infixExpression[i] == '(' && infixExpression[i + 1] == '-') ||
            (infixExpression[i - 1] == '+' && infixExpression[i] == '(' && infixExpression[i + 1] == '-') ||
            (infixExpression[i - 1] == '*' && infixExpression[i] == '(' && infixExpression[i + 1] == '-') ||
			(infixExpression[i - 1] == '/' && infixExpression[i] == '(' && infixExpression[i + 1] == '-') ||
			(infixExpression[i - 1] == '%' && infixExpression[i] == '(' && infixExpression[i + 1] == '-') ||
			(infixExpression[i - 1] == '^' && infixExpression[i] == '(' && infixExpression[i + 1] == '-') || 
			(infixExpression[i - 1] == '-' && infixExpression[i] == '(' && infixExpression[i + 1] == '+') ||
            (infixExpression[i - 1] == '+' && infixExpression[i] == '(' && infixExpression[i + 1] == '+') ||
            (infixExpression[i - 1] == '*' && infixExpression[i] == '(' && infixExpression[i + 1] == '+') ||
			(infixExpression[i - 1] == '/' && infixExpression[i] == '(' && infixExpression[i + 1] == '+') ||
			(infixExpression[i - 1] == '%' && infixExpression[i] == '(' && infixExpression[i + 1] == '+') ||
			(infixExpression[i - 1] == '^' && infixExpression[i] == '(' && infixExpression[i + 1] == '+')   ) {
            // Thêm dấu cộng vào biểu thức hậu tố trước toán hạng âm
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = ch;
            newNode->next = stack;
            stack = newNode;
            table(infixExpression, postfixExpression, stack, i, j);
            // Xử lý toán hạng âm
            int negativeValue = 0;
            int k = i + 2;

            if(infixExpression[i +1] == '-'){
            postfixExpression[j++] = '-';
        	}else if(infixExpression[i +1] == '+'){
		    postfixExpression[j++] = '+'; 
         	}else if(infixExpression[i +1] == '*'){
		    postfixExpression[j++] = '*'; 
            }else if(infixExpression[i +1] == '/'){
		    postfixExpression[j++] = '/'; 
			}else if(infixExpression[i +1] == '%'){
		    postfixExpression[j++] = '%'; 
			}else if(infixExpression[i +1] == '^'){
		    postfixExpression[j++] = '^'; 
			}
		    
            // Đọc giá trị số âm và lưu trữ nó
            while (isdigit(infixExpression[k])) {
                negativeValue = negativeValue * 10 + (infixExpression[k] - '0');
                k++;
            }
            // Chuyển giá trị số âm thành chuỗi và thêm vào biểu thức hậu tố
            char negativeValueStr[20];
            sprintf(negativeValueStr, "%d", negativeValue);
            int l;
            for (l = 0; negativeValueStr[l] != '\0'; l++) {
                postfixExpression[j++] = negativeValueStr[l];
            }

            postfixExpression[j++] = ' ';

            // Cập nhật chỉ số i để bỏ qua các ký tự số âm trong biểu thức trung tố
            i = k - 1;

            table(infixExpression, postfixExpression, stack, i, j); // In ra màn hình
            continue;
        }



        if(isOperand1(ch)){
        	 while (isOperand1(infixExpression[i])) {
                postfixExpression[j++] = infixExpression[i++];
            }
            while( infixExpression[i-1] != ')' && ch != 'e' && ch != 'p' &&ch !='i'){
            	postfixExpression[j++] = infixExpression[i++];
            	
			}
            postfixExpression[j++] = ' ';
           i--;
            table(infixExpression, postfixExpression, stack, i, j);
        }else if(isOperand(ch)) {
            while (isOperand(infixExpression[i])) {
                postfixExpression[j++] = infixExpression[i++];
            }
            postfixExpression[j++] = ' ';
            i--;

            table(infixExpression, postfixExpression, stack, i, j); // In ra màn hình
		} else if (isOperator(ch)) {
            while (stack != NULL && isOperator(stack->data) && isHigherPrecedence(stack->data, ch)) {
                postfixExpression[j++] = stack->data;
                stack = stack->next;
                postfixExpression[j++] = ' ';
                table(infixExpression, postfixExpression, stack, i, j);
            }

            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = ch;
            newNode->next = stack;
            stack = newNode;

            table(infixExpression, postfixExpression, stack, i, j);
        } else if (ch == '(') {
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = ch;
            newNode->next = stack;
            stack = newNode;

            table(infixExpression, postfixExpression, stack, i, j);
        } else if (ch == ')') {
            while (stack != NULL && stack->data != '(') {
                postfixExpression[j++] = stack->data;
                stack = stack->next;
            }

            if (stack != NULL && stack->data == '(') {
                stack = stack->next;
            }
            table(infixExpression, postfixExpression, stack, i, j);
        }
    }

    while (stack != NULL) {
        postfixExpression[j++] = stack->data;
        stack = stack->next;
    }

    postfixExpression[j] = '\0';
    printf("           ");
    printf("%*s", len * 2 + len, postfixExpression);
}

// Hàm tính giá trị của biểu thức hậu tố
double evaluatePostfix(char* postfixExpression) {
    struct Node* stack = NULL; // Ngăn xếp để lưu trữ các toán hạng
    int i;
   int len = strlen(postfixExpression);

    // Duyệt qua từng ký tự trong biểu thức hậu tố
    for (i = 0; i < len; i++) {
        char ch = postfixExpression[i];

      // Nếu ký tự hiện tại là chữ số hoặc số âm, đưa vào ngăn xếp
        if (isdigit(ch) || (ch == '-' && isdigit(postfixExpression[i + 1]))) {
            double operand = 0;
            int sign = 1;
            // Kiểm tra xem có phải số âm hay không
            if (ch == '-') {
                sign = -1;
                i++;
            }

            while (isdigit(postfixExpression[i]) || postfixExpression[i] == '.') {
                if (postfixExpression[i] == '.') {
                    i++;
                    double decimal = 0.1;
                    while (isdigit(postfixExpression[i])) {
                        operand += (postfixExpression[i] - '0') * decimal;
                        decimal *= 0.1;
                        i++;
                    }
                    break;
                }
                operand = operand * 10 + (postfixExpression[i] - '0');
                i++;
            }

            // Thêm số âm nếu có
            operand *= sign;

            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = operand;
            newNode->next = stack;
            stack = newNode;
        
        }else if(isOperand1(ch)){
        	char c = postfixExpression[i+1];
        	char h = postfixExpression[i+2];
        	double operand = 0;
            int sign = 1;
            
    		while(!isdigit(postfixExpression[i])&& ch != 'i' && ch != 'e' ) {
    			i++;
			}
	
        	if (postfixExpression[i+1] == '-') {
                sign = -1;
                i++;
            }

            while (isdigit(postfixExpression[i]) || postfixExpression[i] == '.') {
                if (postfixExpression[i] == '.') {
                    i++;
                    double decimal = 0.1;
                    while (isdigit(postfixExpression[i])) {
                        operand += (postfixExpression[i] - '0') * decimal;
                        decimal *= 0.1;
                        i++;
                    }
                    break;
                }
                operand = operand * 10 + (postfixExpression[i] - '0');
                printf("wqeqwe  %s",ch);
                printf("wqeqwe");
                  if (ch == 'e' && operand != 0) {
                     operand = operand * M_E;
                     }else if(ch=='e' && operand == 0){
                     	operand=e;
					 }
					 printf("wqeqwe");
                i++;
            }

            // Thêm số âm nếu có
            operand *= sign;

        	if(ch=='s'&&c=='i'&&h=='n' || ch == 'S' && c=='I' &&h=='N'){
        		operand = calculate_sin(operand);
			}else if(ch=='c'&&c=='o' && h=='s'|| ch == 'C' && c=='O' &&h=='S'){
        		operand = calculate_cos(operand);
            }else if(ch=='t'&&c=='a' && h=='n'|| ch == 'T' && c=='A' && h=='N'){
        		operand = calculate_tan(operand);
            }else if(ch=='l'&&c=='n' || ch == 'L' && c=='N'){
        		operand = calculate_ln(operand);
            }else if(ch=='l'&&c=='o' && h=='g'|| ch == 'L' && c=='O'&&h=='g'){
        		operand =calculate_log(operand);
            }
            else if(ch=='e'){
        		operand = e;
            }else if(ch=='p' && c== 'i' &&postfixExpression[i+2] != ')'){
        		operand =M_PI;
            }
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = operand;
            newNode->next = stack;
            stack = newNode;
		}
        // Nếu ký tự hiện tại là toán tử
        else if (isOperator(ch)) {
            double operand2 = stack->data;
            stack = stack->next;
            double operand1 = stack->data;
            stack = stack->next;
            double result;

            switch (ch) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            case '^':
                result = pow(operand1, operand2);
                break;
            case '%':
                result = fmod(operand1, operand2);
                break;
            }

            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = result;
            newNode->next = stack;
            stack = newNode;
        }
    }

    // Kết quả cuối cùng sẽ nằm trên đỉnh ngăn xếp
    if (stack != NULL) {
        double finalResult = stack->data;
        stack = stack->next;
        return finalResult;
    }

    return 0;
}



bool isMinusOperator(char * infixExpression, int index) {
    if (index == 0 || infixExpression[index - 1] == '(' && infixExpression[index-2] =='-' || isOperator(infixExpression[index - 1]))
        return true;
    return false;
}

void display(int k,int size){
    gotoxy(size, k);
    printf("infix");
    gotoxy(size * 3, k);
    printf("postfix");
    gotoxy(size * 3 + 20, k);
    printf("stack");
    printf("\n");
    printf("     ");
    for (int i = 0; i < size; i++) {
        printf("-");
    }
    printf("   |   ");
    for (int i = 0; i < size * 2; i++) {
        printf("-");
    }
    printf("   |   ");
    for (int i = 0; i < 8; i++) {
        printf("-");
    }
    printf("    \n");
}
//void setConsoleWindowSize(int width, int height) {
//    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//    SMALL_RECT rect = {0, 0, width , height+1 };
//
//    // Thay đổi kích thước của cửa sổ
//    SetConsoleWindowInfo(console, TRUE, &rect);
//
//    COORD bufferSize = {width, height};
//    // Thay đổi kích thước của bộ đệm màn hình
//    SetConsoleScreenBufferSize(console, bufferSize);
//}
//56-4+44/4^5/5+4%3-22*66