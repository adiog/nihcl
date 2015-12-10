
Test class Iterator
OrderedCltn[Point[(0,0)]
Point[(1,1)]
Point[(2,2)]
Point[(3,3)]
Point[(4,4)]
Point[(5,5)]
]
Set[Point[(0,0)]
Point[(5,5)]
Point[(4,4)]
Point[(3,3)]
Point[(2,2)]
Point[(1,1)]
]
LinkedList[Point[(0,0)]
Point[(5,5)]
Point[(4,4)]
Point[(3,3)]
Point[(2,2)]
Point[(1,1)]
]
Heap[Point[(0,0)]
Point[(1,1)]
Point[(2,2)]
Point[(3,3)]
Point[(4,4)]
Point[(5,5)]
]

Test Iterator(OrderedCltn).storeOn()
Iterator[OrderedCltn[0]#0]
(0,0)(1,1)(2,2)
Iterator[OrderedCltn[3]#0]

Test Iterator(OrderedCltn) readFrom()
Iterator[OrderedCltn[3]#0]
(3,3)(4,4)(5,5)
Test Iterator(OrderedCltn).deepCopy()
Iterator[OrderedCltn[3]#0]
(3,3)(4,4)(5,5)
Test Iterator(OrderedCltn).reset()
Iterator[OrderedCltn[0]#0]
(0,0)(1,1)(2,2)(3,3)(4,4)(5,5)

Test Iterator(LinkedList).storeOn()
Iterator[LinkedList[0]#0]
(0,0)(5,5)(4,4)
Iterator[LinkedList[3]#0]

Test Iterator(LinkedList) readFrom()
Iterator[LinkedList[3]#0]
(3,3)(2,2)(1,1)
Test Iterator(LinkedList).deepCopy()
Iterator[LinkedList[3]#0]
(3,3)(2,2)(1,1)
Test Iterator(LinkedList).reset()
Iterator[LinkedList[0]#0]
(0,0)(5,5)(4,4)(3,3)(2,2)(1,1)

Test Iterator(Heap).storeOn()
Iterator[Heap[0]#0 Heap[Point[(0,0)]
Point[(1,1)]
Point[(2,2)]
Point[(3,3)]
Point[(4,4)]
Point[(5,5)]
]
]
(0,0)(1,1)(2,2)
Iterator[Heap[3]#0 Heap[Point[(3,3)]
Point[(4,4)]
Point[(5,5)]
]
]

Test Iterator(Heap) readFrom()
Iterator[Heap[3]#0 Heap[Point[(3,3)]
Point[(4,4)]
Point[(5,5)]
]
]
(3,3)(4,4)(5,5)
Test Iterator(Heap).deepCopy()
Iterator[Heap[3]#0 Heap[Point[(3,3)]
Point[(4,4)]
Point[(5,5)]
]
]
(3,3)(4,4)(5,5)
Test Iterator(Heap).reset()
Iterator[Heap[0]#0 Heap[Point[(0,0)]
Point[(1,1)]
Point[(2,2)]
Point[(3,3)]
Point[(4,4)]
Point[(5,5)]
]
]
(0,0)(1,1)(2,2)(3,3)(4,4)(5,5)
