 //SUBMIT this file
//complete all the missing SADirectory implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "SADirectory.h"

SADirectory::SADirectory(string name, FSObject* parent): Directory(name, parent), count(0){
	for(int i = 0; i < DIR_SIZE; i++)
		this->children[i] = NULL;
}

SADirectory::~SADirectory(){
	for(int i = 0; i < count; i++)
		delete children[i];
}

bool SADirectory::addChild(bool isDir, string name){
	if(!(getChild(name))){
		if(count != DIR_SIZE){
			if(isDir){
				children[count] = new SADirectory(name, this);
				count += 1;
			}
			else{
				children[count] = new File(name, this);
				count += 1;
			}
			return true;
		}
	}
	return false;
}

bool SADirectory::removeChild(string name){
	for(int i = 0; i < count; i++){
		if(children[i]->getName() == name){
			delete children[i];
			if(i != count - 1){
				for(int j = i; j < count; j++)
					children[j] = children[j + 1];
			}
			count -= 1;
			return true;
		}
	}
	return false;
}

FSObject* SADirectory::getChild(string name){
	for(int i = 0; i < count; i++){
		if(children[i]->getName() == name)
			return children[i];
	}
	return NULL;
}

FSObject* SADirectory::getChild(int i){
	if(i >= 0 && i < DIR_SIZE)
		return children[i];
	return NULL;
}

string SADirectory::list(){
	string list = "";
	if(count == 0)
		return "<empty>";
	else{
		for(int i = 0; i < count; i++)
			if(typeid(*children[i]) == typeid(SADirectory)){
				if(i != count - 1)
					list += ("[" + children[i]->getName() + "] ");
				else
					list += ("[" + children[i]->getName() + "]");
			}
			else{
				if(i != count - 1)
					list += children[i]->getName() + " ";
				else
					list += children[i]->getName();
			}
	}
	return list;
}

int SADirectory::getCount(){
	return count;
}


