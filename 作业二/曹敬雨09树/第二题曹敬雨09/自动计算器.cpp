#include <iostream>
#include <stack>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

struct Token {  // 一个简单的结构体，成员只有一个字符串，用来储存数值或符号 
    string text;
    int pos;
    Token(string text) : text(text) {}
    double doubleValue() {  //  将string类型转化为double类型 
        stringstream ss(text);
        double value;
        ss >> value;
        return value;
    }
};

class Parser {

    struct Tree {      // 二叉树
        Token token;   // 储存数值或符号 
        Tree * left;   // 指向左子树的指针 
        Tree * right;  // 指向右子树的指针 

        Tree(Token token) : token(token) {
            left = nullptr;
            right = nullptr;
        }
        ~Tree() {
            if (left != nullptr) delete left;
            if (right != nullptr) delete right;
        }
    };

    Tree * expression;  // 指向表达式二叉树的指针 
    double result;      // 整个表达式的计算结果 

    static double execute(Tree * expression) {  // 计算表达式的值 
        if (expression->left == nullptr) {   // 左子树为空时，token储存的是当前子树的值 
            return expression->token.doubleValue();
        } else {   // 左右子树均存在，分别结算左右子树的值，再根据符号进行四则运算 
            double left = execute(expression->left);
            double right = execute(expression->right);
            switch (expression->token.text[0]) { // 左右子树均存在时，token储存的是符号 
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return left / right;
            }
            // 这里不加的的话会报warning：control may reach end of non-void function 
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

    // 执行表达式计算 
    double execute() {
        if (expression != nullptr) {
            result = execute(expression);
            delete expression;
            expression = nullptr;
        }
        return result;
    }

    // 创建一颗新树 
    bool create(stack<pair<Tree*, int>> &subTreeStack, stack<pair<string, int>> &operatorStack) {
        if(operatorStack.empty() || subTreeStack.empty()) return false;
        Tree* node = new Tree(Token(operatorStack.top().first));  // 新子树值为此时符号栈的顶部 
        int operatorPos = operatorStack.top().second;
        operatorStack.pop();              // pop掉符号栈的顶部 
        node->right = subTreeStack.top().first;     // 新树的右孩子为子树栈的顶部 
        int subTreePos = subTreeStack.top().second;
        subTreeStack.pop();               // pop掉子树栈的顶部 
        if (!subTreeStack.empty()) {
            node->left = subTreeStack.top().first;  // 新树的左孩子为此时子树栈的顶部 
            subTreeStack.pop();
        } else if(subTreePos == operatorPos + 1){  // 考虑特殊情况：-5，-0，=0 
            Tree* temp = new Tree(Token("0"));
            node->left = temp;                 // 新树的左孩子为一个值为0的子树 
        } else return false;
        subTreeStack.push({node, operatorPos});   // 新树加进栈顶 
        return true;
    }

    // 将表达式构建成一颗二叉树 
    bool parse(string str) {
        stack<pair<Tree*, int>> subTreeStack;    // 子树栈 
        stack<pair<string, int>> operatorStack;  // 符号栈

        for (unsigned i = 0; i < str.length(); i++) {
            if (str[i] >= '0' && str[i] <= '9') {  // 数字为叶子结点 
                string value = "";
                int pre = i;
                for (unsigned j = i; j < str.length(); j++) {  // 提取数字，包含可能存在的小数点 
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
                    if (i >= 1 && str[i-1] == '(') // 当出现（-或者（+手动添加一个值为0的子树 
                       subTreeStack.push({new Tree(Token("0")), i - 1});
                    // 遇到加减符号，如果符号栈不为空，先将此时的栈构建一颗子树，再将该符号入栈 
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
                    // 遇到乘除符号，如果符号栈不为空且栈顶同为乘除符号，先将此时的栈构建一颗子树，再入栈 
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
                while (!operatorStack.empty() && operatorStack.top().first != "(") {  // 构建子树，直到遇到'(' 
                    if(create(subTreeStack, operatorStack) == false) return false;
                }
                if(operatorStack.top().first != "(") return false;
                operatorStack.pop();  // pop '('
            }
        }
        while (!operatorStack.empty()) {  //继续构建二叉树，直至符号栈为空 
            if(create(subTreeStack, operatorStack) == false) return false;
        }
        expression = subTreeStack.top().first; // 最后子树栈的栈顶的值即为表达式的值 
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
        if (expression.length() > 0) {  // 不处理空字符串 
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
