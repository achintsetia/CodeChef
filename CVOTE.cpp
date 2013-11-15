#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct cmp_str
{
  bool operator()(string const a, string const b)
  {
    return strcmp(a.c_str(), b.c_str()) < 0;
  }
};

int main( int argc, char** argv)
{
  map<string, string> chefCountry;
  map<string, int, cmp_str> chefVotes;
  map<string, int, cmp_str> countryVotes;

  int N, M;
  cin >> N >> M;

  string chef, country;

  for( int i=0; i<N; i++)
  {
    cin >> chef >> country;
    chefCountry[chef] = country;
    chefVotes[chef] = 0;
    countryVotes[country] = 0;
  }

  for( int i=0; i<M; i++)
  {
    cin >> chef;
    chefVotes[chef]++;
    countryVotes[chefCountry[chef]]++;
  }

  int maxVotes = 0;
  string maxChef, maxCountry;

  for( map<string, int, cmp_str>::iterator ii=chefVotes.begin();
    ii!=chefVotes.end(); ++ii)
  {
    //cout << (*ii).first << ": " << (*ii).second << endl;
    if( (*ii).second > maxVotes)
    {
      maxVotes = (*ii).second;
      maxChef = (*ii).first;
    }
  }

  maxVotes = 0;
  for( map<string, int, cmp_str>::iterator ii=countryVotes.begin();
    ii!=countryVotes.end(); ++ii)
  {
    //cout << (*ii).first << ": " << (*ii).second << endl;
    if( (*ii).second > maxVotes)
    {
      maxVotes = (*ii).second;
      maxCountry = (*ii).first;
    }
  }

  cout << maxCountry << endl;
  cout << maxChef << endl;
  return 0;
}
