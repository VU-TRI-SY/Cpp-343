#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    bool dir;
    Graph(bool direction = true){
        dir = direction;
    }

    void display(){
        cout << dir << endl;
    }
};

int main(){
    Graph g1(true);
    Graph g2(false);
    g1.display();
    g2.display();
}