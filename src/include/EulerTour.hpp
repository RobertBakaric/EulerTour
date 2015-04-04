/*
 * EulerTour.hpp
 * 
 * Copyright 2015 Robert Bakaric <rbakaric@irb.hr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <vector>
#include <unordered_map>

using namespace std;



/* NOTE:
 *  graph is described by two integer vectors. Given an 
 *  index position i=[0..|vec|] the integer label on that 
 *  position in the first vector marks the parent 
 *  (predecessor) vertex and the integer label in the second 
 *  vector on that position marks its child (succesor) vertex 
 */


/* Graph container */

template <typename Tint>
class Graph{

  protected:
/* Data Container */
  unordered_map<Tint, vector<Tint>> GraphMap;

/* Functions */ 
  void MakeGraph(const vector<Tint>& parent, const vector<Tint>& child);

  public:

/* Constructor */
  Graph(const vector<Tint>& parent, const vector<Tint>& child);
/* Destructor */
  ~Graph();
/* Explicite Constructor */
  void make(const vector<Tint>& parent, const vector<Tint>& child);
/* Explicite destructor */
  void destroy();

};



/* Constructors */

template <typename Tint>
Graph<Tint>::Graph(const vector<Tint>& parent, const vector<Tint>& child){
  MakeGraph(parent, child);
}

template <typename Tint>
void Graph<Tint>::make(const vector<Tint>& parent, const vector<Tint>& child){
  MakeGraph(parent, child);
}


template <typename Tint>
void Graph<Tint>::MakeGraph(const vector<Tint>& parent, const vector<Tint>& child){
  for (Tint i = 0; i< parent.size(); i++){
    GraphMap[parent[i]].push_back(child[i]);
  }
}


/* Destructors */

template <typename Tint>
Graph<Tint>::~Graph(){
  GraphMap.clear();
}

template <typename Tint>
void Graph<Tint>::destroy(){
  GraphMap.clear();
}



/* EulerTour class */

template <typename Tint>
class Euler : protected Graph<Tint>{

/* Data Containers */
  vector<Tint> DepthVec;
  vector<Tint> VertexIdVec;
  
/* Internal Functions */
  
  void DepthFirstTrav(const Tint vertex, Tint depth, Tint Flag);
  
  public:
  
/* Constructor */
  Euler(const Tint start, const vector<Tint>& parent, const vector<Tint>& child);
  Euler(const vector<Tint>& parent, const vector<Tint>& child);
  Euler();

/* Destructor */
  ~Euler();

/* External Functions */
  void make(const Tint start, const vector<Tint>& parent, const vector<Tint>& child);
  void make(const vector<Tint>& parent, const vector<Tint>& child);
  void destroy();

  void Traverse(Tint start);
  void Clean();
  vector<Tint>& GetDepthVec();
  vector<Tint>& GetVertexIdVec();


};


/* Constructors */
template <typename Tint>
Euler<Tint>::Euler(const Tint start,const vector<Tint>& parent, const vector<Tint>& child) : Graph<Tint>(parent,child){
  Traverse(start);
}

template <typename Tint>
Euler<Tint>::Euler(const vector<Tint>& parent, const vector<Tint>& child) : Graph<Tint>(parent,child){}

template <typename Tint>
Euler<Tint>::Euler() : Graph<Tint>(){}



template <typename Tint>
void Euler<Tint>::make(const Tint start,const vector<Tint>& parent, const vector<Tint>& child) {
  this->make(parent,child);
  Traverse(start);
}

template <typename Tint>
void Euler<Tint>::make(const vector<Tint>& parent, const vector<Tint>& child){
  this->make(parent,child);
}




/* Destructors */
template <typename Tint>
Euler<Tint>::~Euler(){
  vector<Tint>().swap(DepthVec);
  vector<Tint>().swap(VertexIdVec);
}

template <typename Tint>
void Euler<Tint>::destroy(){
  vector<Tint>().swap(DepthVec);
  vector<Tint>().swap(VertexIdVec);
  this->destroy();
}





/* Functions */

template <typename Tint>
void Euler<Tint>::DepthFirstTrav(const Tint vertex, Tint depth, Tint Flag){
  for(Tint i = 0;i< this->GraphMap[vertex].size();i++){ 
    if(Flag == 0){
      DepthVec.push_back(--depth);
      VertexIdVec.push_back(vertex);
    }
    DepthVec.push_back(++depth);
    VertexIdVec.push_back(this->GraphMap[vertex][i]);
    Flag = 0;
    if(this->GraphMap.find(this->GraphMap[vertex][i]) != this->GraphMap.end()){
      DepthFirstTrav(this->GraphMap[vertex][i], depth, 1);
      DepthVec.push_back(depth);
      VertexIdVec.push_back(this->GraphMap[vertex][i]);
    }
  }
}

template <typename Tint>
vector<Tint>& Euler<Tint>::GetDepthVec(){
  return DepthVec;
}

template <typename Tint>
vector<Tint>& Euler<Tint>::GetVertexIdVec(){
  return VertexIdVec;
}

template <typename Tint>
void Euler<Tint>::Clean(){
  vector<Tint>().swap(DepthVec);
  vector<Tint>().swap(VertexIdVec);
}

template <typename Tint>
void Euler<Tint>::Traverse(Tint start){
  DepthVec.push_back(0);
  VertexIdVec.push_back(start);
  DepthFirstTrav(start, 0,1);
  DepthVec.push_back(0);
  VertexIdVec.push_back(start);
}

