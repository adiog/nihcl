/^public:/{
N
s/^public:.*\n[ 	]*public:/public:/w changes
s/^public:.*\n[ 	]*protected:/protected:/w changes
s/^public:.*\n[ 	]*private:/private:/w changes
}
/^protected:/{
N
s/^public:.*\n[ 	]*public:/public:/w changes
s/^public:.*\n[ 	]*protected:/protected:/w changes
s/^public:.*\n[ 	]*private:/private:/w changes
}
