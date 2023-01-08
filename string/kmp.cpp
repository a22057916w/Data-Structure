#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;


// build the LPS(longest prefix and (also) suffix) table
// please refer to the reference source 1.
vector<int> buildLPS(string &txt) {
  vector<int> lps(txt.length(), 0);

  int i_sub = 1;          // index of substring of the given string (for suffix)
  int i_txt = i_sub - 1;  // index of the whole string (for prefix)

  // basically, we take txt as pattern to match its substring till the substring
  // becomes the whole string
  while(i_sub < txt.length()) {

    // if suffix == prefix, both index += 1
    if(txt[i_sub] == txt[i_txt]) {
      i_sub++;
      i_txt++;
      lps[i_sub] = i_txt;
    }
    // if i_txt == 0, it mean there are no prefix to match just do i_sub++
    else if(i_txt == 0)
      i_sub++;
    // if suffix != prefix, we use KMP strategy to find new prefix
    // so we do i_txt-- and refer to lps table
    else
      i_txt = lps[i_txt - 1];
  }

  return lps;
}

// the idea is to find the amount of gap that we want to shift
// while we mismathcing, to avoid the repeat comparison.
// please refer to the source 3
void KMPserach(string &txt, string &pat){
  vector<int> lps = buildLPS(pat);

  int i_txt = 0;
  int i_pat = 0;

  // think i_txt as i_sub, i_pat as i_txt in fnction buildLPS
  // except this time we don't nned to build the lps table
  while(i_txt < txt.length()) {
    if(txt[i_txt] == pat[i_pat]) {
      i_txt++;
      i_pat++;
    }
    else if(i_pat == 0)
      i_txt++;
    else {
      i_pat = lps[i_pat - 1];
    }

    // if i_pat == pattern's lenght means we find a match
    // return the index, reset i_pat, and keeping seraching
    if(i_pat == pat.length() - 1) {
      printf("Found pattern at index %d ", i_txt - i_pat);
      i_pat = lps[i_pat - 1];
    }
  }
}

int main() {
  string txt = "ABABDABACDABABCABAB";
  string pat = "ABABCABAB";

  KMPserach(txt, pat);

  return 0;
}

/*
reference:
  https://yeefun.github.io/kmp-algorithm-for-beginners/ (詳細建lps解說)
  https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/ （範例）
  https://stackoverflow.com/questions/13271856/understanding-knuth-morris-pratt-algorithm (圖示解說)
*/
