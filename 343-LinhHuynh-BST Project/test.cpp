#include<bits/stdc++.h>
using namespace std;
bool isPrefix(const string& k1, const string& k2){//check k2 is substring (prefix) of k1 or not
int i = 0;
int j = 0;
size_t len1 = k1.size();
size_t len2 = k2.size();

while(i < len1 && j < len2){
    if(k1[i] != k2[j])
    return false;
    
    i++;
    j++;
}

//"Helloaaaa"
//"Hello"
if(i == len1 && j == len2)
    return true;

if(j == len2 && i < len1)
    return true;

//i = len1 and j < len2
return false;
} 
int main(){
    string k1;
    string k2;
    cin >> k1;
    cin >> k2;
    cout << isPrefix(k1, k2);
}