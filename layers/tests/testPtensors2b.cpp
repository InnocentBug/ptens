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
#include "Ptens_base.cpp"
#include "Ptensors0b.hpp"
#include "Ptensors1b.hpp"
#include "Ptensors2b.hpp"

using namespace ptens;
using namespace cnine;

PtensSession ptens_session;


int main(int argc, char** argv){

  typedef Ptensors0b<float> Ptens0;
  typedef Ptensors1b<float> Ptens1;
  typedef Ptensors2b<float> Ptens2;

  AtomsPack xatoms=AtomsPack::random(8,8,0.5);
  Ptens0 X0=Ptens0(xatoms,channels=1,filltype=4);
  Ptens1 X1=Ptens1(xatoms,channels=1,filltype=4);
  Ptens2 X2=Ptens2(xatoms,channels=1,filltype=4);

  AtomsPack yatoms=AtomsPack::random(8,8,0.5);
  auto Y0=Ptens2::gather(X0,yatoms);
  cout<<Y0<<endl;

  auto Y1=Ptens2::gather(X1,yatoms);
  cout<<Y1<<endl;

  auto Y2=Ptens2::gather(X2,yatoms);
  cout<<Y2<<endl;

  exit(0);
  Ptens0 X0g=Ptens0::zeros_like(X0);
  Ptens1 X1g=Ptens1::zeros_like(X1);
  Ptens2 X2g=Ptens2::zeros_like(X2);

  X0g.add_gather_back(Y0);
  cout<<X0g<<endl;
  X1g.add_gather_back(Y1);
  cout<<X1g<<endl;
  X2g.add_gather_back(Y2);
  cout<<X2g<<endl;


  //Ptensors1b<float> Ab(A);
  //cout<<Ab<<endl;

}

