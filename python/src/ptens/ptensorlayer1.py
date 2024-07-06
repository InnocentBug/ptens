#
# This file is part of ptens, a C++/CUDA library for permutation 
# equivariant message passing. 
#  
# Copyright (c) 2023, Imre Risi Kondor
#
# This source code file is subject to the terms of the noncommercial 
# license distributed with cnine in the file LICENSE.TXT. Commercial 
# use is prohibited. All redistributed versions of this file (in 
# original or modified form) must retain this copyright notice and 
# must be accompanied by a verbatim copy of the license. 
#
#

import torch

import ptens_base as pb 
from ptens_base import ptensors0 as _ptensors0
from ptens_base import ptensors1 as _ptensors1
from ptens_base import ptensors2 as _ptensors2

import ptens as p
import ptens.ptensorlayer as ptensorlayer
import ptens.ptensor1 as ptensor1


class ptensorlayer1(ptensorlayer):

    @classmethod
    def zeros(self,atoms,nc,device='cpu'):
        assert isinstance(atoms,pb.atomspack)
        assert isinstance(nc,int)
        R=ptensorlayer1(torch.zeros([atoms.nrows1(),nc],device=device))
        R.atoms=atoms
        return R

    @classmethod
    def randn(self,atoms,nc,device='cpu'):
        assert isinstance(atoms,pb.atomspack)
        assert isinstance(nc,int)
        R=ptensorlayer1(torch.randn([atoms.nrows1(),nc],device=device))
        R.atoms=atoms
        return R

    @classmethod
    def from_matrix(self,atoms,M):
        assert isinstance(atoms,pb.atomspack)
        assert isinstance(M,torch.Tensor)
        assert M.dim()==2
        assert M.size(0)==atoms.nrows1()
        R=ptensorlayer1(M)
        R.atoms=atoms
        return R

    def clone(self):
        r=ptensorlayer1(super().clone())
        r.atoms=self.atoms
        return r


    # ----- Access -------------------------------------------------------------------------------------------


    def getk(self):
        return 1
    
    def __len__(self):
        return len(self.atoms)
    
    def get_nc(self):
        return self.size(1)
    
    def __getitem__(self,i):
        assert i<len(self)
        offs=self.atoms.row_offset1(i)
        n=self.atoms.nrows1(i)
        return ptensor1.from_matrix(self.atoms[i],torch.Tensor(self)[offs:offs+n])


    # ---- Linmaps -------------------------------------------------------------------------------------------
    

    @classmethod
    def linmaps(self,x):
        if isinstance(x,p.ptensorlayer0):
            return broadcast0(x)
        if isinstance(x,p.ptensorlayer1):
            nc=x.get_nc()
            r=p.ptensorlayer0.zeros(atoms,2*nc)
            r[:,0:nc]=broadcast(x.reduce0())
            r[:,nc:2*nc]=x
            return r

    def reduce0(self):
        if self.atoms.is_constk():
            k=self.atoms.constk()
            a=reshape(size(0)/k,k,size(1))
            return ptensorlayer0(atoms,a.sum(dim=1)) 
        else:
            r=p.ptensorlayer0.zeros(self.atoms,self.get_nc())
            _ptensors1(self.atoms,self).add_reduce0_to(_ptensors0(self.atoms,r))
            return r

    @classmethod
    def broadcast(self,x):
        if isinstance(x,ptensorlayer0):
            if self.atoms.is_constk():
                a=x.unsqueeze(1).expand(x.size(0),self.atoms.constk(),x.size(1))
                return p.ptensorlayer1(atoms,a) 
            else:
                raise RuntimeError("Unimplemented")


    # ---- Message passing -----------------------------------------------------------------------------------


    @classmethod
    def gather(self,atoms,x,map):
        return Ptensorsb_Gather0Fn.apply(x,S)


    # ---- I/O ----------------------------------------------------------------------------------------------


    def __repr__(self):
        return "ptensorlayer1(len="+str(len(self.atoms))+",nc="+str(self.size(1))+")"

    def __str__(self):
        r=""
        for i in range(len(self)):
            r=r+str(self[i])+"\n"
        return r





#     def __init__(self,atoms,M):
#         assert isinstance(atoms,pb.atomspack)
#         assert isinstance(M,torch.Tensor)
#         assert M.dim()==2
#         assert M.size(0)==atoms.nrows1()
#         R=ptensorlayer1(M)
#         R.atoms=atoms
#         return R

