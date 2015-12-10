
Test class Object
C is an instance of class Point
C = (1,2)
C->isKindOf(*Object::desc()): 1
C->isKindOf(*Class::desc()): 0
C->isKindOf(*Rectangle::desc()): 0
C->isA()->isKindOf(*Object::desc()): 1
C->isA()->isKindOf(*Class::desc()): 1
C->isA()->isKindOf(*Rectangle::desc()): 0
