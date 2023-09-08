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

#ifndef _ptens_Ptensors2
#define _ptens_Ptensors2

#include "Rtensor3_view.hpp"

//#include "Cgraph.hpp"
#include "RtensorPackB.hpp"
#include "AtomsPack.hpp"
#include "AindexPack.hpp"
#include "Ptensor2.hpp"
#include "diff_class.hpp"

#include "PtensLoggedTimer.hpp"


namespace ptens{


  #ifdef _WITH_CUDA
  extern void Ptensors2_reduce0_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce0n_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce0B_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce0_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce0n_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce0B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);

  extern void Ptensors2_reduce1_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce1n_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce1B_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce1_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce1n_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce1B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);

  extern void Ptensors2_reduce2_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce2B_cu(cnine::RtensorPackB& R,const cnine::RtensorPackB& x, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce2_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);
  extern void Ptensors2_reduce2B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, int offs, int n, const cudaStream_t& stream);

  extern void Ptensors2_broadcast0_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast0B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast0Bn_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast0_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast0B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast0Bn_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);

  extern void Ptensors2_broadcast1_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast1B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast1Bn_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast1_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast1B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast1Bn_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);

  extern void Ptensors2_broadcast2_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast2B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast2_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);
  extern void Ptensors2_broadcast2B_cu(cnine::RtensorPackB& R, const cnine::RtensorPackB& x, const AindexPack& list, const int offs, const cudaStream_t& stream);
  #endif


  class Ptensors2: public cnine::RtensorPackB, public cnine::diff_class<Ptensors2>{
  public:

    typedef cnine::Gdims Gdims;
    typedef cnine::IntTensor itensor;
    typedef cnine::IntTensor IntTensor;
    typedef cnine::RtensorA rtensor;
    typedef cnine::RtensorPackB RtensorPackB;
    //typedef cnine::RtensorPackB RtensorPack;
    typedef cnine::Rtensor1_view Rtensor1_view;
    typedef cnine::Rtensor2_view Rtensor2_view;
    typedef cnine::Rtensor3_view Rtensor3_view;

    AtomsPack atoms;
    rtensor norms;


    ~Ptensors2(){
#ifdef WITH_FAKE_GRAD
      if(grad) delete grad;
#endif 
    }


  public: // ----- Constructors ------------------------------------------------------------------------------


    Ptensors2(){}

    Ptensors2(const int _nc, const int _dev=0):
      RtensorPackB(3,_nc,_dev) /*, nc(_nc)*/{}

    Ptensors2(const AtomsPack& _atoms, const int _nc, const int _dev=0):
      RtensorPackB(3,_nc,_dev), /*nc(_nc),*/ atoms(_atoms){}

    Ptensors2(const AtomsPack& _atoms, const int _nc, const cnine::fill_zero& dummy, const int _dev=0):
      Ptensors2(zero(_atoms,_nc,_dev)){}

    Ptensors2(const cnine::Tensor<int>& M, const int _nc, const cnine::fill_zero& dummy, const int _dev=0):
      RtensorPackB(M.dims[0],{M.dims[1],M.dims[1],_nc},dummy,_dev), atoms(M){}

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    Ptensors2(const int _n, const int _k, const int _nc, const FILLTYPE& dummy, const int _dev=0):
      RtensorPackB(_n,{_k,_k,_nc},dummy,_dev), atoms(_n,_k)/*, nc(_nc)*/{}


  public: // ----- Named constructors ------------------------------------------------------------------------


    static Ptensors2 raw(const int _n, const int _k, const int _nc, const int _dev=0){
      return Ptensors2(_n,_k,_nc,cnine::fill_raw(),_dev);}

    static Ptensors2 zero(const int _n, const int _k, const int _nc, const int _dev=0){
      return Ptensors2(_n,_k,_nc,cnine::fill_zero(),_dev);}

    static Ptensors2 gaussian(const int _n, const int _k, const int _nc, const int _dev=0){
      return Ptensors2(_n,_k,_nc,cnine::fill_gaussian(),_dev);}

    static Ptensors2 gaussian(const int _n, const int _k, const int _nc, const float sigma, const int _dev){
      return Ptensors2(_n,_k,_nc,cnine::fill_gaussian(sigma),_dev);}

    static Ptensors2 randn(const int _n, const int _k, const int _nc, const int _dev=0){
      return Ptensors2(_n,_k,_nc,cnine::fill_gaussian(),_dev);}

    static Ptensors2 randn(const int _n, const int _k, const int _nc, const float sigma, const int _dev){
      return Ptensors2(_n,_k,_nc,cnine::fill_gaussian(sigma),_dev);}

    static Ptensors2 sequential(const int _n, const int _k, const int _nc, const int _dev=0){
      Ptensors2 R(_n,_k,_nc,cnine::fill_raw(),0);
      for(int i=0; i<_n; i++)
	R.view3_of(i).set(i); 
      return R.to_device(_dev);
    }


    static Ptensors2 raw(const AtomsPack& _atoms, const int _nc, const int _dev=0){
     Ptensors2 R(_atoms,_nc,_dev);
      R.reserve(_atoms.tsize2()*_nc);
      R.dir=IntTensor::raw({_atoms.size(),4});
      R.tail=0;
      for(int i=0; i<_atoms.size(); i++){
	R.dir.set_row(i,{R.tail,_atoms.size_of(i),_atoms.size_of(i),_nc});
	R.tail+=_atoms.size_of(i)*_atoms.size_of(i)*_nc;
      }
      return R;
    }

    static Ptensors2 zero(const AtomsPack& _atoms, const int _nc, const int _dev=0){
     Ptensors2 R(_atoms,_nc,_dev);
      R.reserve_zero(_atoms.tsize2()*_nc);
      R.dir=IntTensor::raw({_atoms.size(),4});
      R.tail=0;
      for(int i=0; i<_atoms.size(); i++){
	R.dir.set_row(i,{R.tail,_atoms.size_of(i),_atoms.size_of(i),_nc});
	R.tail+=_atoms.size_of(i)*_atoms.size_of(i)*_nc;
      }
      return R;
    }

    static Ptensors2 gaussian(const AtomsPack& _atoms, const int _nc, const int _dev=0){
      Ptensors2 R(_nc,0);
      for(int i=0; i<_atoms.size(); i++)
	R.push_back(Ptensor2::gaussian(_atoms(i),_nc));
      return R.to_device(_dev);
    }

    static Ptensors2 gaussian(const AtomsPack& _atoms, const int _nc, const float sigma, const int _dev){
      Ptensors2 R(_nc,0);
      for(int i=0; i<_atoms.size(); i++)
	R.push_back(Ptensor2::gaussian(_atoms(i),_nc,sigma,0));
      return R.to_device(_dev);
    }

    static Ptensors2 randn(const AtomsPack& _atoms, const int _nc, const int _dev=0){
      return Ptensors2::gaussian(_atoms,_nc,_dev);}

    static Ptensors2 randn(const AtomsPack& _atoms, const int _nc, const float sigma, const int _dev){
      return Ptensors2::gaussian(_atoms,_nc,sigma,_dev);}

    static Ptensors2 sequential(const AtomsPack& _atoms, const int _nc, const int _dev=0){
      Ptensors2 R(_nc,0);
      for(int i=0; i<_atoms.size(); i++)
	R.push_back(Ptensor2::sequential(_atoms(i),_nc));
      return R.to_device(_dev);
    }

    static Ptensors2 concat(const Ptensors2& x, const Ptensors2& y){
      Ptensors2 R=Ptensors2::zero(x.atoms,x.nc+y.nc,x.dev);
      R.add_to_channels(x,0);
      R.add_to_channels(y,x.nc);
      return R;
    }


  public: // ----- Copying -----------------------------------------------------------------------------------


    Ptensors2(const Ptensors2& x):
      RtensorPackB(x),
      cnine::diff_class<Ptensors2>(x),
      atoms(x.atoms) /*,nc(x.nc)*/{
      PTENS_COPY_WARNING();
    }
	
    Ptensors2(Ptensors2&& x):
      RtensorPackB(std::move(x)),
      cnine::diff_class<Ptensors2>(std::move(x)),
      atoms(std::move(x.atoms))/*,nc(x.nc)*/{
      PTENS_COPY_WARNING();
    }

    Ptensors2& operator=(const Ptensors2& x)=delete;


  public: // ---- Spawning -----------------------------------------------------------------------------------


    static Ptensors2 zeros_like(const Ptensors2& x){
      return Ptensors2(RtensorPackB::zeros_like(x),x.atoms);//,x.nc);
    }

    static Ptensors2* new_zeros_like(const Ptensors2& x){
      return new Ptensors2(RtensorPackB::zeros_like(x),x.atoms);//,x.nc);
    }

   static Ptensors2 gaussian_like(const Ptensors2& x){
     return Ptensors2(RtensorPackB::gaussian_like(x),x.atoms);//,x.nc);
    }

    static Ptensors2 randn_like(const Ptensors2& x){
      return Ptensors2(RtensorPackB::gaussian_like(x),x.atoms);//,x.nc);
    }

    static Ptensors2 sequential_like(const Ptensors2& x){
      return Ptensors2(RtensorPackB::sequential_like(x),x.atoms);//,x.nc);
    }

    
  public: // ----- Conversions -------------------------------------------------------------------------------


    //Ptensors2(RtensorPack&& x, const AtomsPack& _atoms, const int _nc):
    //RtensorPack(std::move(x)), atoms(_atoms), nc(_nc){}

    Ptensors2(RtensorPackB&& x, const AtomsPack& _atoms)://, const int _nc):
      RtensorPackB(std::move(x)), atoms(_atoms)/*, nc(_nc)*/{}

    Ptensors2(const rtensor& A, const AtomsPack& _atoms):
      RtensorPackB(A,_atoms.dims2(A.dim(1))), atoms(_atoms){
      nc=A.dim(1);
    }

    //Ptensors2(const rtensor& A):
    //CNINE_UNIMPL();
    //RtensorPackB(A), atoms(A.dim(0)){
    //}

    #ifdef _WITH_ATEN
    Ptensors2(const at::Tensor& T, const AtomsPack& _atoms):
      Ptensors2(rtensor::regular(T),_atoms){}
    #endif 

    //rtensor view_as_matrix() const{
    //return rtensor::view_of_blob({tail/nc,nc},get_arr(),dev);
    //}


  public: // ---- Transport ----------------------------------------------------------------------------------


    Ptensors2(const Ptensors2& x, const int _dev):
      RtensorPackB(x,_dev),
      atoms(x.atoms)/*,nc(x.nc)*/{}

    Ptensors2& to_device(const int _dev){
      RtensorPackB::to_device(_dev);
      return *this;
    }


  public: // ----- Access ------------------------------------------------------------------------------------


    //int get_nc() const{
    //return nc;
    //}

    int getn() const{
      return size();
    }

    AtomsPack view_of_atoms(){
      return atoms.view();
    }


    int k_of(const int i) const{
      return dim_of(i,0);
    }

    Atoms atoms_of(const int i) const{
      return Atoms(atoms(i));
    }

    rtensor tensor_of(const int i) const{
      return RtensorPackB::operator()(i);
    }

    Rtensor3_view view_of(const int i) const{
      return RtensorPackB::view3_of(i);
    }

    Rtensor2_view fused_view_of(const int i) const{
      return RtensorPackB::view3_of(i).fuse01();
    }

    Rtensor3_view view_of(const int i, const int offs, const int n) const{
      return RtensorPackB::view3_of(i).block(0,0,offs,-1,-1,n);
    }

    Ptensor2_xview view_of(const int i, const vector<int>& ix) const{
      vector<int> v=headers(i);
      PTENS_ASSRT(v.size()==4);
      if(dev==1) return Ptensor2_xview(arrg+v[0],v[3],v[2]*v[3],v[3],1,ix,1);
      return Ptensor2_xview(arr+v[0],v[3],v[2]*v[3],v[3],1,ix,0);
    }

    Ptensor2_xview view_of(const int i, const vector<int>& ix, const int offs, const int n) const{
      vector<int> v=headers(i);
      PTENS_ASSRT(v.size()==4);
      if(dev==1) return Ptensor2_xview(arrg+v[0]+offs,n,v[2]*v[3],v[3],1,ix,1);
      return Ptensor2_xview(arr+v[0]+offs,n,v[2]*v[3],v[3],1,ix,0);
    }

    Ptensor2 operator()(const int i) const{
      return Ptensor2(tensor_of(i),atoms_of(i));
    }

    int push_back(const Ptensor2& x){
      if(size()==0) nc=x.get_nc();
      else PTENS_ASSRT(nc==x.get_nc());
      RtensorPack::push_back(x);
      atoms.push_back(x.atoms);
      return size()-1;
    }

    template<typename OBJ1, typename OBJ2, typename FN>
    void for_each_view(const OBJ1& x, const OBJ2& y, FN lambda){
      int N=size();
      PTENS_ASSRT(x.size()==N);
      PTENS_ASSRT(y.size()==N);
      for(int i=0; i<N; i++)
	lambda(view_of(i),x.view_of(i),y.view_of(i));
    }


  public: // ---- Cumulative operations ----------------------------------------------------------------------


    void add_to_channels(const Ptensors2& x, const int offs){
      PTENS_CPUONLY();
      int N=size();
      PTENS_ASSRT(x.size()==N);
      for(int i=0; i<N; i++)
	view_of(i,offs,x.nc)+=x.view_of(i);
    }

    void add_channels(const Ptensors2& x, const int offs){
      PTENS_CPUONLY();
      int N=size();
      PTENS_ASSRT(x.size()==N);
      for(int i=0; i<N; i++)
	view_of(i)+=x.view_of(i,offs,nc);
    }


  public: // ---- Reductions ---------------------------------------------------------------------------------


    RtensorPackB reduce0() const{
      TimedFn T("Ptensors2","reduce0",*this);
      RtensorPackB R(size(),Gdims(2*nc),cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i).sum01_into(R.view1_of(i).block(0,nc));
	  view_of(i).diag01().sum0_into(R.view1_of(i).block(nc,nc));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce0_cu(R,*this,0,nc,stream)));
      return R;
    }

    RtensorPackB reduce0_n() const{
      TimedFn T("Ptensors2","reduce0_n",*this);
      RtensorPackB R(size(),Gdims(2*nc),cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i).avg01_into(R.view1_of(i).block(0,nc));
	  view_of(i).diag01().avg0_into(R.view1_of(i).block(nc,nc));
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_reduce0n_cu(R,*this,0,nc,stream)));
      return R;
    }

    RtensorPackB reduce0(const int offs, const int n) const{
      TimedFn T("Ptensors2","reduce0",*this);
      RtensorPackB R(size(),Gdims(n),cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i,offs,n).sum01_into(R.view1_of(i));
	  view_of(i,offs+n,n).diag01().sum0_into(R.view1_of(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce0B_cu(R,*this,offs,n,stream)));
      return R;
    }

    RtensorPackB reduce0_n(const AindexPack& list) const{
      TimedFn T("Ptensors2","reduce0_n",*this,list,(list.count2+list.count1)*nc);
      int N=list.size();
      RtensorPackB R(N,Gdims(2*nc),cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i)).avg01_into(R.view1_of(i).block(0,nc));
	  view_of(list.tens(i),list.ix(i)).diag01().avg0_into(R.view1_of(i).block(nc,nc));
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_reduce0n_cu(R,*this,list,0,nc,stream)));
      return R;
    }


    RtensorPackB reduce1() const{
      TimedFn T("Ptensors2","reduce1",*this);
      cnine::array_pool<int> dims;
      for(int i=0; i<size(); i++)
	dims.push_back(vector<int>({k_of(i),3*nc}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i).sum0_into(R.view2_of(i).block(0,0,-1,nc));
	  view_of(i).sum1_into(R.view2_of(i).block(0,nc,-1,nc));
	  R.view2_of(i).block(0,2*nc,-1,nc)+=view_of(i).diag01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce1_cu(R,*this,0,nc,stream)));
      return R;
    }

    RtensorPackB reduce1_n() const{
      TimedFn T("Ptensors2","reduce1_n",*this);
      cnine::array_pool<int> dims;
      for(int i=0; i<size(); i++)
	dims.push_back(vector<int>({k_of(i),3*nc}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i).avg0_into(R.view2_of(i).block(0,0,-1,nc));
	  view_of(i).avg1_into(R.view2_of(i).block(0,nc,-1,nc));
	  R.view2_of(i).block(0,2*nc,-1,nc)+=view_of(i).diag01();
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_reduce1n_cu(R,*this,0,nc,stream)));
      return R;
    }

    RtensorPackB reduce1(const int offs, const int n) const{
      TimedFn T("Ptensors2","reduce1",*this);
      cnine::array_pool<int> dims;
      for(int i=0; i<size(); i++)
	dims.push_back(vector<int>({k_of(i),n}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i,offs,n).sum0_into(R.view2_of(i));
	  view_of(i,offs+n,n).sum1_into(R.view2_of(i));
	  R.view2_of(i)+=view_of(i,offs+2*n,n).diag01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce1B_cu(R,*this,offs,n,stream)));
      return R;
    }

    RtensorPackB reduce2() const{
      TimedFn T("Ptensors2","reduce2",*this);
      return *this;
    }

    RtensorPackB reduce2(const int offs, const int n) const{ // flipping 
      TimedFn T("Ptensors2","reduce2",*this);
      cnine::array_pool<int> dims;
      for(int i=0; i<size(); i++)
	dims.push_back(vector<int>({k_of(i),k_of(i),n}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  R.view3_of(i)+=view_of(i,offs,n);
	  R.view3_of(i)+=view_of(i,offs+n,n).transp01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce2B_cu(R,*this,offs,n,stream)));
      return R;
    }


  public: // ---- Indexed reductions ---------------------------------------------------------------------------------


    RtensorPackB reduce0(const AindexPack& list) const{
      TimedFn T("Ptensors2","reduce0",*this,list,(list.count2+list.count1)*nc);
      int N=list.size();
      RtensorPackB R(N,Gdims(2*nc),cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i)).sum01_into(R.view1_of(i).block(0,nc));
	  view_of(list.tens(i),list.ix(i)).diag01().sum0_into(R.view1_of(i).block(nc,nc));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce0_cu(R,*this,list,0,nc,stream)));
      return R;
    }

    void reduce0_back(const RtensorPackB& x, const AindexPack& list){
      TimedFn T("Ptensors2","reduce0_back",*this,x,list,(list.count1+list.count2)*x.nc);
      int N=list.size();
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i))+=repeat0(repeat0(x.view1_of(i).block(0,nc),list.nix(i)),list.nix(i));
	  view_of(list.tens(i),list.ix(i)).diag01()+=repeat0(x.view1_of(i).block(nc,nc),list.nix(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast0B_cu(*this,x,list,0,stream)));
    }

    RtensorPackB reduce1(const AindexPack& list) const{
      TimedFn T("Ptensors2","reduce1",*this,list,(list.count1+2*list.count2)*nc);
      int N=list.size();
      cnine::array_pool<int> dims;
      for(int i=0; i<N; i++)
	dims.push_back(vector<int>({list.nix(i),3*nc}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i)).sum0_into(R.view2_of(i).block(0,0,-1,nc));
	  view_of(list.tens(i),list.ix(i)).sum1_into(R.view2_of(i).block(0,nc,-1,nc));
	  R.view2_of(i).block(0,2*nc,-1,nc)+=view_of(list.tens(i),list.ix(i)).diag01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce1_cu(R,*this,list,0,nc,stream)));
      return R;
    }

    void reduce1_back(const RtensorPackB& x, const AindexPack& list){
      TimedFn T("Ptensors2","reduce1_back",*this,x,list,(list.count1+2*list.count2)*x.nc);
      int N=list.size();
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i))+=repeat0(x.view2_of(i).block(0,0,-1,nc),list.nix(i));
	  view_of(list.tens(i),list.ix(i))+=repeat1(x.view2_of(i).block(0,nc,-1,nc),list.nix(i));
	  view_of(list.tens(i),list.ix(i)).diag01()+=x.view2_of(i).block(0,2*nc,-1,nc);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast1B_cu(*this,x,list,0,stream)));
    }

    RtensorPackB reduce2(const AindexPack& list) const{ // no flipping 
      TimedFn T("Ptensors2","reduce2",*this,list,(list.count2)*nc);
      int N=list.size();
      cnine::array_pool<int> dims;
      for(int i=0; i<N; i++)
	dims.push_back(vector<int>({list.nix(i),list.nix(i),nc}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  R.view3_of(i)+=view_of(list.tens(i),list.ix(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce2_cu(R,*this,list,0,nc,stream)));
      return R;
    }

    void reduce2_back(const RtensorPackB& x, const AindexPack& list){ // no flipping 
      TimedFn T("Ptensors2","reduce2_back",*this,x,list,(list.count2)*x.nc);
      int N=list.size();
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i))+=x.view3_of(i);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast2B_cu(*this,x,list,0,stream)));
    }




    RtensorPackB reduce1_n(const AindexPack& list) const{
      TimedFn T("Ptensors2","reduce1_n",*this,list,(list.count1+2*list.count2)*nc);
      int N=list.size();
      cnine::array_pool<int> dims;
      for(int i=0; i<N; i++)
	dims.push_back(vector<int>({list.nix(i),3*nc}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i)).avg0_into(R.view2_of(i).block(0,0,-1,nc));
	  view_of(list.tens(i),list.ix(i)).avg1_into(R.view2_of(i).block(0,nc,-1,nc));
	  R.view2_of(i).block(0,2*nc,-1,nc)+=view_of(list.tens(i),list.ix(i)).diag01();
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_reduce1n_cu(R,*this,list,0,nc,stream)));
      return R;
    }


    // deprecated: now called broadcast0_back
    RtensorPackB reduce0(const AindexPack& list, const int offs, const int n) const{
      TimedFn T("Ptensors2","reduce0",*this,list,(list.count2+list.count1)*n);
      int N=list.size();
      RtensorPackB R(N,Gdims(n),cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i),offs,n).sum01_into(R.view1_of(i));
	  view_of(list.tens(i),list.ix(i),offs+n,n).diag01().sum0_into(R.view1_of(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce0B_cu(R,*this,list,offs,n,stream)));
      return R;
    }

    // deprecated: now called broadcast1_back
    RtensorPackB reduce1(const AindexPack& list, const int offs, const int n) const{
      TimedFn T("Ptensors2","reduce1",*this,list,(list.count1+2*list.count2)*n);
      int N=list.size();
      cnine::array_pool<int> dims;
      for(int i=0; i<N; i++)
	dims.push_back(vector<int>({list.nix(i),n}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i),offs,n).sum0_into(R.view2_of(i));
	  view_of(list.tens(i),list.ix(i),offs+n,n).sum1_into(R.view2_of(i));
	  R.view2_of(i)+=view_of(list.tens(i),list.ix(i),offs+2*n,n).diag01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce1B_cu(R,*this,list,offs,n,stream)));
      return R;
    }

    // deprecated now called broadcast2_back
    RtensorPackB reduce2(const AindexPack& list, const int offs, const int n) const{
      TimedFn T("Ptensors2","reduce2",*this,list,(2*list.count2)*n);
      int N=list.size();
      cnine::array_pool<int> dims;
      for(int i=0; i<N; i++)
	dims.push_back(vector<int>({list.nix(i),list.nix(i),n}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  R.view3_of(i)+=view_of(list.tens(i),list.ix(i),offs,n);
	  R.view3_of(i)+=view_of(list.tens(i),list.ix(i),offs+n,n).transp();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce2B_cu(R,*this,list,offs,n,stream)));
      return R;
    }


  public: // ---- Broadcasting -------------------------------------------------------------------------------


    void broadcast0(const RtensorPackB& x){
      TimedFn T("Ptensors2","brcast0",*this,x);
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i).add(repeat0(repeat0(x.view1_of(i).block(0,nc),k_of(i)),k_of(i)));
	  view_of(i).diag01().add(repeat0(x.view1_of(i).block(nc,nc),k_of(i)));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast0B_cu(*this,x,0,stream)));
    }

    void broadcast0_n(const RtensorPackB& x){
      TimedFn T("Ptensors2","brcast0_n",*this,x);
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i).add(repeat0(repeat0(x.view1_of(i).block(0,nc),k_of(i)),k_of(i)),1.0/((float)k_of(i)*(float)(k_of(i))));
	  view_of(i).diag01().add(repeat0(x.view1_of(i).block(nc,nc),k_of(i)),1.0/((float)k_of(i)));
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast0Bn_cu(*this,x,0,stream)));
    }

    void broadcast0(const RtensorPackB& x, const int offs){
      TimedFn T("Ptensors2","brcast0",*this,x);
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i,offs,n)+=repeat0(repeat0(x.view1_of(i),k_of(i)),k_of(i));
	  view_of(i,offs+n,n).diag01()+=repeat0(x.view1_of(i),k_of(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast0_cu(*this,x,offs,stream)));
    }

    void broadcast1(const RtensorPackB& x){
      TimedFn T("Ptensors2","brcast1",*this,x);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i)+=repeat0(x.view2_of(i).block(0,0,-1,nc),k_of(i));
	  view_of(i)+=repeat1(x.view2_of(i).block(0,nc,-1,nc),k_of(i));
	  view_of(i).diag01()+=x.view2_of(i).block(0,2*nc,-1,nc);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast1B_cu(*this,x,0,stream)));
    }

    void broadcast1_n(const RtensorPackB& x){
      TimedFn T("Ptensors2","brcast1_n",*this,x);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i).add(repeat0(x.view2_of(i).block(0,0,-1,nc),k_of(i)),1.0/((float)k_of(i)));
	  view_of(i).add(repeat1(x.view2_of(i).block(0,nc,-1,nc),k_of(i)),1.0/((float)k_of(i)));
	  view_of(i).diag01()+=x.view2_of(i).block(0,2*nc,-1,nc);
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast1Bn_cu(*this,x,0,stream)));
    }

    void broadcast1(const RtensorPackB& x, const int offs){
      TimedFn T("Ptensors2","brcast1",*this,x);
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i,offs,n)+=repeat0(x.view2_of(i),k_of(i));
	  view_of(i,offs+n,n)+=repeat1(x.view2_of(i),k_of(i));
	  view_of(i,offs+2*n,n).diag01()+=x.view2_of(i);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast1_cu(*this,x,offs,stream)));
    }

    void broadcast2(const RtensorPackB& x){ // no flipping
      TimedFn T("Ptensors2","brcast2",*this,x);
      //const int n=x.dim_of(0,2);
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i)+=x.view3_of(i);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast2B_cu(*this,x,0,stream)));
    }

    void broadcast2(const RtensorPackB& x, const int offs){
      TimedFn T("Ptensors2","brcast2",*this,x);
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<size(); i++){
	  view_of(i,offs,n)+=x.view3_of(i);
	  view_of(i,offs+n,n)+=x.view3_of(i).transp01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast2_cu(*this,x,offs,stream)));
    }


  public: // ---- Idexed broadcasting -------------------------------------------------------------------------------


    void broadcast0(const RtensorPackB& x, const AindexPack& list, const int offs){
      TimedFn T("Ptensors2","brcast0",*this,x,list,(list.count1+list.count2)*x.nc);
      int N=list.size();
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue; // probably redundant
	  view_of(list.tens(i),list.ix(i),offs,n)+=repeat0(repeat0(x.view1_of(i),list.nix(i)),list.nix(i));
	  view_of(list.tens(i),list.ix(i),offs+n,n).diag01()+=repeat0(x.view1_of(i),list.nix(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast0_cu(*this,x,list,offs,stream)));
    }

    RtensorPackB broadcast0_back(const AindexPack& list, const int offs, const int n) const{
      TimedFn T("Ptensors2","bcast0_back",*this,list,(list.count2+list.count1)*n);
      int N=list.size();
      RtensorPackB R(N,Gdims(n),cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i),offs,n).sum01_into(R.view1_of(i));
	  view_of(list.tens(i),list.ix(i),offs+n,n).diag01().sum0_into(R.view1_of(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce0B_cu(R,*this,list,offs,n,stream)));
      return R;
    }

    void broadcast1(const RtensorPackB& x, const AindexPack& list, const int offs){
      TimedFn T("Ptensors2","brcast1",*this,x,list,(list.count1+2*list.count2)*x.nc);
      int N=list.size();
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i),offs,n)+=repeat0(x.view2_of(i),list.nix(i));
	  view_of(list.tens(i),list.ix(i),offs+n,n)+=repeat1(x.view2_of(i),list.nix(i));
	  view_of(list.tens(i),list.ix(i),offs+2*n,n).diag01()+=x.view2_of(i);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast1_cu(*this,x,list,offs,stream)));
    }

    RtensorPackB broadcast1_back(const AindexPack& list, const int offs, const int n) const{
      TimedFn T("Ptensors2","brcast1_back",*this,list,(list.count1+2*list.count2)*n);
      int N=list.size();
      cnine::array_pool<int> dims;
      for(int i=0; i<N; i++)
	dims.push_back(vector<int>({list.nix(i),n}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  view_of(list.tens(i),list.ix(i),offs,n).sum0_into(R.view2_of(i));
	  view_of(list.tens(i),list.ix(i),offs+n,n).sum1_into(R.view2_of(i));
	  R.view2_of(i)+=view_of(list.tens(i),list.ix(i),offs+2*n,n).diag01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce1B_cu(R,*this,list,offs,n,stream)));
      return R;
    }

    void broadcast2(const RtensorPackB& x, const AindexPack& list, const int offs){
      TimedFn T("Ptensors2","brcast2",*this,x,list,(2*list.count2)*x.nc);
      int N=list.size();
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i),offs,n)+=x.view3_of(i);
	  view_of(list.tens(i),list.ix(i),offs+n,n)+=x.view3_of(i).transp01();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast2_cu(*this,x,list,offs,stream)));
    }

    RtensorPackB broadcast2_back(const AindexPack& list, const int offs, const int n) const{
      TimedFn T("Ptensors2","brcast2_back",*this,list,(2*list.count2)*n);
      int N=list.size();
      cnine::array_pool<int> dims;
      for(int i=0; i<N; i++)
	dims.push_back(vector<int>({list.nix(i),list.nix(i),n}));
      RtensorPackB R(dims,cnine::fill_zero(),dev);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(list.nix(i)==0) continue;
	  R.view3_of(i)+=view_of(list.tens(i),list.ix(i),offs,n);
	  R.view3_of(i)+=view_of(list.tens(i),list.ix(i),offs+n,n).transp();
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_reduce2B_cu(R,*this,list,offs,n,stream)));
      return R;
    }


    // ---- normalized 

    void broadcast0_n(const RtensorPackB& x, const AindexPack& list){
      TimedFn T("Ptensors2","brcast0_n",*this,x,list,(list.count1+list.count2)*x.nc);
      int N=list.size();
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i)).
	    add(repeat0(repeat0(x.view1_of(i).block(0,nc),list.nix(i)),list.nix(i)),1.0/((float)list.nix(i)*list.nix(i)));
	  view_of(list.tens(i),list.ix(i)).diag01().
	    add(repeat0(x.view1_of(i).block(nc,nc),list.nix(i)),1.0/((float)list.nix(i)));
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast0Bn_cu(*this,x,list,0,stream)));
    }

    void broadcast1_n(const RtensorPackB& x, const AindexPack& list){
      TimedFn T("Ptensors2","brcast1_n",*this,x,list,(list.count1+2*list.count2)*x.nc);
      int N=list.size();
      //const int n=x.dim_of(0,1);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i))
	    .add(repeat0(x.view2_of(i).block(0,0,-1,nc),list.nix(i)),1.0/((float)list.nix(i)));
	  view_of(list.tens(i),list.ix(i))
	    .add(repeat1(x.view2_of(i).block(0,nc,-1,nc),list.nix(i)),1.0/((float)list.nix(i)));
	  view_of(list.tens(i),list.ix(i)).diag01()+=x.view2_of(i).block(0,2*nc,-1,nc);
	}
      }
      //PTENS_CPUONLY();
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast1Bn_cu(*this,x,list,0,stream)));
    }


    // ---- deprecated

    // deprecated: now called reduce0_back
    void broadcast0(const RtensorPackB& x, const AindexPack& list){
      TimedFn T("Ptensors2","brcast0",*this,x,list,(list.count1+list.count2)*x.nc);
      int N=list.size();
      const int n=x.nc;
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i))+=repeat0(repeat0(x.view1_of(i).block(0,nc),list.nix(i)),list.nix(i));
	  view_of(list.tens(i),list.ix(i)).diag01()+=repeat0(x.view1_of(i).block(nc,nc),list.nix(i));
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast0B_cu(*this,x,list,0,stream)));
    }

    // deprecated: now called reduce1_back
    void broadcast1(const RtensorPackB& x, const AindexPack& list){
      TimedFn T("Ptensors2","brcast1",*this,x,list,(list.count1+2*list.count2)*x.nc);
      int N=list.size();
      //const int n=x.dim_of(0,1);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i))+=repeat0(x.view2_of(i).block(0,0,-1,nc),list.nix(i));
	  view_of(list.tens(i),list.ix(i))+=repeat1(x.view2_of(i).block(0,nc,-1,nc),list.nix(i));
	  view_of(list.tens(i),list.ix(i)).diag01()+=x.view2_of(i).block(0,2*nc,-1,nc);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast1B_cu(*this,x,list,0,stream)));
    }

    // deprecated: now called reduce2_back
    void broadcast2(const RtensorPackB& x, const AindexPack& list){
      TimedFn T("Ptensors2","brcast2",*this,x,list,(list.count2)*x.nc);
      int N=list.size();
      //const int n=x.dim_of(0,2);
      if(dev==0){
	for(int i=0; i<N; i++){
	  if(x.dim_of(i,0)==0) continue;
	  view_of(list.tens(i),list.ix(i))+=x.view3_of(i);
	}
      }
      GPUCODE(CUDA_STREAM(Ptensors2_broadcast2B_cu(*this,x,list,0,stream)));
    }


  public: // ---- I/O ----------------------------------------------------------------------------------------


    string classname() const{
      return "Ptensors2";
    }

    string repr() const{
      return "<Ptensors2[N="+to_string(size())+"]>";
    }

    string str(const string indent="") const{
      if(dev>0){
	Ptensors2 y(*this,0);
	return y.str();
      }
      ostringstream oss;
      for(int i=0; i<size(); i++){
	oss<<indent<<(*this)(i)<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const Ptensors2& x){
      stream<<x.str(); return stream;}

  };

}


#endif 
 
