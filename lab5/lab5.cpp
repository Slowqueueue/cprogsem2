//Реализовать рекурсивный алгоритм построения цепочки из имеющегося набора костей домино.
#define  _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class domino {
public:
    int left, right;

    domino(int left, int right) {
        this->left = left; this->right = right;
    }

    domino rotate() {
        domino* dom = new domino(right, left);
        return *dom;
    }

    string make_string() {
        return "[" + to_string(left) + "|" + to_string(right) + "]";
    }
};

bool is_suitable(domino dom, vector <domino> chained) {
    return chained.empty() || chained[chained.size() - 1].right == dom.left;
}

void chain_out(vector <domino> chained) {
    for (int i = 0; i < chained.size(); i++) cout << chained.at(i).make_string() << " ";
    cout << endl;
}

void make_chain(vector <domino>& chained, vector <domino> initial) {
    if (initial.empty()) return;
    for (int i = 0; i < initial.size(); ++i) {
        domino dom = initial.at(i);
        if (is_suitable(dom, chained)) {
            chained.push_back(dom);
            chain_out(chained);
            domino buffer = initial.at(i);
            initial.erase(initial.begin() + i);
            make_chain(chained, initial);
            if (initial.empty()) return;
            initial.insert(initial.begin() + i, buffer);
            chained.erase(chained.end() - 1);
        }
        else {
            dom = dom.rotate();
            if (is_suitable(dom, chained)) {
                chained.push_back(dom);
                chain_out(chained);
                domino buffer = initial.at(i);
                initial.erase(initial.begin() + i);
                make_chain(chained, initial);
                if (initial.empty()) return;
                initial.insert(initial.begin() + i, buffer);
                chained.erase(chained.end() - 1);
            }
        }
    }
}

int main() {
    vector <domino> unchained, chained;
    domino* dom;
    int num = 0, domleft = 0, domright = 0;
    printf("Enter number of dominoes: \n");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        printf("Enter domino #%d(N N): \n", i + 1);
        scanf("%d", &domleft);
        scanf("%d", &domright);
        dom = new domino(domleft, domright);
        unchained.push_back(*dom);
    }
    make_chain(chained, unchained);
    cin.get();
    return 0;
}