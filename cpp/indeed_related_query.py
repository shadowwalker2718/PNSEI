s=[['a','python'],['a','java'],['a','java2'],['a','php'],['a','python2'],['a','java3'],['a','java']]
s=[['a','x'],['a','x'],['a','x'],['a','x'],['a','x'],['a','x'],['a','x']]
s=[['a','python'],['b','java'],['a','java'],['b','php'],['c','python'],['c','java'],['d','java']]

# O(N^2)

d,m={},{}
e=0
for i, j in s: #O(N)
  #print e, '::: ',i, j, d
  e+=1
  if m.has_key(j):
    print "&"+ str(m[j])+" "
    e+=len(m[j]) #O(N)
    rs,mx={0:[]},0 # freq => string list
    for (x,y) in m[j].items():
      if mx<=y:
        mx=y
        rs.setdefault(mx,[]).append(x)
    print str(mx)+'>>>'+str(rs[mx])
  if d.has_key(i):
    for k in d[i]: #O(N)
      e+=1
      if j!=k: # BUG1
        m.setdefault(j,{}).setdefault(k,0)
        m.setdefault(k,{}).setdefault(j,0)
        m[j][k]+=1
        m[k][j]+=1
    #print m
    d[i].append(j)
  else:
    d[i]=[j]
    #if m.has_key(j):
    #  print '...'+str(m[j])

print e



