#include <iostream>
#include <string>
#include <stack>
#include <unordered_set>
#include <vector>

std::vector<std::string> splitString(std::string str, std::string delimiter = " ")
{
    std::vector<std::string> tokens;
    int start = 0;
    int end = str.find(delimiter);
    while (end != -1) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start, end - start));
    return tokens;
}


// Evaluate Reverse Polish Notation
int evalRPN(std::vector<std::string>& tokens) {
    std::unordered_set<std::string> operations = {"+", "-", "*", "/"};
    std::stack<long> st;
    for(int i=0; i < tokens.size(); i++){
        if(operations.find(tokens[i]) == operations.end()){
            st.push(stol(tokens[i]));
        }
        else{
            long long fstValue = st.top(); st.pop();
            long long sndValue = st.top(); st.pop();
            if(tokens[i] == "+") st.push(sndValue + fstValue);
            else if(tokens[i] == "-") st.push(sndValue - fstValue);
            else if(tokens[i] == "*") st.push(sndValue * fstValue);
            else st.push(sndValue / fstValue);
        }
    }
    return (int)st.top();
}

// Test time of execution
std::chrono::duration<double> testTime(std::vector<std::string> tokens, int n){
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i < n; i++){
        evalRPN(tokens);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d = end-start;
    return d;
}

int main() {
    std::string expression = "10 6 9 3 + -11 * / * 17 + 5 +";
    std::vector<std::string> tokens = splitString(expression);
    std::cout << evalRPN(tokens) << "\n";
    std::cout << "Time: " << testTime(tokens, 100000).count() << " seconds\n";
    return 0;
}
