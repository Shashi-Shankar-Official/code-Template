#include <bits/stdc++.h>
using namespace std;

// class MinStack {
//     public: 
//     stack<pair<int, int>> st;
//     void push(int val) {
//         if(st.empty()) {
//             st.push({val, val});
//         } else {
//             st.push({val, min(val, st.top().second)});
//         }
//     }

//     void pop() {
//         if(!st.empty()) {
//             st.pop();
//         }
//     }

//     int top() {
//         if(!st.empty()) {
//             return st.top().first;
//         }
//         return -1;
//     }
//     int getMin() {
//         if(!st.empty()) {
//             return st.top().second;
//         }
//         return -1;
//     }

// };

class MinStack {
    public:
    stack<int> st;
    int minVal=INT_MAX;
    void push(int val) {
        if(st.empty()) {
            st.push(val);
            minVal = min(minVal, val);
        } else {
            if(val < minVal) {
                st.push(2*val-minVal);
                minVal = val;
            } else {
                st.push(val);
            }
        }
    }

    int top() {
        if(st.empty()) {
            return -1;
        } else {
            if(st.top() < minVal) {
                return minVal;
            } else {
                return st.top();
            }
        }
    }

    void pop() {
        if(st.empty()) {
            return;
        } else {
            if(st.top() < minVal) {
                minVal = 2*minVal-st.top();
                st.pop();
            } else {
                st.pop();
            }
        }
    }

    int getMin() {
        return minVal;
    }
};

int main() {

    MinStack ms;
    ms.push(5);
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.push(10);
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.push(3);
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.push(7);
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.push(11);
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.pop();
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.pop();
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.pop();
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.pop();
    cout<< ms.top() << " "<< ms.minVal << endl; 
    ms.pop();

    return 0;
}