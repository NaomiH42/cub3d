#! /usr/bin/bash
class_name=$1
file=$class_name.hpp
echo "#ifndef ${class_name^^}_HPP
# define ${class_name^^}_HPP

#include <iostream>

class ${class_name^}
{

public:
	${class_name^}( void );
	~${class_name^}( void );
	${class_name^}( ${class_name^} &c);
	${class_name^} &operator=(${class_name^} &c);

private:

};

#endif" > ${class_name^}.hpp
