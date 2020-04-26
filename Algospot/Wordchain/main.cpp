#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int adj[26][26];
vector<string> g[26][26];
int indegree[26];
int outdegree[26];

void getEulerCircuit(int here, vector<int>& circuit) {
  for (int there = 0; there < 26; there++) {
    while (adj[here][there] > 0) {
      adj[here][there]--;
      getEulerCircuit(there, circuit);
    }
  }
  circuit.push_back(here);
}

vector<int> getEulerCircuitOrTrail() {
  vector<int> circuit;
  for (int i = 0; i < 26; i++) {
    if (outdegree[i] == indegree[i] + 1) {
      getEulerCircuit(i, circuit);
      return circuit;
    }
  }

  for (int i = 0; i < 26; i++) {
    if (outdegree[i] > 0) {
      getEulerCircuit(i, circuit);
      return circuit;
    }
  }
  return circuit;
}



bool checkEuler() {
  int outv = 0;
  int inv = 0;
  for (int i = 0; i < 26; i++) {
    int delta = outdegree[i] - indegree[i];
    if (delta == 1) outv++;
    else if (delta == 0) continue;
    else if (delta == -1) inv++;
    else return false;
  }
  if ((inv == 1 && outv == 1) || (inv == 0 && outv == 0)) return true;
  else return false;
}

bool checkGraph() {
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      if (g[i][j].size() != 0) return false;
    }
  }
  return true;
}

int main() {
  freopen("sample_input.txt", "r", stdin);
  int C;
  cin >> C;
  for (int c = 0; c < C; c++) {

    memset(adj, 0, sizeof(adj));
    memset(indegree, 0, sizeof(indegree));
    memset(outdegree, 0, sizeof(outdegree));

    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        g[i][j].clear();
      }
    }
    
    int n;
    cin >> n;

    int start_v;

    for (int i = 0; i < n; i++) {
      string s;
      
      cin >> s;
      char c1 = s[0] - 'a';
      char c2 = s[s.size() - 1] - 'a';

      adj[c1][c2]++;
      g[c1][c2].push_back(s);
      outdegree[c1]++;
      indegree[c2]++;

      if (i == 0) start_v = c1;
    }

    if (!checkEuler()) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    
    vector<int> circuit = getEulerCircuitOrTrail();
    
    if (circuit.size() != n + 1) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }

    reverse(circuit.begin(), circuit.end());

    for (int i = 0; i < circuit.size() - 1; i++) {
      cout << g[circuit[i]][circuit[i+1]].back() << ' ';
      g[circuit[i]][circuit[i + 1]].pop_back();
    }
    cout << endl;


  }
  return 0;
}