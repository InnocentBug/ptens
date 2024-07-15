import torch
import ptens_base as pb
import ptens as p

print("\n-------------------------------------")
print (" batched_ptensorlayer0")
print("-------------------------------------\n")

print("A batched_ptensorlayer0 stores a batch of ptensorlayer0 objects.\n\n")

print("We can define it from a collection of ptensor layers:\n")
subatoms=pb.atomspack.from_list([[1,3,4],[2,5],[0,2]])
a=p.ptensorlayer0.randn(subatoms,3)
A=p.batched_ptensorlayer0.from_ptensorlayers([a,a,a])
print(A)

print("Or define it from a torch tensor:\n")
atoms=pb.batched_atomspack([subatoms,subatoms,subatoms])
M=torch.randn([atoms.nrows0(),3])
A=p.batched_ptensorlayer0.from_matrix(atoms,M)
print(A)

print("If two batched P-tensor layers have the same reference domains,\nwe can do arithmetic on them:\n")
# Unfortunately these have to be added manually one-by-one
B=p.batched_ptensorlayer0.randn(atoms,3)
print(A+B)


print("\n---------")
print(" Linmaps")
print("---------\n")

print("The linmaps from a 0th order layer is just the identity map:\n")
A0=p.batched_ptensorlayer0.randn(atoms,3)
B=p.batched_ptensorlayer0.linmaps(A0)
print(B)

print("The linmaps from a 1st order layer sums each P-tensor along the atoms dimension:\n")
A1=p.batched_ptensorlayer1.randn(atoms,3)
B=p.batched_ptensorlayer0.linmaps(A1)
print(B)

print("The linmaps from a 2nd order P-tensor consists of")
print("(a) summing each P-tensor along both atoms dimensions")
print("(b) summing each P-tensor along its diagonal:\n")
A2=p.batched_ptensorlayer2.randn(atoms,3)
print(p.batched_ptensorlayer0.linmaps(A2))

exit(0) 

print("\n---------")
print(" Gather")
print("---------\n")


atoms2=pb.atomspack.random(5,5,0.6)
print(atoms2,"\n")

B0=p.batched_ptensorlayer0.gather(atoms2,A0)
print(B0)

B1=p.batched_ptensorlayer0.gather(atoms2,A1)
print(B1)

B2=p.batched_ptensorlayer0.gather(atoms2,A2)
print(B2)

