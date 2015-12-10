
Test class SeqCltn
b = (1,1)
(1,2)
(1,3)
(1,3)
b.first() == b.SeqCltn::first(): 1
b.last() == b.SeqCltn::last(): 1
b.hash() == b.SeqCltn::hash(): 1
b.indexOf(D) == b.SeqCltn::indexOf(D): 1
b.occurrencesOf(D) == b.SeqCltn::occurrencesOf(D): 1
c = (1,1)
(1,2)
(1,3)
(1,3)
b.isEqual(c) == b.SeqCltn::isEqual(c): 1
c = (1,1)
(1,2)
(1,3)
(0,0)
b.isEqual(c) == b.SeqCltn::isEqual(c): 1
