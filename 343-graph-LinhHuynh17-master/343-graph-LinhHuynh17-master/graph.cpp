#include "graph.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <utility>
#include <vector>
#include <climits>
#include <unordered_set>

using namespace std;

// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {
  graph_direction = directionalEdges;
}

// destructor
Graph::~Graph() {}

// @return total number of vertices
int Graph::verticesSize() const {
  return graph.size();
}

// @return total number of edges
int Graph::edgesSize() const {
  int noOfEdges = 0;
  for(auto it = graph.begin(); it != graph.end(); it++){ // it refers to an element of graph pair<key, value>
    noOfEdges += it->second.size();
    // it --> ("A", {("B", 8), ("C", 1)})
    // second: {("B", 8), ("C", 1)}
  }

  if(graph_direction == true){
    return noOfEdges;
  }else{
    return noOfEdges/2;
  }
}

// @return number of edges from given vertex, -1 if vertex not found
int Graph::vertexDegree(const string &label) const {
  if(graph.count(label)){
    return graph.at(label).size();
  }else{
    return -1;
  }
}

// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &label) {
  if(graph.count(label)){
    return false;
  }else{
    graph.insert(make_pair(label, vector< pair<string, int> >()));
    return true;
  }
}

/** return true if vertex already in graph */
bool Graph::contains(const string &label) const {
  return graph.count(label);
}

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &label) const {
  if(graph.count(label)){
    string res = "";
    // for(auto adj : graph.at(label)){
    //   res += adj.first + "(" + to_string(adj.second) + ")";
    // }
    if(graph.at(label).size() > 0){
      auto vt = graph.at(label);
      sort(vt.begin(), vt.end(), [](pair<string, int>& p1, pair<string, int>& p2){
        return p1.second < p2.second;
      }); //sort vt by weight
      int len = vt.size(); //vt is adjacent list of label
      for(int i = 0; i < len-1; i++){
        res += vt[i].first + "(" + to_string(vt[i].second) + "),";
      }
      res += vt[len-1].first + "(" + to_string(vt[len-1].second) + ")";
    }
    return res;
  }else{
    return ""; 
  }
}

// @return true if successfully connected
bool Graph::connect(const string &from, const string &to, int weight) {
  if(from == to){
    if(!graph.count(from)){
      graph.insert(make_pair(from, vector< pair<string, int> >()));
    }
    return false;
  }else{ //from != to
    if(!graph.count(from)){ //check if 'from' is in graph or not
      graph.insert(make_pair(from, vector< pair<string, int> >()));
    }
    if(!graph.count(to)){ //check if 'to' is in graph or not
      graph.insert(make_pair(to, vector< pair<string, int> >()));
    }

    //check from and to are already connected or not
    // if directed: from -> to
    // undirected: from -> to and to -> from
    for(auto adj : graph.at(from)){
      if(adj.first == to){
        return false;
      }
    }

    
    //from and two has no edge
    if(graph_direction){
      graph[from].push_back(make_pair(to, weight));
    }else{
      graph[from].push_back(make_pair(to, weight));
      graph[to].push_back(make_pair(from, weight));
    }
    return true;
  }
}

bool Graph::disconnect(const string &from, const string &to) {
  if(graph.count(from) && graph.count(to) && from != to){
    if(graph_direction == true){

      for(auto it = graph[from].begin(); it != graph[from].end(); it++){ //graph[from]: return reference to the vector that is adjacent list of vertex from
        if(it->first == to){
          graph[from].erase(it); //remove the vertex that is in the adjacent list of 'from' --> disconnect edge (from, to)
          return true;
        }
      }

      return false;
    }else{
      bool res = false;
      for(auto it = graph[from].begin(); it != graph[from].end(); it++){ //graph[from]: return reference to the vector that is adjacent list of vertex from
        if(it->first == to){
          graph[from].erase(it); //remove the vertex that is in the adjacent list of 'from' --> disconnect edge (from, to)
          res = true;
        }
      }

      for(auto it = graph[to].begin(); it != graph[to].end(); it++){
        if(it->first == from){
          graph[to].erase(it); 
        }
      }

      return res;
    }
  }

  return false;
}

// depth-first traversal starting from given startLabel
void Graph::dfs(const string &startLabel, void visit(const string &label)) {
  if(graph.count(startLabel)){
    map<string, int> vst;
    for(auto it = graph.begin(); it != graph.end(); ++it) {
      vst[it->first] = 0; // [] operator will create a new entry if not found
    }
    stack<string> st;
    st.push(startLabel);
    vst[startLabel] = 1;
    while(!st.empty()){
      string vertex = st.top();
      st.pop();
      visit(vertex);
      // for(auto adj : graph[vertex]){
      //   if(!vst[adj.first]){
      //     st.push(adj.first);
      //     vst[adj.first] = 1;
      //   }
      // }
      for (auto it = graph[vertex].rbegin(); it != graph[vertex].rend(); ++it) {
        if(!vst[it->first]){
            st.push(it->first);
            vst[it->first] = 1;
          }
      }
    }
  }
}

// breadth-first traversal starting from startLabel
void Graph::bfs(const string &startLabel, void visit(const string &label)) {
  if(graph.count(startLabel)){
    map<string, int> vst;
    for(auto it = graph.begin(); it != graph.end(); ++it) {
      vst[it->first] = 0; // [] operator will create a new entry if not found
    }
    queue<string> q;
    q.push(startLabel);
    vst[startLabel] = 1;
    while(!q.empty()){
      string vertex = q.front();
      q.pop();
      visit(vertex);
      for(auto adj : graph[vertex]){
        if(!vst[adj.first]){
          q.push(adj.first);
          vst[adj.first] = 1;
        }
      }
    }
  }
}

// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>> Graph::dijkstra(const string &startLabel) const {
  map<string, int> weights;
  map<string, string> previous;
  // TODO(student) Your code here
  map<string, int> cost;
  if(contains(startLabel) == true){
    map<string, bool> vst;
    priority_queue <pair<string, int>, vector <pair<string, int>>, greater_cmp <pair<string, int>>> pq;

    for(auto it = graph.begin(); it != graph.end(); it++){
      cost[it->first] = INT_MAX;
      vst[it->first] = false;
    }

    cost[startLabel] = 0;
    pq.push(make_pair(startLabel, 0));

    // string previous_vertex = startLabel;

    while(!pq.empty()){
      pair<string, int> e = pq.top();
      pq.pop();

      string node = e.first;
      if(vst[node] == true){
        continue;
      }

      vst[node] = true;
      // previous[node] = previous_vertex;
      // previous_vertex = node;
      weights[node] = cost[node];

      for(auto temp : graph.at(node)){
        string cv = temp.first;
        int w = temp.second;
        if(cost[cv] > cost[node] + w){
          cost[cv] = cost[node] + w;
          pq.push(make_pair(cv, cost[cv]));
          previous[cv] = node;
        }
      }
    }

    weights.erase(startLabel);
    previous.erase(startLabel); 

  }
  
  return make_pair(weights, previous);
}

// minimum spanning tree using Prim's algorithm

int Graph::mstPrim(const string &startLabel, void visit(const string &from, const string &to, int weight)) const {
  if(contains(startLabel)){
    map<string, int> dist;
    map<string, bool> vst;
    priority_queue <pair<string, int>, vector <pair<string, int>>, greater_cmp <pair<string, int>> > pq;
    for(auto it = graph.begin(); it != graph.end(); it++){
      dist[it->first] = INT_MAX;
      vst[it->first] = false;
    }

    dist[startLabel] = 0;
    pq.push(make_pair(startLabel, 0));
    string previous_vertex = startLabel;
    while(!pq.empty()){
        pair<string, int> p = pq.top(); 
        pq.pop();
        string u = p.first;
        if(vst[u]) continue;
        vst[u] = true;
        if(u != startLabel){
          int wei = p.second;
          // if in adjcentlist of u has vertex v that v-u = wei
          for(auto tp: graph.at(u)){
            if(tp.second == wei){
              visit(tp.first, u, wei);
              break;
            }
          }
        }
        // visit()
        for (auto tmp : graph.at(u))
        {
            string v = tmp.first;
            int wei = tmp.second;
            if(wei < dist[v] && vst[v] == 0) {
                dist[v] = wei;
                pq.push(make_pair(v, dist[v]));
            }
        }
    }

    int res = 0;
    for(auto it = dist.begin(); it != dist.end(); it++){
      res += it->second;
    }

    return res;
  }

  return -1;
}

int Graph::mstKruskal(const string &startLabel, void visit(const string &from, const string &to, int weight)) const {
  if(!contains(startLabel)) return -1;

  int res = 0;
  map<string, int> ranked;
  map<string, string> parent;
  vector<edge> e;

  for(auto it = graph.begin(); it != graph.end(); it++){
    for(auto& tp: it->second){
      if(it->first.compare(tp.first) < 0){
        e.push_back({it->first, tp.first, tp.second});
      }else if(it->first.compare(tp.first) > 0){
        e.push_back({tp.first, it->first, tp.second});
      }
    }

    ranked[it->first] = 0;
    parent[it->first] = "Null";
  }
  

  sort(e.begin(), e.end(), [](edge a,edge b){
    return a.w < b.w;
  });
  int i = 0, j = 0;
  int n = e.size()/2;
  int m = graph.size();
  while(i < n-1 && j < m){
    string u = root(e[j].u, parent);
    string v = root(e[j].v, parent);
    if(u == v) {
      j+=2;
    }
    else{
        merge(u, v, ranked, parent);
        res += e[j].w;
        i++;
        visit(u, v, e[j].w);
    }
  }
  return res;
}

// read a text file and create the graph
bool Graph::readFile(const string &filename) {
  ifstream myfile(filename);
  if (!myfile.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return false;
  }
  int edges = 0;
  int weight = 0;
  string fromVertex;
  string toVertex;
  myfile >> edges;
  for (int i = 0; i < edges; ++i) {
    myfile >> fromVertex >> toVertex >> weight;
    connect(fromVertex, toVertex, weight);
  }
  for(auto it = graph.begin(); it != graph.end(); it++){
    sort(it->second.begin(), it->second.end(), [](pair<string, int>& p1, pair<string, int>& p2){
      return p1.first.compare(p2.first) < 0;
    });
  }
  myfile.close();
  return true;
}
