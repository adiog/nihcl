
Test class KeySortCltn
A=>Ant
C=>Cat
E=>Emu
E=>Eeyore
H=>25-Dec-85
J=>98.6
M=>Man
Z=>29-Jan-63 9:30:00 pm
index 0 before key A
index 6 before key M
index 1 before key C
index 3 before key E
index 7 before key Z
index 3 before key F
index -1 before key @
index 7 before key [
clone isEqual c: 1
clone == c: 1
clone != c: 0
c.compare(clone) = 0
c.includesKey(String("J")) = 1
c.includesKey(String("K")) = 0
c.occurrencesOfKey(String("Q")) = 0
c.occurrencesOfKey(String("M")) = 1
c.occurrencesOfKey(String("E")) = 2
atKey(String("J")) = 98.6
atKey(String("N")) = NIL

OrderedCltn o =
Ant
Cat
Emu
Eeyore
25-Dec-85
98.6
Man
29-Jan-63 9:30:00 pm
A
C
E
E
H
J
M
Z

SortedCltn b =
A=>Ant
C=>Cat
E=>Emu
E=>Eeyore
*c.removeKey(String("Z")) = Z=>29-Jan-63 9:30:00 pm
*c.removeKey(String("Q")) = NIL
*c.removeKey(String("E")) = E=>Emu
A=>Ant
C=>Cat
E=>Eeyore
H=>25-Dec-85
J=>98.6
M=>Man

apple
bat
cat
dog=>1
apple
bat
cat
eagle=>2
apple
bat
cat
gopher=>0
index apple
bat
cat
dog
before key 0
