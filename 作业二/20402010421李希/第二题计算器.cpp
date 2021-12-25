#include <iostream>
#include <stack>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

struct Token {  // һ���򵥵Ľṹ�壬��Աֻ��һ���ַ���������������ֵ����� 
    string text;
    int pos;
    Token(string text) : text(text) {}
    double doubleValue() {  //  ��string����ת��Ϊdouble���� 
        stringstream ss(text);
        double value;
        ss >> value;
        return value;
    }
};

class Parser {

    struct Tree {      // ������
        Token token;   // ������ֵ����� 
        Tree * left;   // ָ����������ָ�� 
        Tree * right;  // ָ����������ָ�� 

        Tree(Token token) : token(token) {
            left = nullptr;
            right = nullptr;
        }
        ~Tree() {
            if (left != nullptr) delete left;
            if (right != nullptr) delete right;
        }
    };

    Tree * expression;  // ָ����ʽ��������ָ�� 
    double result;      // �������ʽ�ļ����� 

    static double execute(Tree * expression) {  // ������ʽ��ֵ 
        if (expression->left == nullptr) {   // ������Ϊ��ʱ��token������ǵ�ǰ������ֵ 
            return expression->token.doubleValue();
        } else {   // �������������ڣ��ֱ��������������ֵ���ٸ��ݷ��Ž����������� 
            double left = execute(expression->left);
            double right = execute(expression->right);
            switch (expression->token.text[0]) { // ��������������ʱ��token������Ƿ��� 
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return left / right;
            }
            // ���ﲻ�ӵĵĻ��ᱨwarning��control may reach end of non-void function 
            return 0;
        }
     }

public:  
    Parser() {
        expression = nullptr;
    }

    ~Parser() {
        if (expression != nullptr) delete expression;
    }

    // ִ�б��ʽ���� 
    double execute() {
        if (expression != nullptr) {
            result = execute(expression);
            delete expression;
            expression = nullptr;
        }
        return result;
    }

    // ����һ������ 
    bool create(stack<pair<Tree*, int>> &subTreeStack, stack<pair<string, int>> &operatorStack) {
        if(operatorStack.empty() || subTreeStack.empty()) return false;
        Tree* node = new Tree(Token(operatorStack.top().first));  // ������ֵΪ��ʱ����ջ�Ķ��� 
        int operatorPos = operatorStack.top().second;
        operatorStack.pop();              // pop������ջ�Ķ��� 
        node->right = subTreeStack.top().first;     // �������Һ���Ϊ����ջ�Ķ��� 
        int subTreePos = subTreeStack.top().second;
        subTreeStack.pop();               // pop������ջ�Ķ��� 
        if (!subTreeStack.empty()) {
            node->left = subTreeStack.top().first;  // ����������Ϊ��ʱ����ջ�Ķ��� 
            subTreeStack.pop();
        } else if(subTreePos == operatorPos + 1){  // �������������-5��-0��=0 
            Tree* temp = new Tree(Token("0"));
            node->left = temp;                 // ����������Ϊһ��ֵΪ0������ 
        } else return false;
        subTreeStack.push({node, operatorPos});   // �����ӽ�ջ�� 
        return true;
    }

    // �����ʽ������һ�Ŷ����� 
    bool parse(string str) {
        stack<pair<Tree*, int>> subTreeStack;    // ����ջ 
        stack<pair<string, int>> operatorStack;  // ����ջ

        for (unsigned i = 0; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {  // ����ΪҶ�ӽ�� 
                string value = "";
                int pre = i;
                for (unsigned j = i; j < str.length(); j++) {  // ��ȡ���֣��������ܴ��ڵ�С���� 
                    if ((str[j] >= '0' && str[j] <= '9') || str[j] == '.') {
                        value += str[j];
                        i = j;
                    } else {
                        break;
                    }
                }
                Tree* node = new Tree(Token(value));
                subTreeStack.push({node, pre});
            } else if (str[i] == '+' || str[i] == '-') {
                string value = "";
                value += str[i];
                if (operatorStack.empty()) {
                    operatorStack.push({value, i});
                } else {
                    if (i >= 1 && str[i-1] == '(') // �����֣�-���ߣ�+�ֶ����һ��ֵΪ0������ 
                       subTreeStack.push({new Tree(Token("0")), i - 1});
                    // �����Ӽ����ţ��������ջ��Ϊ�գ��Ƚ���ʱ��ջ����һ���������ٽ��÷�����ջ 
                    while (!operatorStack.empty() &&
                      (operatorStack.top().first == "+" || operatorStack.top().first == "-"
                        || operatorStack.top().first == "*" || operatorStack.top().first == "/")) {
                        if(create(subTreeStack, operatorStack) == false) return false;
                    }
                    operatorStack.push({value, i});
                }
            } else if (str[i] == '*' || str[i] == '/') {
                if(subTreeStack.empty())  return false;
                string value = ""; 
                value += str[i];
                if (operatorStack.empty()) {
                    operatorStack.push({value, i});
                } else {
                    // �����˳����ţ��������ջ��Ϊ����ջ��ͬΪ�˳����ţ��Ƚ���ʱ��ջ����һ������������ջ 
                    while (!operatorStack.empty() &&
                        (operatorStack.top().first == "*" || operatorStack.top().first == "/")) {
                        if(create(subTreeStack, operatorStack) == false) return false;
                    }
                    operatorStack.push({value, i});
                }
            } else if (str[i] == '(') {
                string value = "";
                value += str[i];
                operatorStack.push({value, i});
            } else if (str[i] == ')') {
                while (!operatorStack.empty() && operatorStack.top().first != "(") {  // ����������ֱ������'(' 
                    if(create(subTreeStack, operatorStack) == false) return false;
                }
                if(operatorStack.top().first != "(") return false;
                operatorStack.pop();  // pop '('
            }
        }
        while (!operatorStack.empty()) {  //����������������ֱ������ջΪ�� 
            if(create(subTreeStack, operatorStack) == false) return false;
        }
        expression = subTreeStack.top().first; // �������ջ��ջ����ֵ��Ϊ���ʽ��ֵ 
        return true;
    }         
                           
};

int main() {  
    Parser p = Parser();  
    string expression;
    ifstream in("cin.txt");
    ofstream out("out.txt");
    ofstream out_Statistics("Statistics.txt");
    int Error_Cnt = 0, Correct_Cnt = 0;
    while ( in >> expression) {
        if (expression.length() > 0) {  // ��������ַ��� 
            if(!p.parse(expression)){
                Error_Cnt++;
                continue;
            } else  Correct_Cnt++;
            out  << expression  << "    =  " << fixed << setprecision(4) <<  p.execute() << endl;
        }
    }
    time_t now = time(0);
    string times = ctime(&now);
    out_Statistics << "Execution time :" << times << '\n';
    out_Statistics << "The total number of expressions is :  " <<  Error_Cnt + Correct_Cnt << '\n';
    out_Statistics << "The number of correct expressions is :  " <<  Correct_Cnt << '\n';
    out_Statistics << "The number of error expressions is :  " << Error_Cnt << '\n';

    return 0;
}
