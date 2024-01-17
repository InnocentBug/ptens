/*
 * This file is part of ptens, a C++/CUDA library for permutation 
 * equivariant message passing. 
 *  
 * Copyright (c) 2024, Imre Risi Kondor
 *
 * This source code file is subject to the terms of the noncommercial 
 * license distributed with cnine in the file LICENSE.TXT. Commercial 
 * use is prohibited. All redistributed versions of this file (in 
 * original or modified form) must retain this copyright notice and 
 * must be accompanied by a verbatim copy of the license. 
 *
 */

#ifndef _ptens_Ptensors0bBatch
#define _ptens_Ptensors0bBatch

#include "diff_class.hpp"

#include "AtomsPackBatch.hpp"
#include "Ptensors0b.hpp"


namespace ptens{

  template<typename TYPE> class Ptensors1bBatch;
  template<typename TYPE> class Ptensors2bBatch;


  template<typename TYPE>
  class Ptensors0bBatch: public object_pack<Ptensors0b<TYPE> >, public cnine::diff_class<Ptensors0bBatch<TYPE> >{

    typedef object_pack<Ptennsors0b<TYPE> > BASE;

    using BASE::obj;
    using BASE::size;
    using BASE::operator[];
    using BASE::zip;
    using BASE::repr;
    using BASE::str;

    AtomsPackBatch atoms;


  public: // ----- Constructors ------------------------------------------------------------------------------


    //Ptensors0bBatch(){}

    Ptensors0bBatch(const AtomsPackBatch& _atoms):
      atoms(_atoms){}

    Ptensors0bBatch R(const AtomsPackBatch& a, const int _nc, const int _dev):
      Ptensors0bBatch(a){
      for(int i=0; i<atoms.size() i++)
	obj.push_back(Ptensors0b<TYPE>(atoms[i],_nc,_dev));
    }

    Ptensors0bBatch R(const AtomsPackBatch& a, const int _nc, const int fcode, const int _dev):
      Ptensors0bBatch(a){
      for(int i=0; i<atoms.size() i++)
	obj.push_back(Ptensors0b<TYPE>(atoms[i],_nc,fcode,_dev));
    }


  public: // ----- Spawning ----------------------------------------------------------------------------------


    Ptensors0bBatch copy() const{
      Ptensors0bBatch R(atoms);
      for(int i=0; i<size(); i++)
	R.obj.push_back((*this)[i].copy());
      return R;
    }

    Ptensors0b copy(const int _dev) const{
      Ptensors0bBatch R(atoms);
      for(int i=0; i<size(); i++)
	R.obj.push_back((*this)[i].copy(_dev));
      return R;
    }

    Ptensors0b zeros_like() const{
      Ptensors0bBatch R(atoms);
      for(int i=0; i<size(); i++)
	R.obj.push_back((*this)[i].zeros_like());
      return R;
    }

    Ptensors0b gaussian_like() const{
      Ptensors0bBatch R(atoms);
      for(int i=0; i<size(); i++)
	R.obj.push_back((*this)[i].gaussian_like());
      return R;
    }

    static Ptensors0b zeros_like(const Ptensors0b& x){
      Ptensors0bBatch R(atoms);
      for(int i=0; i<size(); i++)
	R.obj.push_back(Ptensors0b::zeros_like(x[i]));
      return R;
    }

    static Ptensors0b gaussian_like(const Ptensors0b& x){
      Ptensors0bBatch R(atoms);
      for(int i=0; i<size(); i++)
	R.obj.push_back(Ptensors0b::gaussian_like(x[i]));
      return R;
    }

    static Ptensors0b* new_zeros_like(const Ptensors0b& x){
      Ptensors0bBatch* R=new Ptensors0bBatch(atoms);
      for(int i=0; i<size(); i++)
	R->obj.push_back(Ptensors0b::zeros_like(x[i]));
      return R;
    }
    

  public: // ----- Access ------------------------------------------------------------------------------------


    static int getk(){
      return 0;
    }

    int get_dev() const{
      PTENS_ASSRT(size()>0);
      return (*this)[0].get_dev();
    }

    int get_nc() const{
      PTENS_ASSRT(size()>0);
      return (*this)[0].get_nc();
    }

    // save this or rebuild it each time?
    //AtomsPackBatch get_atoms(){
    //return atoms;
      //AtomsPackBatchObj* r=new AtomsPackBatchObj();
      //for(auto& p:obj)
      //r->obj.push_back(p.atoms.obj.atoms);
      //return r;
    //}


  public: // ---- Message passing ----------------------------------------------------------------------------


    template<typename SOURCE, typename = typename std::enable_if<std::is_base_of<Ptensorsb<float>, SOURCE>::value, SOURCE>::type>
    static Ptensors0bBatch<TYPE> linmaps(const SOURCE& x){
      Ptensors0bBatch<float> R(x.atoms,x.get_nc()*vector<int>({1,1,2})[x.getk()],x.get_dev());
      R.add_linmaps(x);
      return R;
    }

    template<typename SOURCE, typename = typename std::enable_if<std::is_base_of<Ptensorsb<float>, SOURCE>::value, SOURCE>::type>
    static Ptensors0b<TYPE> gather(const SOURCE& x, const AtomsPackBatch& a){
      Ptensors0bBatch<float> R(a,x.get_nc()*vector<int>({1,1,2})[x.getk()],x.get_dev());
      Ptensors0bBatch<TYPE> R(a);
      for(int i=0; i<x.size(); i++)
	R.obj.push_back(PtensorsOb<TYPE>::gather(x[i],a[i]));
      return R;
    }

    void add_linmaps(const Ptensors0bBatch<TYPE>& x){
      //add(x);
    }

    void add_linmaps(const Ptensors1bBatch<TYPE>& x){
      //add(x.reduce0());
    }

    void add_linmaps(const Ptensors2bBatch<TYPE>& x){
      //add(x.reduce0());
    }

    template<typename SOURCE>
    void add_gather(const SOURCE& x){
      (atoms.overlaps_mmap(x.atoms))(*this,x);
    }

    template<typename OUTPUT>
    void add_gather_back(const OUTPUT& x){
      //x.atoms.overlaps_mmap(atoms).inv()(*this,x);
    }

    
  public: // ---- I/O ----------------------------------------------------------------------------------------


    string classname() const{
      return "Ptensors0bBatch";
    }


  };

}

#endif 


      //Ptensors0bBatch<TYPE> R(x.get_atoms(),x.get_nc()*vector<int>({1,1,2})[x.getk()],x.get_dev());
      //for(int i=0; i<R.size(); i++)
      //r[i].add_linmaps(x[i]);
      //Ptensors0bBatch<TYPE> R(a,x.get_nc()*vector<int>({1,1,2})[x.getk()],x.get_dev());
      //for(int i=0; i<size(); i++)
      //r[i].add_gather(x[i]);
    // is this the good way to do it?
    //template<typename SOURCE>
    //MessageMapBatch overlaps_mmap(const SOURCE& x){
    //MessageMapBatch R;
    //for(int i=0; i<size(); i++){
    //R.push_back((*this)[i].atoms.overlaps_mmap(x[i].atoms));
    //}
    //return R;
    //}
