
Test class OrderedCltn
b = (1,1)
(1,2)
(1,3)
(1,3)
b.first(): (1,1)
b.last(): (1,3)
b = (1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
b.after(Point(1,2)): (1,21)
b.before(Point(1,2)): (1,19)
b.includes(C): 1
c == b: 1
b.compare(c): 0
c = 
b = (1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
(1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
b.compare(c): 1
c.compare(b): -1
b.includes(C): 1
b = (1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
c == b: 0
b.compare(c): -2
c&b:(1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
(1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
b.indexOfSubCollection(c): -1
c = (1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
b.replaceFrom(1,3,c): (1,1)
(1,1)
(1,19)
(1,2)
(1,3)
(1,1)
(1,19)
(1,2)
(1,21)
(1,3)
(1,3)
b.sort(): (1,1)
(1,1)
(1,1)
(1,2)
(1,2)
(1,3)
(1,3)
(1,3)
(1,19)
(1,19)
(1,21)
b.asSet(): (1,1)
(1,19)
(1,3)
(1,21)
(1,2)
c.removeId(D)->isSame(D): 1
