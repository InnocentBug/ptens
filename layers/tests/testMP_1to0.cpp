#include "Cnine_base.cpp"
#include "CnineSession.hpp"

#include "LinmapLayers.hpp"
#include "ConcatLayers.hpp"
#include "EMPlayers.hpp"

using namespace ptens;
using namespace cnine;


int main(int argc, char** argv){

  cnine_session session;

  int N=8;
  Hgraph G=Hgraph::random(N,0.3);
  cout<<G.dense()<<endl;

  Ptensors0 L0=Ptensors0::sequential(N,1);
  Ptensors1 L1=concat(L0,G);
  PRINTL(L1);

  Ptensors0 L2=Ptensors0::zero(G.nhoods(0),1);
  add_msg(L2,L1,G);
  PRINTL(L2);
  
}
