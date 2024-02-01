/*
 * This file is part of ptens, a C++/CUDA library for permutation 
 * equivariant message passing. 
 *  
 * Copyright (c) 2023, Imre Risi Kondor
 *
 * This source code file is subject to the terms of the noncommercial 
 * license distributed with cnine in the file LICENSE.TXT. Commercial 
 * use is prohibited. All redistributed versions of this file (in 
 * original or modified form) must retain this copyright notice and 
 * must be accompanied by a verbatim copy of the license. 
 *
 */

#include "Cnine_base.cpp"

#include "BatchedPtensors1b.hpp"
#include "BatchedSubgraphLayer0b.hpp"
//#include "BatchedSubgraphLayer1b.hpp"

using namespace ptens;
using namespace cnine;

PtensSession ptens::ptens_session;

typedef BatchedPtensors0b<float> BPtens0;
typedef BatchedPtensors1b<float> BPtens1;


int main(int argc, char** argv){

  int n=6;

  Ggraph g0=Ggraph::random(n);
  BatchedGgraph G({g0,g0,g0});
  cout<<G<<endl;

  Subgraph trivial=Subgraph::trivial();

  AtomsPack xatoms0=AtomsPack::random(n,0.5);
  BatchedAtomsPack xatoms({xatoms0,xatoms0,xatoms0});

  BPtens1 X1=BPtens1(xatoms,channels=3,filltype=3);

  BatchedSubgraphLayer0b<float> U(X1,G,trivial);
  cout<<U<<endl;

  cout<<666666<<endl;

  Ggraph g1=Ggraph::from_edges(g0.edge_list());
  g1.cache(0);
  Ltensor<float> M({3*n,3},3);
  Ltensor<float> P({6*g0.nedges(),3},3);
  //cout<<M<<endl;

  auto V=BatchedSubgraphLayer0b<float>::from_vertex_features({0,0,0},M);
  cout<<V<<endl;
  
  auto W=BatchedSubgraphLayer0b<float>::from_edge_features({0,0,0},P);
  cout<<W<<endl;
  


}
