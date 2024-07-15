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

#ifndef _ptens_BatchedPtensors1
#define _ptens_BatchedPtensors1

#include "diff_class.hpp"
#include "object_pack.hpp"

#include "BatchedAtomsPack.hpp"
#include "Ptensors1.hpp"
#include "BatchedPtensors.hpp"
#include "MultiLoop.hpp"


namespace ptens{

  //template<typename TYPE> class Ptensors1Batch;
  //template<typename TYPE> class Ptensors2Batch;


  template<typename TYPE>
  class BatchedPtensors1: public BatchedPtensors<TYPE>,
			   public cnine::diff_class<BatchedPtensors1<TYPE> >{
  public:

    typedef BatchedPtensors<TYPE> BASE;
    typedef cnine::Ltensor<TYPE> TENSOR;
    //typedef BatchedAtomsPackN<AtomsPack1obj<int> > BatchedAtomsPack1;
    
    using cnine::diff_class<BatchedPtensors1<TYPE> >::grad;
    using BASE::get_dev;

    using TENSOR::dim;
    using TENSOR::get_arr;

    BatchedAtomsPack atoms;

    //cnine::GatherMapProgramPack forward_program;
    //cnine::GatherMapProgramPack backward_program;


    ~BatchedPtensors1(){
#ifdef WITH_FAKE_GRAD
      if(grad) delete grad;
#endif 
    }


  public: // ----- Constructors ------------------------------------------------------------------------------


    //BatchedPtensors1(){}

    BatchedPtensors1(const BatchedAtomsPack& _atoms, const TENSOR& M):
      BASE(M), atoms(_atoms){
    }

    BatchedPtensors1(const TENSOR& M, const BatchedAtomsPack& _atoms):
      BASE(M), atoms(_atoms){}

    //BatchedPtensors1(const BatchedAtomsPack& _atoms, const cnine::TensorView<TYPE>& M):
    //BASE(M.copy()), atoms(_atoms){}

    //BatchedPtensors1(const BatchedAtomsPack& _atoms, const cnine::Tensor<float>& M):
    //BASE(cnine::Ltensor<float>(M).copy(ptens_session->managed_gmem)), atoms(_atoms){}

    //BatchedPtensors1(const BatchedAtomsPack& _atoms, const TENSOR& M):
    //BASE(M.copy(ptens_session->managed_gmem)), atoms(_atoms){}

    BatchedPtensors1(const BatchedAtomsPack& _atoms, const int _nc, const int fcode, const int _dev):
      BASE({_atoms.nrows1(),_nc},fcode,_dev), atoms(_atoms){}


    BatchedPtensors1(const BatchedAtomsPack& _atoms, const int _nc, const int _dev):
      BatchedPtensors1(_atoms,_nc,0,_dev){}

    //BatchedPtensors1(const BatchedAtomsPack& _atoms, const int _nc, const int fcode, const int _dev):
    //BatchedPtensors1(BatchedAtomsPack1(_atoms),_nc,fcode,_dev){}


    BatchedPtensors1(TYPE* _arr, const BatchedAtomsPack& _atoms, const int _nc, const int _dev):
      BASE(_arr,{_atoms.nrows1(),_nc},_dev), atoms(_atoms){}


    // TODO 
    BatchedPtensors1(const initializer_list<Ptensors1<TYPE> >& list):
      BASE(cnine::Ltensor<TYPE>::stack(0,list)){
      vector<shared_ptr<AtomsPackObj> > x;
      for(auto& p:list) x.push_back(p.atoms.obj);
      atoms=BatchedAtomsPack(x);
    }
	
    static BatchedPtensors1 cat(const vector<BatchedPtensors1>& list){
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      PTENS_ASSRT(list.size()>0);
      vector<BatchedAtomsPack> v;
      for(auto& p:list)
	v.push_back(p.atoms);
      BatchedPtensors1 R(BatchedAtomsPack::cat(v),list[0].get_nc(),list[0].get_dev());

      int N=list[0].size();
      for(int i=0; i<N; i++){
	vector<cnine::Ltensor<TYPE> > w;
	for(int j=0; j<list.size(); j++)
	  w.push_back(list[j].view_of(i));
	R.view_of(i).cnine:: template Ltensor<TYPE>::operator=(cnine::Ltensor<TYPE>::stack(0,w));
      }
      return R;
    }


  public: // ---- Named parameter constructors ---------------------------------------------------------------


    struct vparams{
      int nc=1;
      int fcode=0;
      int dev=0;
    };      

    template<typename... Args>
    BatchedPtensors1(const BatchedAtomsPack& _atoms, const Args&... args):
      atoms(_atoms){
      vparams v;
      unroller(v,args...);
      BASE::reset(BASE({atoms.nrows1(),v.nc},v.fcode,v.dev));
    }

    template<typename... Args>
    void unroller(vparams& v, const cnine::ChannelsArgument& x, const Args&... args){
      v.nc=x.get(); unroller(v, args...);}

    template<typename... Args>
    void unroller(vparams& v, const cnine::FillArgument& x, const Args&... args){
      v.fcode=x.get(); unroller(v, args...);}

    template<typename... Args>
    void unroller(vparams& v, const cnine::DeviceArgument& x, const Args&... args){
      v.dev=x.get(); unroller(v, args...);}

    void unroller(vparams& v){}


  public: // ----- Spawning ----------------------------------------------------------------------------------


    BatchedPtensors1 copy() const{
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(TENSOR::copy(),atoms);
    }

    BatchedPtensors1 copy(const int _dev) const{
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(TENSOR::copy(_dev),atoms);
    }

    BatchedPtensors1 zeros_like() const{
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(TENSOR::zeros_like(),atoms);
    }

    BatchedPtensors1 zeros_like(const int nc) const{
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(TENSOR({dim(0),nc},0,get_dev()),atoms);
    }

    BatchedPtensors1 gaussian_like() const{
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(TENSOR::gaussian_like(),atoms);
    }

    static BatchedPtensors1 zeros_like(const BatchedPtensors1& x){
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(x.BASE::zeros_like(),x.atoms);
    }

    static BatchedPtensors1 zeros_like(const BatchedPtensors1& x, const int nc){
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(TENSOR({x.dim(0),nc},0,get_dev()),x.atoms);
    }

    static BatchedPtensors1 gaussian_like(const BatchedPtensors1& x){
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return BatchedPtensors1(x.TENSOR::gaussian_like(),x.atoms);
    }

    static BatchedPtensors1* new_zeros_like(const BatchedPtensors1& x){
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return new BatchedPtensors1(x.BASE::zeros_like(),x.atoms);
    }
    
    static BatchedPtensors1* new_like(TYPE* _arr, const BatchedPtensors1& x){
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      return new BatchedPtensors1(x.TENSOR::like(_arr),x.atoms);
    }
    

  public: // ----- Conversions -------------------------------------------------------------------------------


    //BatchedPtensors1(const TENSOR& x, const BatchedAtomsPack1& _atoms):
    //BASE(x),
    //atoms(_atoms){}


  public: // ----- Access ------------------------------------------------------------------------------------


    static int getk(){
      return 1;
    }

    int size() const{
      return atoms.size();
    }

    int get_nc() const{
      return TENSOR::dim(1);
    }

    //BatchedAtomsPack get_atoms() const{
    //return atoms.obj->get_atoms();
    //}

    BatchedPtensors1& get_grad(){ // why do we need these?
      return cnine::diff_class<BatchedPtensors1<TYPE> >::get_grad();
    }

    const BatchedPtensors1& get_grad() const{
      return cnine::diff_class<BatchedPtensors1<TYPE> >::get_grad();
    }

    BatchedPtensors1& get_grad(TYPE* _arr){
      if(!grad) grad=new_like(_arr,*this);
      return *grad;
    }

    Ptensors1<TYPE> view_of(const int i) const{
      return Ptensors1<TYPE>(atoms[i],TENSOR::rows(atoms.offset1(i),atoms.nrows1(i)));
    }

    //Ptensors1<TYPE> operator[](const int i){
    //return Ptensors1<TYPE>(atoms.obj->obj[i],TENSOR::rows(atoms.offset(i)),atoms.nrows(i));
    //}

    Ptensors1<TYPE> operator[](const int i) const{
      return Ptensors1<TYPE>(atoms[i],TENSOR::rows(atoms.offset1(i),atoms.nrows1(i)));
    }

    const cnine::Rtensor3_view view3(const int K) const{
      int nc=get_nc();
      return split0(TENSOR::view2(),dim(0)/K,K);
      //return cnine::Rtensor3_view(const_cast<float*>(get_arr()),dim(0)/K,K,nc,K*nc,nc,1,get_dev());
    }

    //cnine::Rtensor3_view view3(const int K){
    //int nc=get_nc();
    //return cnine::Rtensor3_view(get_arr(),dim(0)/K,K,nc,K*nc,nc,1,get_dev());
    //}

    const cnine::Rtensor3_view view3(const int K, const int offs, const int nc) const{
      int _nc=get_nc();
      return split0(TENSOR::view2().cols(offs,nc),dim(0)/K,K);
      //return cnine::Rtensor3_view(const_cast<float*>(get_arr())+offs,dim(0)/K,K,nc,K*_nc,_nc,1,get_dev());
    }

    /*
    cnine::Rtensor3_view view3(const int K, const int offs, const int nc){
      int _nc=get_nc();
      return cnine::Rtensor3_view(get_arr()+offs,dim(0)/K,K,nc,K*_nc,_nc,1,get_dev());
    }


    static int nrows(const BatchedAtomsPack& _atoms){
      return _atoms.nrows1();
    }
    */

    //template<typename SOURCE, typename = typename std::enable_if<std::is_base_of<BatchedPtensors<float>, SOURCE>::value, SOURCE>::type>
    //static int nchannels(const SOURCE& x){
    //return x.get_nc()*vector<int>({1,2,5})[x.getk()];
    //}


  public: // ---- Linmaps ------------------------------------------------------------------------------------

    // these are hacks for the sake of BatchedSubgraphLayer1. todo: introduce constk


    Ptensors<TYPE> reduce0(const int K) const{
      TimedFn T("BatchedSubgraphLayer1b","reduce0",*this);
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      Ptensors<TYPE> R({dim(0)/K,get_nc()},0,get_dev());
      view3(K).sum1_into(R.view2());
      return R;
    }

    Ptensors<TYPE> reduce0(const int K, const int offs, const int nc) const{
      TimedFn T("BatchedSubgraphLayer1b","reduce0",*this);
      //cnine::using_vram_manager vv(ptens_session->managed_gmem);
      Ptensors<TYPE> R({dim(0)/K,nc},0,get_dev());
      view3(K,offs,nc).sum1_into(R.view2());
      return R;
    }

    void broadcast0(const int K, const Ptensors<TYPE>& x, const int offs){
      TimedFn T("BatchedSubgraphLayer1b","broadcast0",*this);
      PTENS_ASSRT(x.ndims()==2);
      view3(K,offs,x.dim(1))+=cnine::repeat1(x.view2(),K);
    }


  public: // ---- Message passing ----------------------------------------------------------------------------


    template<typename SOURCE, typename = typename std::enable_if<std::is_base_of<BatchedPtensors<float>, SOURCE>::value, SOURCE>::type>
    static BatchedPtensors1<TYPE> linmaps(const SOURCE& x){
      BatchedPtensors1<TYPE> R(x.atoms,x.get_nc()*vector<int>({1,2,5})[x.getk()],x.get_dev());
      R.add_linmaps(x);
      return R;
    }

    template<typename SOURCE, typename = typename std::enable_if<std::is_base_of<BatchedPtensors<float>, SOURCE>::value, SOURCE>::type>
    void add_linmaps(const SOURCE& x){
      for(int i=0; i<size(); i++)
	view_of(i).add_linmaps(x.view_of(i));
      //cnine::MultiLoop(size(),[&](const int i){view_of(i).add_linmaps(x.view_of(i));});
    }

    template<typename SOURCE, typename = typename std::enable_if<std::is_base_of<BatchedPtensors<float>, SOURCE>::value, SOURCE>::type>
    void add_linmaps_back(const SOURCE& x){
      for(int i=0; i<size(); i++)
	view_of(i).add_linmaps_back(x.view_of(i));
      //cnine::MultiLoop(size(),[&](const int i){view_of(i).add_linmaps_back(x.view_of(i));});
    }


  public: // ---- Message passing ----------------------------------------------------------------------------


    template<typename SOURCE, typename = typename std::enable_if<std::is_base_of<BatchedPtensors<float>, SOURCE>::value, SOURCE>::type>
    static BatchedPtensors1<TYPE> gather(const SOURCE& x, const BatchedAtomsPack& a, const int min_overlaps=1){
      BatchedPtensors1<TYPE> R(a,x.get_nc()*vector<int>({1,2,5})[x.getk()],x.get_dev());
      R.add_gather(x,min_overlaps);
      return R;
    }

    template<typename SOURCE>
    void add_gather(const SOURCE& x, const int min_overlaps=1){
      int N=size();
      PTENS_ASSRT(N==x.size());
      //for(int i=0; i<N; i++){
      //MessageList mlist=atoms.obj->obj[i]->atoms->overlaps_mlist(*x.atoms.obj->obj[i]->atoms,min_overlaps);
      //MessageMap mmap=atoms.obj->obj[i]->message_map(*mlist.obj,*x.atoms.obj->obj[i]);
      //forward_program.obj.push_back(mmap.obj);
      //backward_program.obj.push_back(to_share(new cnine::GatherMapProgram(mmap.obj->inv()))); // eliminate the copy here 
      //}
      //forward_program(*this,x);
    }

    template<typename OUTPUT>
    void add_gather_back(const OUTPUT& x){
      //x.atoms.inverse_overlaps_mmap(atoms)(*this,x);
      //for(int i=0; i<size(); i++)
      //view_of(i).add_gather_back(x.view_of(i));
      //cnine::MultiLoop(size(),[&](const int i){view_of(i).add_gather_back(x.view_of(i));});
      int N=size();
      PTENS_ASSRT(N==x.size());
      //cnine::GatherMapProgramPack P;
      //for(int i=0; i<N; i++){
      //MessageList mlist=x.atoms.obj->obj[i]->atoms->overlaps_mlist(*atoms.obj->obj[i]->atoms);
      //MessageMap mmap=x.atoms.obj->obj[i]->message_map(*mlist.obj,*atoms.obj->obj[i]);
      //P.obj.push_back(to_share(new cnine::GatherMapProgram(mmap.obj->inv()))); // eliminate the copy here 
      //}
      //P(*this,x);
    }

    
  public: // ---- I/O ----------------------------------------------------------------------------------------


    string classname() const{
      return "BatchedPtensors1";
    }

    string repr() const{
      return "<BatchedPtensors1[N="+to_string(size())+",nrows="+to_string(TENSOR::dim(0))+",nc="+to_string(get_nc())+"]>";
    }

    string str(const string indent="") const{ 
      ostringstream oss;
      for(int i=0; i<size(); i++){
	oss<<indent<<"Batch "<<i<<":"<<endl;
	oss<<(*this)[i].str(indent+"  ")<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const BatchedPtensors1& x){
      stream<<x.str(); return stream;}


  };

}

#endif 

    /*
    template<typename OUTPUT>
    void add_gather_back(const OUTPUT& x){
      //x.atoms.inverse_overlaps_mmap(atoms)(*this,x);
      //for(int i=0; i<size(); i++)
      //view_of(i).add_gather_back(x.view_of(i));
      //cnine::MultiLoop(size(),[&](const int i){view_of(i).add_gather_back(x.view_of(i));});
      int N=size();
      PTENS_ASSRT(N==x.size());
      //cnine::GatherMapProgramPack P;
      for(int i=0; i<N; i++){
	MessageList mlist=x.atoms.obj->obj[i]->atoms->overlaps_mlist(*atoms.obj->obj[i]->atoms);
	MessageMap mmap=x.atoms.obj->obj[i]->message_map(*mlist.obj,*atoms.obj->obj[i]);
	backward_program.obj.push_back(to_share(new cnine::GatherMapProgram(mmap.obj->inv()))); // eliminate the copy here 
      }
      backward_program(*this,x);
    }
    */

    /*
    template<typename OUTPUT>
    void add_gather_back_alt(const OUTPUT& x){
      int N=size();
      PTENS_ASSRT(N==x.size());
      cnine::GatherMapProgramPack P;
      for(int i=0; i<N; i++){
	P.obj.push_back(to_share(new cnine::GatherMapProgram(mmap.obj->inv()))); // eliminate the copy here 
      }
      P(*this,x);
    }
    */
