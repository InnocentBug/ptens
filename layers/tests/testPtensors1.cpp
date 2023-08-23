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
#include "CnineSession.hpp"

#include "LinmapLayers.hpp"
#include "EMPlayers.hpp"

using namespace ptens;
using namespace cnine;

PtensSession ptens_session;


int main(int argc, char** argv){

  //cnine_session session;

  if(false){
    Ptensors1 A=Ptensors1::randn({{1,2,3},{3,5},{2}},2);
    cout<<A<<endl;
    auto Ag=A.to_device(1);
    cout<<Ag<<endl;
    auto B=A.to_device(0);
    cout<<B<<endl;
    exit(0);
  }

  Ptensors1 A=Ptensors1::sequential(2,3,1);
  cout<<A<<endl;
  cout<<linmaps0(A)<<endl;
  cout<<linmaps1(A)<<endl;
  cout<<linmaps2(A)<<endl;
  cout<<"-----"<<endl;

  #ifdef _WITH_CUDA
  Ptensors1 Ag(A,1);
  cout<<linmaps0(Ag)<<endl;
  cout<<linmaps1(Ag)<<endl;
  cout<<linmaps2(Ag)<<endl;
  #endif

}
