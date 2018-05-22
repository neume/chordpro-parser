#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream in;

  in.open("sample.chordpro");
  string line = "";
  while(getline(in, line))
  {
    cout << line << endl;
  }
  return 0;
}
