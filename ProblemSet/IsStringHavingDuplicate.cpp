#include<bits/stdc++.h>
using namespace std;
bool isHavingDuplicate(string input)
{
    int n = input.length();
    if(n<1)
    {
        return false;
    }
    bool hash[256]={0,};int i = 0;
    while(i<=n-1)
    {
        if(hash[input[i]])
        {
            return true;
        }
        hash[input[i]] = true;
        i++;
    }
    return false;
}
int main()
{
    string input[] = {"abccba","abc","a",""};
    int n = sizeof(input)/sizeof(input[0]);
    for(int i =0;i<n;i++)
    {
        if(isHavingDuplicate(input[i]))
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}
