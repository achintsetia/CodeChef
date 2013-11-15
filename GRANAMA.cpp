/* 
 * File:   main.cpp
 * Author: Achint
 *
 * Created on December 2, 2012, 4:51 PM
 */

//#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

/*
 * 
 */
int histR[26], histS[26];

void makeHist(string R, string S)
{
    for( int i=0; i<26; i++) histR[i] = 0;
    for( int i=0; i<26; i++) histS[i] = 0;
    
    int sizeR = R.size();
    int sizeS = S.size();
    for(int i=0; i<sizeR; i++)
        histR[R[i] - 'a']++;
    
    for(int i=0; i<sizeS; i++)
        histS[S[i] - 'a']++;
}
bool compareHists()
{
    for( int i=0; i<26; i++)
        if(histR[i] != histS[i])
            return false;
    return true;    
}

bool sameContent()
{
    for( int i=0; i<26; i++)
        if((histR[i] > 0 && histS[i] == 0) ||(histR[i] == 0 && histS[i] > 0))
            return false;
    return true;
}
int main(int argc, char** argv)
{
    int T;
    string R,S;
    
    cin >> T;
    for( int i=0; i<T; i++)
    {
        cin >> R >> S;
        makeHist(R, S);
        if( !sameContent())
            cout << "YES" << endl;
        else if( compareHists())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
