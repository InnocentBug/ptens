x=subgraphlayer0(G,x_in)

a=p.subgraphlayer1.gather(x,self.nodes)
a=self.linear(a,w0,b0)

b=p.subgraphlayer1.gather(x,self.edges)
b=self.linear(b,w1,b1)

c=p.subgraphlayer1.gather(x,self.cycle5)
b=self.linear(c,w2,b2)

d=p.subgraphlayer1.gather(x,self.cycle6)
d=self.linear(d,w3,b3)

z=sugraphlayer1.cat(a,b,c,d)
z=ReLU(z)

y=subgraphlayer2(z,S)

