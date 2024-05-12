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

class ptensorlayerc(torch.Tensor):

    def clone(self):
        r=ptensorlayerc(super().clone())
        r.atoms=self.atoms
        return r


    # ---- Operations ----------------------------------------------------------------------------------------


    def __add__(self,y):
        assert self.size==y.size
        assert self.atoms==y.atoms
        r=self.clone()
        r+=y
        return r



def matmul(x,y):
    return x.from_matrix(x.atoms,torch.matmul(x,y))

mm=matmul
