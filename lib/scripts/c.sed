s/^DEFINE_CLASS[ 	]*(\([a-zA-Z 	]*\),\([a-zA-Z 	]*\),\([0-9 	]*\),\([a-zA-Z0-9_ 	]*\),\([a-zA-Z0-9_ 	]*\));/DEFINE_CLASS(\1,\2,\3,"$Header: c.sed,v 2.202 89/06/22 10:18:18 keith Exp $",\4,\5);/w changes
/^DEFINE_CLASS([^,]*,[^,]*,[0-9 ]*,[^,]*,[^,]*,[^,]*/{
h
s/^DEFINE_CLASS[ 	]*(\([a-zA-Z 	]*\),\([a-zA-Z 	]*\),\([0-9 	]*\),\(".*"\),\([a-zA-Z0-9_ 	]*\),\([a-zA-Z0-9_ 	]*\));/DEFINE_CLASS(\1,\3,\4,\5,\6);/w changes
x
s/[^,]*,[ 	]*\([a-zA-Z]*\).*/#define BASE_CLASSES \&class_\1\
#define MEMBER_CLASSES\
#define VIRTUAL_BASE_CLASSES\
/w changes
G
}
/^[ 	]*\([A-Z][a-zA-Z0-9_]*\)::\1(istream\&[ 	]*strm,[ 	]*\1\&[ 	]*where[ 	]*)/{
N
s/\((istream\&[ 	]*strm,[ 	]*[A-Z][a-zA-Z0-9_]*\&[ 	]*where[ 	]*)\)[ 	]*\n[ 	]*{/\1\
\	: (strm,where)\
{/w changes
s/\((istream\&[ 	]*strm,[ 	]*[A-Z][a-zA-Z0-9_]*\&[ 	]*where[ 	]*)\)[ 	\n]*:[ 	\n]*\([A-Za-z_]\)/\1\
\	: (strm,where),\
\	\2/w changes
}
/^[ 	]*\([A-Z][a-zA-Z0-9_]*\)::\1(fileDescTy\&[ 	]*fd,[ 	]*\1\&[ 	]*where[ 	]*)/{
N
s/\((fileDescTy\&[ 	]*fd,[ 	]*[A-Z][a-zA-Z0-9_]*\&[ 	]*where[ 	]*)\)[ 	]*\n[ 	]*{/\1\
\	: (fd,where)\
{/w changes
s/\((fileDescTy\&[ 	]*fd,[ 	]*[A-Z][a-zA-Z0-9_]*\&[ 	]*where[ 	]*)\)[ 	\n]*:[ 	\n]*\([A-Za-z_]\)/\1\
\	: (fd,where),\
\	\2/w changes
}
/^[ 	]*Object[*][ 	]*[A-Z][a-zA-Z0-9_]*::add[ 	]*(/s/const[ 	]*Object/Object/gw changes
/^[ 	]*Object[*][ 	]*[A-Z][a-zA-Z0-9_]*::addLast[ 	]*(/s/const[ 	]*Object/Object/gw changes
/^[ 	]*void[ 	]*[A-Z][a-zA-Z0-9_]*::atAllPut[ 	]*(/s/const[ 	]*Object/Object/gw changes
/^[ 	]*Assoc[*][ 	]*[A-Z][a-zA-Z0-9_]*::addAssoc[ 	]*(/s/const[ 	]*Object/Object/gw changes
/^[ 	]*Object[*][ 	]*[A-Z][a-zA-Z0-9_]*::atKey[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/^[ 	]*Object[*][ 	]*[A-Z][a-zA-Z0-9_]*::addAfter[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/^[ 	]*Object[*][ 	]*[A-Z][a-zA-Z0-9_]*::addBefore[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/^[ 	]*Object[*][ 	]*[A-Z][a-zA-Z0-9_]*::addAtIndex[ 	]*(/s/,[ 	]*const Object\&/, Object\&/w changes
/^#if/s/ATT3B/att3b/gw changes
/^#if/s/MASSCOMP/mc300/gw changes
/^#if/s/RTPC/ibm032/gw changes
/^#if/s/SUN3/sun/gw changes
/^#if/s/VAX/vax/gw changes
s/^[ 	]*\([A-Z][a-zA-Z0-9_]*\)::\1(fileDescTy\&\([^,]*\),[ 	]*\1\&[^)]*)/\1::\1(OIOfd\&\2)/w changes
s/^[ 	]*\([A-Z][a-zA-Z0-9_]*\)::\1(istream\&\([^,]*\),[ 	]*\1\&[^)]*)/\1::\1(OIOistream\&\2)/w changes
s/:[ 	]*(strm,where)/: (strm)/w changes
s/:[ 	]*(fd,where)/: (fd)/w changes
/this[ 	]*=[ 	]*\&where/d
/^[ 	]*void[ 	]*[A-Z][a-zA-Z0-9_]*::storer/s/fileDescTy/OIOfd/w changes
/^[ 	]*void[ 	]*[A-Z][a-zA-Z0-9_]*::storer/s/\([^a-zA-Z0-9_]\)ostream/\1OIOostream/w changes
s/readBin(\([a-zA-Z0-9_]*\)[ 	]*,[ 	]*\([^,]*,\)/\1.get(\2/w changes
s/storeBin(\([a-zA-Z0-9_]*\)[ 	]*,[ 	]*\([^,]*,\)/\1.put(\2/w changes
s/readBin(\([a-zA-Z0-9_]*\)[ 	]*,[ 	]*\([^,)]*\))/\1 >> \2/w changes
s/storeBin(\([a-zA-Z0-9_]*\)[ 	]*,[ 	]*\([^,)]*\))/\1 << \2/w changes
/strm[ 	]*<</s/[ 	]*<<[ 	]*"[ 	]"//gw changes
s/[ 	]oops/ nihcl/gw changes
s/[ 	]OOPS/ NIHCL/gw changes
s/^oops/nihcl/
s/^OOPS/NIHCL/
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
