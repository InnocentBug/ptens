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
 */

#ifndef _ptens_AindexPack
#define _ptens_AindexPack

#include <map>

#include "hlists.hpp"
#include "Atoms.hpp"
#include "GatherMap.hpp"


namespace ptens{


  class AindexPack: public cnine::hlists<int>{
  public:

    typedef cnine::hlists<int> BASE;

    int _max_nix=0;
    int count1=0;
    int count2=0;

    std::shared_ptr<cnine::GatherMap> bmap;


  public: // ---- Constructors ------------------------------------------------------------------------------


    AindexPack(){}

    AindexPack(const vector<pair<int,vector<int> > >& x){
      for(auto& p:x)
	push_back(p.first,p.second);
    }


  public: // ---- Copying -----------------------------------------------------------------------------------


    AindexPack(const AindexPack& x):
      BASE(x){
      bmap=x.bmap;
      _max_nix=x._max_nix;
      count1=x.count1;
      count2=x.count2;
    }

    AindexPack(AindexPack&& x):
      BASE(std::move(x)){
      bmap=x.bmap; 
      _max_nix=x._max_nix;
      count1=x.count1;
      count2=x.count2;
    }

    AindexPack& operator=(const AindexPack& x)=delete;


  public: // ---- Access -------------------------------------------------------------------------------------


    int max_nix() const{
      return _max_nix;
    }

    int tix(const int i) const{
      assert(i<size());
      return head(i);
    }

    int tens(const int i) const{
      assert(i<size());
      return head(i);
    }

    vector<int> ix(const int i) const{
      return BASE::operator()(i); 
    }

    int ix(const int i, const int j) const{
      return BASE::operator()(i,j);
    }

    int nix(const int i) const{
      return BASE::size_of(i);
    }

    //const cnine::GatherMap& get_bmap() const{
    //assert(bmap);
    //return *bmap;
    //}

    /*
    int* get_barr(const int _dev=0) const{
      assert(bmap);
      bmap->to_device(_dev);
      if(_dev==0) return bmap->arr;
      return bmap->arrg;
    }
    */

    void push_back(const int tix, vector<int> indices){
      BASE::push_back(tix,indices);
       _max_nix=std::max(_max_nix,(int)indices.size());
    }

    
  public: // ---- Operations ---------------------------------------------------------------------------------

  public: // ---- I/O ----------------------------------------------------------------------------------------


    string repr() const{
      return "<AindexPack[N="+to_string(size())+"]>";
    }

    friend ostream& operator<<(ostream& stream, const AindexPack& v){
      stream<<v.str(); return stream;}

  };

}


#endif 
 
