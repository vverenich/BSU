#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

void LowerCase(std::string& st) {
  for (int i = 0; i < st.length(); ++i) {
    st[i] = tolower(st[i]);
  }
}

int main() {
  std::string startName;
  int k, n, m;
  std::cin >> startName >> k >> n >> m;
  LowerCase(startName);
  std::map<std::string, int> map;
  map.insert({startName, 0});
  for (int i = 0; i < n; ++i) {
    std::string name;
    std::cin >> name;
    LowerCase(name);
    map.insert({name, i});
  }
  int num = 1;
  for (std::map<std::string, int>::iterator it = map.begin(); it != map.end();
       ++it) {
    if (it->first != startName) {
      it->second = num;
      ++num;
    }
  }
  std::vector<std::set<int>> graph(map.size());

  for (int i = 0; i < m; ++i) {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    LowerCase(s1);
    LowerCase(s2);
    graph[map[s1]].insert(map[s2]);
    graph[map[s2]].insert(map[s1]);
  }
  std::queue<int> q;
  q.push(map[startName]);
  std::vector<std::pair<bool, int>> used(map.size());
  used[map[startName]] = std::make_pair(true, 0);
  int number = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (std::set<int>::iterator i = graph[v].begin(); i != graph[v].end();
         ++i) {
      int to = *i;
      if (!used[to].first) {
        q.push(to);
        used[to] = std::make_pair(true, used[v].second + 1);
        if (used[to].second < k + 1) {
          ++number;
        }
      }
    }
  }
  std::cout << number << "\n";
  for (int i = 1; i < k + 1; ++i) {
    for (std::map<std::string, int>::iterator it = map.begin(); it != map.end();
         ++it) {
      if (used[it->second].second == i) {
        std::cout << it->first << " " << used[it->second].second << "\n";
      }
    }
  }
}