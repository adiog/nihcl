/^class[ 	]*\([A-Z][a-zA-Z]*\)[ 	]*:[ 	]*public[ 	]*\([A-Z][a-zA-Z]*\)/{
N
s/^class \([A-Z][a-zA-Z]*\)[ 	]*:[ 	]*public \([A-Z][a-zA-Z]*\)\(.*\)\n[ 	]*DECLARE_MEMBERS(\([A-Z][a-zA-Z]*\))/class \1: public \2\3\
	DECLARE_MEMBERS(\4,\2)/w changes
}
