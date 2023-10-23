//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <iostream>
//#include <vector>
//#include <stack>
//#include <algorithm>
//#define MaxSize 1000
//#define bool int
//
//using namespace std;
//
////专用于构造后缀表达式，存放符号的栈
//typedef struct {
//    char Data[MaxSize];
//    int topIndex;//始终指向栈顶元素，栈空时为-1
//}post_stack;
//
//bool isEmpty(post_stack* s) {
//    if (s->topIndex == -1)
//        return 1;
//    else
//        return 0;
//}
//
//bool isFull(post_stack* s) {
//    if (s->topIndex >= MaxSize - 1)
//        return 1;
//    return 0;
//}
//
//void push(post_stack* s, char c) {
//    if (!isFull(s)) {
//        s->topIndex++;
//        s->Data[s->topIndex] = c;
//    }
//}
//
//char pop(post_stack* s) {
//    char c;
//    if (!isEmpty(s)) {
//        c = s->Data[s->topIndex];
//        s->topIndex--;
//    }
//    else {
//        cout << "Error!The stack is Empty!\n";
//        exit(0);
//    }
//    return c;
//}
//
//char top(post_stack* s) {
//    char c;
//    if (!isEmpty(s)) {
//        c = s->Data[s->topIndex];
//    }
//    else {
//        cout << "Error!The stack is Empty!\n";
//        exit(0);
//    }
//    return c;
//}
//
////正则表达式预处理，连接表示为&
//void init_regular(char* re) {
//    char init[MaxSize];
//    int n = strlen(re);
//    int i = 0, j = -1;
//    while (i < n - 1 && j < MaxSize) {
//        if ((isalnum(re[i]) || re[i] == ')' || re[i] == '*') && (isalnum(re[i + 1]) || re[i + 1] == '(')) {
//            init[++j] = re[i++];
//            init[++j] = '&';
//        }
//        else
//            init[++j] = re[i++];
//    }
//    init[++j] = re[i];
//    init[++j] = '\0';
//    strcpy(re, init);
//}
//
////计算运算符的优先级，* > & > | > (
//int priority(char ch)
//{
//
//    if (ch == '*')
//    {
//        return 3;
//    }
//
//    if (ch == '&')
//    {
//        return 2;
//    }
//
//    if (ch == '|')
//    {
//        return 1;
//    }
//
//    if (ch == '(')
//    {
//        return 0;
//    }
//    return 0;
//}
//
////正则表达式转后缀表达式
//void regular_to_postfix(char* re) {
//    init_regular(re);
//    char postfix[MaxSize];
//    post_stack regular = { "", -1 };
//    post_stack* p_re = &regular;
//    int n = strlen(re), i = 0, j = -1;
//    while (i < n) {
//        if (isalnum(re[i])) {
//            postfix[++j] = re[i++];
//        }
//        else if (re[i] == '(') {
//            push(p_re, re[i++]);
//        }
//        else if (re[i] == ')') {
//            char top_element;
//            if (!isEmpty(p_re)) {
//                top_element = pop(p_re);
//            }
//            while (top_element != '(') {
//                postfix[++j] = top_element;
//                if (!isEmpty(p_re)) {
//                    top_element = pop(p_re);
//                }
//                else {
//                    cout << "The expression is illegal!\n";
//                    exit(0);
//                }
//            }
//            i++;
//        }
//        else {
//            if (isEmpty(p_re) || top(p_re) == '(') {
//                push(p_re, re[i++]);
//            }
//            else {
//                char top_element = top(p_re);
//                while (priority(re[i]) <= priority(top_element)) {
//                    postfix[++j] = pop(p_re);
//                    if (isEmpty(p_re)) {
//                        break;
//                    }
//                    top_element = top(p_re);
//                }
//                push(p_re, re[i++]);
//            }
//        }
//    }
//    while (!isEmpty(p_re)) {
//        postfix[++j] = pop(p_re);
//    }
//    postfix[++j] = '\0';
//    strcpy(re, postfix);
//}
//
////由后缀表达式构造NFA,其中空串用#表示
//struct NFAstate {
//    int head;
//    char ch;
//    int tail;
//};
//
//struct NFA {
//    int start;
//    int end;
//};
//
//stack<NFA> nfas;
//vector<NFAstate> construct_NFA(char* re) {
//    regular_to_postfix(re);
//    vector<NFAstate> states;
//    int state_num = 0;
//    int n = strlen(re), i = 0;
//    while (i < n) {
//        if (isalnum(re[i])) {
//            NFAstate s = { state_num, re[i], state_num + 1 };
//            states.push_back(s);
//            NFA nfa = { state_num, state_num + 1 };
//            nfas.push(nfa);
//            state_num += 2;
//        }
//        else if (re[i] == '*') {
//            NFA nfa = nfas.top();
//            nfas.pop();
//            NFAstate s1 = { nfa.end, '#', nfa.start };
//            states.push_back(s1);
//            NFAstate s2 = { state_num, '#', nfa.start };
//            states.push_back(s2);
//            NFAstate s3 = { nfa.end, '#', state_num + 1 };
//            states.push_back(s3);
//            NFAstate s4 = { state_num, '#', state_num + 1 };
//            states.push_back(s4);
//            nfa.start = state_num;
//            nfa.end = state_num + 1;
//            nfas.push(nfa);
//            state_num += 2;
//        }
//        else if (re[i] == '&') {
//            NFA nfa2 = nfas.top();
//            nfas.pop();
//            NFA nfa1 = nfas.top();
//            nfas.pop();
//            NFAstate state12 = { nfa1.end, '#', nfa2.start };
//            states.push_back(state12);
//            NFA nfa = { nfa1.start, nfa2.end };
//            nfas.push(nfa);
//        }
//        else if (re[i] == '|') {
//            NFA nfa2 = nfas.top();
//            nfas.pop();
//            NFA nfa1 = nfas.top();
//            nfas.pop();
//            NFAstate s1 = { state_num, '#', nfa1.start };
//            states.push_back(s1);
//            NFAstate s2 = { state_num, '#', nfa2.start };
//            states.push_back(s2);
//            NFAstate s3 = { nfa1.end, '#', state_num + 1 };
//            states.push_back(s3);
//            NFAstate s4 = { nfa2.end, '#', state_num + 1 };
//            states.push_back(s4);
//            NFA nfa = { state_num, state_num + 1 };
//            nfas.push(nfa);
//            state_num += 2;
//        }
//        i++;
//    }
//    return states;
//}
//
////NFA -> DFA(子集构造法)
////返回正则表达式的字符集
//vector<char> input_character(char* re) {
//    vector<char> result;
//    int n = strlen(re);
//    for (int i = 0; i < n; i++) {
//        if (isalnum(re[i]) && find(result.begin(), result.end(), re[i]) == result.end()) {
//            result.push_back(re[i]);
//        }
//    }
//    return result;
//}
//
////状态集合的闭包函数
//vector<int> closure(vector<int> T, vector<NFAstate> states) {
//    stack<int> ts;
//    int n = T.size(), state_num = states.size();
//    for (int i = 0; i < n; i++) {
//        ts.push(T[i]);
//    }
//    vector<int> closureT = T;
//    while (!ts.empty()) {
//        int t = ts.top();
//        ts.pop();
//        //t--#->u
//        vector<int> us;
//        for (int i = 0; i < state_num; i++) {
//            if (states[i].head == t && states[i].ch == '#') {
//                us.push_back(states[i].tail);
//            }
//        }
//        int u_num = us.size();
//        for (int i = 0; i < u_num; i++) {
//            if (find(closureT.begin(), closureT.end(), us[i]) == closureT.end()) {
//                closureT.push_back(us[i]);
//                ts.push(us[i]);
//            }
//        }
//    }
//    sort(closureT.begin(), closureT.end());
//    return closureT;
//}
//
////move函数
//vector<int> move(vector<int> T, char ch, vector<NFAstate> states) {
//    vector<int> moveT;
//    int n = T.size(), state_num = states.size();
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < state_num; j++) {
//            if (states[j].head == T[i] && states[j].ch == ch) {
//                moveT.push_back(states[j].tail);
//            }
//        }
//    }
//    return moveT;
//}
//
//struct DFAstate {
//    vector<int> s;
//    bool flag;
//};
//
//struct DFAside {
//    vector<int> head;
//    char ch;
//    vector<int> tail;
//};
//
//struct DFAside_upper {
//    char head;
//    char ch;
//    char tail;
//};
//
//struct DFA {
//    char start;
//    vector<char> end;
//};
//
////寻找Dstates中尚未标记的T
//int find_unmark_state(vector<DFAstate>& Dstates) {
//    int n = Dstates.size();
//    for (int i = 0; i < n; i++) {
//        if (Dstates[i].flag == false) {
//            return i;
//        }
//    }
//    return -1;
//}
//
////判断状态U是否在Dstates中
//bool U_in_Dstates(vector<int> u, vector<DFAstate>& Dstates) {
//    int n = Dstates.size();
//    for (int i = 0; i < n; i++) {
//        if (u == Dstates[i].s) {
//            return true;
//        }
//    }
//    return false;
//}
//
////构造DFA
//DFA dfa;
//
//vector<DFAside_upper> construct_DFA(char* re) {
//    vector<char> input_ch = input_character(re);
//    int input_ch_num = input_ch.size();
//    vector<NFAstate> states = construct_NFA(re);
//    cout << "NFA State Number:" << states.size() << endl;
//    vector<DFAstate> Dstates;
//    vector<DFAside> Dsides;
//    NFA nfa = nfas.top();
//    vector<int> s0 = { nfa.start };
//    DFAstate s0d;
//    s0d.s = closure(s0, states);
//    s0d.flag = false;
//    Dstates.push_back(s0d);
//    int unmark_index = find_unmark_state(Dstates);
//    while (unmark_index != -1) {
//        Dstates[unmark_index].flag = true;
//        vector<int> T = Dstates[unmark_index].s;
//        for (int i = 0; i < input_ch_num; i++) {
//            vector<int> U = closure(move(T, input_ch[i], states), states);
//            if (U.size() != 0 && !U_in_Dstates(U, Dstates)) {
//                DFAstate temps = { U, false };
//                Dstates.push_back(temps);
//            }
//            if (U.size() != 0) {
//                DFAside side = { Dstates[unmark_index].s, input_ch[i], U };
//                Dsides.push_back(side);
//            }
//        }
//        unmark_index = find_unmark_state(Dstates);
//    }
//    //用A~Z表示每个状态
//    vector<DFAside_upper> Dsides_upper;
//    int Dstates_num = Dstates.size(), Dsides_num = Dsides.size();
//    for (int i = 0; i < Dsides_num; i++) {
//        DFAside_upper Dside_upper;
//        Dside_upper.ch = Dsides[i].ch;
//        for (int j = 0; j < Dstates_num; j++) {
//            if (Dstates[j].s == Dsides[i].head) {
//                Dside_upper.head = 'A' + j;
//                break;
//            }
//        }
//        for (int j = 0; j < Dstates_num; j++) {
//            if (Dstates[j].s == Dsides[i].tail) {
//                Dside_upper.tail = 'A' + j;
//                break;
//            }
//        }
//        Dsides_upper.push_back(Dside_upper);
//    }
//    dfa.start = 'A';//以NFA的start进行初始化，故dfa的start必为A
//    for (int i = 0; i < Dstates_num; i++) {
//        if (find(Dstates[i].s.begin(), Dstates[i].s.end(), nfa.end) != Dstates[i].s.end()) {
//            dfa.end.push_back('A' + i);
//        }
//    }
//    return Dsides_upper;
//}
//
//char find_tran_DFAstate(char head, char ch, vector<DFAside_upper>& Dsides_upper) {
//    for (int i = 0; i < Dsides_upper.size(); i++) {
//        if (Dsides_upper[i].head == head && Dsides_upper[i].ch == ch)
//            return Dsides_upper[i].tail;
//    }
//    return '#';
//}
//
////转移到的子集的索引
//int t_to_set(char t, vector<vector<char>>& pi) {
//    for (int i = 0; i < pi.size(); i++) {
//        if (find(pi[i].begin(), pi[i].end(), t) != pi[i].end())
//            return i;
//    }
//    return -1;
//}
//
//vector<int> diff_index(vector<int> set_index) {
//    vector<int> diff;
//    for (int i = 0; i < set_index.size(); i++) {
//        if (find(diff.begin(), diff.end(), set_index[i]) == diff.end())
//            diff.push_back(set_index[i]);
//    }
//    return diff;
//}
//
////构造最简DFA
//vector<DFAside_upper> simplest_DFA(char* re) {
//    vector<DFAside_upper> Dsides_upper = construct_DFA(re);
//    vector<char> Dstates_upper;
//    cout << "DFA State Num:" << Dsides_upper.size();
//    cout << "DFA Tran:" << endl;
//    for (auto x : Dsides_upper) {
//        printf("%c  %c  %c\n", x.head, x.ch, x.tail);
//    }
//    for (int i = 0; i < Dsides_upper.size(); i++) {
//        if (find(Dstates_upper.begin(), Dstates_upper.end(), Dsides_upper[i].head) == Dstates_upper.end()) {
//            Dstates_upper.push_back(Dsides_upper[i].head);
//        }
//        if (find(Dstates_upper.begin(), Dstates_upper.end(), Dsides_upper[i].tail) == Dstates_upper.end()) {
//            Dstates_upper.push_back(Dsides_upper[i].tail);
//        }
//    }
//    //初始化，划分接收状态集合和非接收状态集合
//    vector<char> unfinal_state;
//    vector<char> final_state = dfa.end;
//    for (int i = 0; i < Dstates_upper.size(); i++) {
//        if (find(final_state.begin(), final_state.end(), Dstates_upper[i]) == final_state.end()) {
//            unfinal_state.push_back(Dstates_upper[i]);
//        }
//    }
//    vector<vector<char>> pi = { unfinal_state, final_state };
//    vector<vector<char>> pi_new = pi;
//    vector<char> input_ch = input_character(re);
//    int input_ch_num = input_ch.size();
//    do {
//        pi = pi_new;
//        for (int i = 0; i < pi.size(); i++) {
//            vector<char> G = pi[i];
//            bool di_or_not = false;
//            for (int j = 0; j < input_ch_num; j++) {
//                vector<int> set_index;
//                for (int k = 0; k < G.size(); k++) {
//                    char t = find_tran_DFAstate(G[k], input_ch[j], Dsides_upper);
//                    int index = t_to_set(t, pi);
//                    set_index.push_back(index);
//                }
//                vector<int> diff = diff_index(set_index);
//                if (diff.size() > 1) {
//                    int divide_num = 0;
//                    while (divide_num < diff.size()) {
//                        vector<char> temp;
//                        for (int m = 0; m < G.size(); m++) {
//                            if (set_index[m] == diff[divide_num]) {
//                                temp.push_back(G[m]);
//                            }
//                        }
//                        pi_new.push_back(temp);
//                        divide_num++;
//                    }
//                    di_or_not = true;
//                    pi_new.erase(pi_new.begin() + i);
//                    break;
//                }
//            }
//            if (di_or_not == true) {
//                break;
//            }
//        }
//    } while (pi_new != pi);
//    //划分结束后，用每个子集的第一个状态作为代表
//    vector<DFAside_upper> simplest_DFAside_upper;
//    for (int i = 0; i < Dsides_upper.size(); i++) {
//        DFAside_upper  spl_Dside = Dsides_upper[i];
//        for (int j = 0; j < pi.size(); j++) {
//            if (find(pi[j].begin(), pi[j].end(), spl_Dside.head) != pi[j].end()) {
//                spl_Dside.head = pi[j][0];
//            }
//            if (find(pi[j].begin(), pi[j].end(), spl_Dside.tail) != pi[j].end()) {
//                spl_Dside.tail = pi[j][0];
//            }
//        }
//        int k = 0;
//        for (k; k < simplest_DFAside_upper.size(); k++) {
//            if (simplest_DFAside_upper[k].head == spl_Dside.head &&
//                simplest_DFAside_upper[k].ch == spl_Dside.ch &&
//                simplest_DFAside_upper[k].tail == spl_Dside.tail) {
//                break;
//            }
//        }
//        if (k == simplest_DFAside_upper.size()) {
//            simplest_DFAside_upper.push_back(spl_Dside);
//        }
//    }
//    char simplest_dfa_start = dfa.start;
//    vector<char> simplest_dfa_end;
//    for (int i = 0; i < pi.size(); i++) {
//        if (find(dfa.end.begin(), dfa.end.end(), pi[i][0]) != dfa.end.end()) {
//            simplest_dfa_end.push_back(pi[i][0]);
//        }
//    }
//    cout << "start: " << simplest_dfa_start << "\tend: ";
//    for (int i = 0; i < simplest_dfa_end.size(); i++) {
//        cout << simplest_dfa_end[i] << " ";
//    }
//    cout << endl;
//    cout << "    输入符号\n状态 ";
//    for (int i = 0; i < input_ch_num; i++) {
//        cout << input_ch[i] << "  ";
//    }
//    cout << endl;
//    vector<char> simplest_dfa_states;
//    for (int i = 0; i < pi.size(); i++) {
//        simplest_dfa_states.push_back(pi[i][0]);
//    }
//    sort(simplest_dfa_states.begin(), simplest_dfa_states.end());
//    for (char s : simplest_dfa_states) {
//        cout << " " << s << "   ";
//        for (int i = 0; i < input_ch_num; i++) {
//            cout << find_tran_DFAstate(s, input_ch[i], simplest_DFAside_upper) << "  ";
//        }
//        cout << endl;
//    }
//    return simplest_DFAside_upper;
//}
//
////判断句子是否某正则表达式的一个实例
//void judge_language(char* re, vector<DFAside_upper> simplest_DFAside_upper, DFA dfa_) {
//    int n = strlen(re);
//    char state = dfa_.start;
//    for (int i = 0; i < n; i++) {
//        state = find_tran_DFAstate(state, re[i], simplest_DFAside_upper);
//    }
//    if (find(dfa_.end.begin(), dfa_.end.end(), state) != dfa_.end.end()) {
//        cout << "true" << endl;
//    }
//    else {
//        cout << "false" << endl;
//    }
//}
//
//
//int main() {
//    string letter = "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z";
//    string digit = "1|2|3|4|5|6|7|8|9|0";
//    string str_number = "(" + digit + ")" + "(" + digit + ")*";
//    string str_identifier = "(" + letter + ")" + "(" + letter + "|" + digit + ")*";
//    char number[44], identifier[232], str_letter[105];
//    strcpy(number, str_number.c_str());
//    strcpy(identifier, str_identifier.c_str());
//    strcpy(str_letter, letter.c_str());
//    vector<DFAside_upper> DFA_identifier = simplest_DFA(str_letter);
//    DFA dfa_identifier = dfa;
//    dfa.end.clear();
//
//    // char re1[100] = "(a|b)*abb";
//    // vector<DFAside_upper> re1_simplest_dfa = simplest_DFA(re1);
//    // DFA dfa_re1 = dfa;
//    // dfa.end.clear();
//    // char re1_test1[100] = "aabb";
//    // judge_language(re1_test1, re1_simplest_dfa, dfa_re1);
//    // char re1_test2[100] = "aaabbbabb";
//    // judge_language(re1_test2, re1_simplest_dfa, dfa_re1);
//    // char re1_test3[100] = "abbab";
//    // judge_language(re1_test3, re1_simplest_dfa, dfa_re1);
//    // cout << endl;
//
//    // char re2[100] = "10|(0|11)0*11";
//    // vector<DFAside_upper> re2_simplest_dfa = simplest_DFA(re2);
//    // DFA dfa_re2 = dfa;
//    // dfa.end.clear();
//    // char re2_test1[100] = "10";
//    // judge_language(re2_test1, re2_simplest_dfa, dfa_re2);
//    // char re2_test2[100] = "110011";
//    // judge_language(re2_test2, re2_simplest_dfa, dfa_re2);
//    // char re2_test3[100] = "1001";
//    // judge_language(re2_test3, re2_simplest_dfa, dfa_re2);
//    // return 0;
//}