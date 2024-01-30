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

#ifndef _ptens_BatchedSubgraphLayer1b
#define _ptens_BatchedSubgraphLayer1b

#include "BatchedGgraph.hpp"
#include "Subgraph.hpp"
#include "BatchedPtensors1b.hpp"


namespace ptens{


  template<typename TYPE> 
  class BatchedSubgraphLayer1b: public BatchedPtensors1b<TYPE>{
  public:

    typedef BatchedPtensors1b<TYPE> BASE;
    typedef cnine::Ltensor<TYPE> TENSOR;

    typedef BatchedAtomsPackN<AtomsPack1obj<int> > BatchedAtomsPack1;

    using BASE::BASE;
    using BASE::atoms;
    using BASE::add_gather;
    using BASE::get_nc;
    using BASE::get_grad;
    using BASE::view3;

    using TENSOR::get_arr;

    const BatchedGgraph G;
    const Subgraph S;


  public: // ----- Constructors ------------------------------------------------------------------------------


    //BatchedSubgraphLayer0b(const BatchedGgraph& _G, const TENSOR& x):
    //BASE(x), G(_G), S(Subgraph::trivial()){}

    BatchedSubgraphLayer1b(const BatchedGgraph& _G, const Subgraph& _S, const BASE& x):
      BASE(x), G(_G), S(_S){}

    BatchedSubgraphLayer1b(const BatchedGgraph& _G, const Subgraph& _S, const BatchedAtomsPack1& atoms, const TENSOR& x):
      BASE(atoms,x), G(_G), S(_S){}

    BatchedSubgraphLayer1b(const BatchedGgraph& _G, const int nc, const int fcode=0, const int _dev=0):
      G(_G), S(Subgraph::trivial()), BASE(_G.getn(),nc,fcode,_dev){}

    BatchedSubgraphLayer1b(const BatchedGgraph& _G, const Subgraph& _S, const BatchedAtomsPack& _atoms, const int nc, const int fcode, const int _dev=0):
      G(_G), S(_S), BASE(_atoms,nc,fcode,_dev){}

    /*
    static BatchedSubgraphLayer0b cat(const vector<BatchedSubgraphLayer0b>& list){
      vector<AtomsPack0> v;
      for(auto& p:list)
	v.push_back(p.atoms);
      return BatchedSubgraphLayer0b(AtomsPack0::cat(v),cnine::Ltensor<TYPE>::stack(0,list));
    }
    */


  public: // ----- Spawning ----------------------------------------------------------------------------------


    BatchedSubgraphLayer1b copy() const{
      return BatchedSubgraphLayer1b(G,S,BASE::copy());
    }

    BatchedSubgraphLayer1b copy(const int _dev) const{
      return BatchedSubgraphLayer1b(G,S,BASE::copy(_dev));
    }

    BatchedSubgraphLayer1b zeros_like() const{
      return BatchedSubgraphLayer1b(G,S,BASE::zeros_like());
    }

    BatchedSubgraphLayer1b zeros_like(const int nc) const{
      return BatchedSubgraphLayer1b(G,S,BASE::zeros_like(nc));
    }

    BatchedSubgraphLayer1b gaussian_like() const{
      return BatchedSubgraphLayer1b(G,S,BASE::gaussian_like());
    }

    static BatchedSubgraphLayer1b* new_zeros_like(const BatchedSubgraphLayer1b& x){
      return new BatchedSubgraphLayer1b(x.G,x.S,x.TENSOR::zeros_like());
    }
    
    //BatchedSubgraphLayer0b(const BatchedSubgraphLayer0b& x, const int _dev):
    //BatchedSubgraphLayer0b(x.G,x.S,BASE(x,_dev)){}


  public: // ---- Access -------------------------------------------------------------------------------------

    /*
    const cnine::Rtensor3_view view3() const{
      int K=S.getn();
      int nc=get_nc();
      return cnine::Rtensor3_view(const_cast<float*>(get_arr()),dim(0)/K,K,nc,K*nc,nc,1);
    }

    cnine::Rtensor3_view view3(){
      int K=S.getn();
      int nc=get_nc();
      return cnine::Rtensor3_view(get_arr(),dim(0)/K,K,nc,K*nc,nc,1);
    }
    */

  public: // ---- Message passing between subgraph layers -----------------------------------------------------


    template<typename SOURCE>
    static BatchedSubgraphLayer1b linmaps(const SOURCE& x){
      BatchedSubgraphLayer1b R(x.G,x.S,x.get_atoms(),x.get_nc()*vector<int>({1,2,5})[x.getk()],0,x.get_dev());
      R.add_linmaps(x);
      return R;
    }

    template<typename SOURCE>
    BatchedSubgraphLayer1b(const SOURCE& x, const Subgraph& _S):
      BatchedSubgraphLayer1b(x.G,_S,x.G.subgraphs(_S),x.get_nc()*vector<int>({1,2,5})[x.getk()],0,x.dev){
      add_gather(x);
    }

    template<typename SOURCE>
    BatchedSubgraphLayer1b(const SOURCE& x, const BatchedGgraph& _G, const Subgraph& _S):
      BatchedSubgraphLayer1b(_G,_S,_G.subgraphs(_S),x.get_nc()*vector<int>({1,2,5})[x.getk()],0,x.dev){
      add_gather(x);
    }


  public: // ---- Autobahn -----------------------------------------------------------------------------------


    // abstract these into a separate template 
    BatchedSubgraphLayer1b autobahn(const TENSOR& W, const TENSOR& B) const{
      S.make_eigenbasis();
      int K=S.getn();
      PTENS_ASSRT(W.dims.size()==3);
      PTENS_ASSRT(W.dims[0]==S.obj->eblocks.size());
      PTENS_ASSRT(W.dims[1]==get_nc());
      PTENS_ASSRT(B.dims.size()==2);
      PTENS_ASSRT(B.dims[0]==S.obj->eblocks.size());
      PTENS_ASSRT(B.dims[1]==W.dims[2]);

      BatchedSubgraphLayer1b R=zeros_like(W.dims[2]);
      for_each_eigenslice(R.view3(K),view3(K),[&]
	(cnine::Rtensor2_view rslice, cnine::Rtensor2_view xslice, const int b){
	  rslice.add_matmul_AA(xslice,W.view3().slice0(b));
	  rslice.add_broadcast0(B.view2().slice0(b));	
	},true);
      return R;
    }


   void add_autobahn_back0(const BatchedPtensors1b<TYPE>& r, const TENSOR& W){
      S.make_eigenbasis();
      int K=S.getn();
      PTENS_ASSRT(W.dims.size()==3);
      PTENS_ASSRT(W.dims[0]==S.obj->eblocks.size());
      PTENS_ASSRT(W.dims[1]==get_nc());
      PTENS_ASSRT(W.dims[2]==r.get_nc());

      for_each_eigenslice(get_grad().view3(K),r.get_grad().view3(K),[&]
	(cnine::Rtensor2_view rslice, cnine::Rtensor2_view xslice, const int b){
	  rslice.add_matmul_AT(xslice,W.view3().slice0(b));
	},true);
    }


    void add_autobahn_back1_to(const TENSOR& W, const TENSOR& B, const BatchedPtensors1b<TYPE>& r){
      S.make_eigenbasis();
      int K=S.getn();
      PTENS_ASSRT(W.dims.size()==3);
      PTENS_ASSRT(W.dims[0]==S.obj->eblocks.size());
      PTENS_ASSRT(W.dims[1]==get_nc());
      PTENS_ASSRT(W.dims[2]==r.get_nc());
      PTENS_ASSRT(B.dims.size()==2);
      PTENS_ASSRT(B.dims[0]==S.obj->eblocks.size());
      PTENS_ASSRT(B.dims[1]==r.get_nc());

      for_each_eigenslice(view3(K),r.get_grad().view3(K),[&]
	(cnine::Rtensor2_view xslice, cnine::Rtensor2_view rslice, const int b){
	  W.view3().slice0(b).add_matmul_TA(xslice,rslice); // OK
	  rslice.sum0_into(B.view2().slice0(b)); 
	});
    }


    void for_each_eigenslice(const cnine::Rtensor3_view x, const cnine::Rtensor3_view y,
      std::function<void(const cnine::Rtensor2_view& xslice, const cnine::Rtensor2_view& yslice, const int b)> lambda,
			     const bool inplace_add=false) const{
      S.make_eigenbasis();
      int N=x.n0;
      int K=x.n1;
      int xnc=x.n2;
      int ync=y.n2;
      int nblocks=S.obj->eblocks.size();

      cnine::Rtensor2_view E=S.obj->evecs.view2();
      const auto& blocks=S.obj->eblocks;

      PTENS_ASSRT(y.n0==N);
      PTENS_ASSRT(y.n1==K);
      PTENS_ASSRT(E.n0==K);
      PTENS_ASSRT(E.n1==K);
      PTENS_ASSRT(x.dev==y.dev);

      auto X=cnine::Ltensor<float>({N,K,xnc},0,x.dev);
      if(!inplace_add) X.view3().add_mprod(E.transp(),x);

      auto Y=cnine::Tensor<float>({N,K,ync},0,x.dev);
      Y.view3().add_mprod(E.transp(),y);

      int offs=0;
      for(int b=0; b<nblocks; b++){
	for(int i=offs; i<offs+blocks[b]; i++)
	  lambda(X.view3().slice1(i),Y.view3().slice1(i),b);
	offs+=blocks[b];
      }

      if(inplace_add) const_cast<cnine::Rtensor3_view&>(x).add_mprod(E,X.view3());
    }


   public: // ---- I/O ----------------------------------------------------------------------------------------


    string classname() const{
      return "BatchedSubgraphLayer1b";
    }


  };




}

#endif 


