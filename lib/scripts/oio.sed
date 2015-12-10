s/^[ 	]*:[ 	]*BASE(strm)/:\
#ifdef MI\
\	Object(strm),\
#endif\
\	BASE(strm)/w changes
s/^[ 	]*:[ 	]*BASE(fd)/:\
#ifdef MI\
\	Object(fd),\
#endif\
\	BASE(fd)/w changes
