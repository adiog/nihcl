#! /bin/csh
rm -f CHANGES_C
foreach f (BitBoard.c Bitset.c Collection.c Date.c FDSet.c Float.c Fraction.c Integer.c Iterator.c Link.c LookupKey.c Point.c Random.c Range.c Rectangle.c Semaphore.c SharedQueue.c String.c Time.c)
	echo $f
	echo "**********" $f "**********" >>CHANGES_C
	sed -e 's/#define[ 	]*VIRTUAL_BASE_CLASSES[ 	]*$/#define VIRTUAL_BASE_CLASSES Object::desc()/w changes' <$f >+$f
	cat changes >>CHANGES_C
end
