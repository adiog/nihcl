
Test class Dictionary
d = (1,1)=>(2,1)
(1,3)=>(2,3)
(1,2)=>(2,2)
d.atKey(Point(1,1)): (2,1)
d = (1,1)=>(3,1)
(1,3)=>(2,3)
(1,2)=>(2,2)
d.includesAssoc(c): 1
d.includesKey(*c.key()): 1
d.keyAtValue(Point(3,1)) = (1,1)
d.includesAssoc(c): 0
d.includesKey(*c.key()): 0
d.asBag: (2,2)
(3,1)
d.addKeysTo(keys): (1,1)
(1,2)
d.addValuesTo(vals): (3,1)
(2,2)
