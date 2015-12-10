/overload[ 	]*[A-Z][a-zA-Z0-9_]*_reader;/d
/friend[ 	]*void[ 	]*[A-Z][a-zA-Z0-9_]*_reader(istream\&/d
/friend[ 	]*void[ 	]*[A-Z][a-zA-Z0-9_]*_reader(fileDescTy\&/d
s/^[ 	]*extern[ 	]*Class[ 	]*class_\([A-Z][a-zA-Z0-9_]*\)/extern const Class class_\1/w changes
/virtual[ 	]*void[ 	]*printOn[ 	]*/s/([ 	]*ostream\&[^)]*)/(ostream\& strm =cout)/w changes
/virtual[ 	]*void[ 	]*dumpOn[ 	]*/s/([ 	]*ostream\&[^)]*)/(ostream\& strm =cerr)/w changes
/virtual[ 	]*Object[*][ 	]*add[ 	]*(/s/const[ 	]*Object/Object/gw changes
/virtual[ 	]*Object[*][ 	]*addLast[ 	]*(/s/const[ 	]*Object/Object/gw changes
/virtual[ 	]*void[ 	]*atAllPut[ 	]*(/s/const[ 	]*Object/Object/gw changes
/virtual[ 	]*Assoc[*][ 	]*addAssoc[ 	]*(/s/const[ 	]*Object/Object/gw changes
/virtual[ 	]*Object[*][ 	]*atKey[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/virtual[ 	]*Object[*][ 	]*addAfter[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/virtual[ 	]*Object[*][ 	]*addBefore[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/virtual[ 	]*Object[*][ 	]*addAtIndex[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/^#if/s/ATT3B/att3b/gw changes
/^#if/s/MASSCOMP/mc300/gw changes
/^#if/s/RTPC/ibm032/gw changes
/^#if/s/SUN3/sun/gw changes
/^#if/s/VAX/vax/gw changes
s/^[ 	]*\([A-Z][a-zA-Z0-9_]*\)(fileDescTy\&\([^,]*\),[ 	]*\1\&[^)]*)/	\1(OIOfd\&\2)/w changes
/^[ 	]*[A-Z][a-zA-Z0-9_]*(OIOfd\&/s/,[ 	]*where//w changes
s/^[ 	]*\([A-Z][a-zA-Z0-9_]*\)(istream\&\([^,]*\),[ 	]*\1\&[^)]*)/	\1(OIOistream\&\2)/w changes
/^[ 	]*[A-Z][a-zA-Z0-9_]*(OIOistream\&/s/,[ 	]*where//w changes
/^[ 	]*virtual[ 	]*void[ 	]*storer/s/fileDescTy/OIOfd/w changes
/^[ 	]*virtual[ 	]*void[ 	]*storer/s/ostream/OIOostream/w changes
s/ oops/ nihcl/gw changes
s/ OOPS/ NIHCL/gw changes
s/\toops/\tnihcl/gw changes
s/\tOOPS/\tNIHCL/gw changes
s/^oops/nihcl/
s/^OOPS/NIHCL/
s/\"OOPS/\"NIHCL/
s/\"oops/\"nihcl/
s/oops_/nihcl_/gw changes
s/OOPS_/NIHCL_/gw changes
s/setOOPS/setNIHCL/gw changes
s/_OOPS/_NIHCL/gw changes
s/oopsOIO/nihclOIO/gw changes
s/oopsIO/nihclIO/gw changes
s/OOPSOIO/NIHCLOIO/gw changes
s/OOPSIOH/NIHCLIOH/gw changes
s/OOPSCONFIG/NIHCLCONFIG/gw changes
s/oopsconfig/nihclconfig/gw changes
s/oopserrs/nihclerrs/gw changes
s/oopserrsx/nihclerrsx/gw changes
s/\b\"OOPS:/\"NIHCL:/gw changes
s/-OOPS/-NIHCL/gw changes
s/liboops/libnihcl/gw changes
s/OOPSLIB/NIHCLLIB/gw changes
s/OOPSLIBDIR/NIHCLLIBDIR/gw changes
s/OOPSINCDIR/NIHCLINCDIR/gw changes
s/OOPSSRCDIR/NIHCLSRCDIR/gw changes
s/OOPSLIB/NIHCLLIB/gw changes
s/OOPSINC/NIHCLINC/gw changes
s/OOPSSRC/NIHCLSRC/gw changes
s/\/oops/\/nihcl/gw changes
s/>oops/>nihcl/gw changes
s/uunet!ncifcrf.gov!nih-csl!keith/uunet!nih-csl!keith/gw changes
s/{decvax!}seismo!elsie!cecil!keith/uunet!nih-csl!keith/gw changes
s/ keith%nih-csl@ncifcrf.gov/keith@alw.nih.gov/gw changes
s/OIOistream/OIOin/gw changes
s/OIOostream/OIOout/gw changes
s/<<[ 	]*"\(.\)"/<< '\1'/gw changes
s/<<[ 	]*"\(\\.\)"/<< '\1'/gw changes
s/CLTN_DEFAULT_CAPACITY/DEFAULT_CAPACITY/w changes
s/CLTN_EXPANSION_INCREMENT/EXPANSION_INCREMENT/w changes
s/CLTN_EXPANSION_FACTOR/EXPANSION_FACTOR/w changes
