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

#include "Ptensors0b.hpp"
#include "Ptensors1b.hpp"
#include "Ptensors2b.hpp"

using namespace ptens;
using namespace cnine;

PtensSession ptens_session;


int main(int argc, char** argv){

  cnine_session session;

  //cudaSetDevice(0);
  //cudaDeviceSynchronize();
  cudaDeviceReset(); // why do we need this?

  int nc=128;
  int niter=5;

  typedef Ptensors0b<float> Ptens0;
  typedef Ptensors1b<float> Ptens1;
  typedef Ptensors2b<float> Ptens2;

  AtomsPack xatoms=AtomsPack::random(300,0.2);
  Ptens0 X0=Ptens0(xatoms,channels=nc,filltype=3);
  Ptens1 X1=Ptens1(xatoms,channels=nc,filltype=3);
  Ptens2 X2=Ptens2(xatoms,channels=nc,filltype=3);

  Ptens0 X0g(X0,1); 
  Ptens1 X1g(X1,1); 
  Ptens2 X2g(X2,1); 

  AtomsPack yatoms=AtomsPack::random(300,0.2);
  Ptens1 Y0=Ptens1::gather(X0,yatoms);
  Ptens1 Y1=Ptens1::gather(X1,yatoms);
  Ptens1 Y2=Ptens1::gather(X1,yatoms);

  Ptens1 Y0g=Ptens1::gather(X0g,yatoms);
  Ptens1 Y1g=Ptens1::gather(X1g,yatoms);
  Ptens1 Y2g=Ptens1::gather(X1g,yatoms);

  {
    TimedFn timer("Ptensors1b","Gather 1<-1",Y1,X1);
    for(int i=0; i<niter; i++)
      //Ptens1 Y1=Ptens1::gather(X1,yatoms);
      Y1.gather(X1);
  }

  {
    TimedFn timer("Ptensors1b","GGather 1<-1",Y1g,X1g);
    for(int i=0; i<niter; i++)
      //Ptens1 Y1g=Ptens1::gather(X1g,yatoms);
      Y1g.gather(X1g);
  }


}

