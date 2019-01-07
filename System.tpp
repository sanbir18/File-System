//SUBMIT this file
//complete all the missing System implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "System.h"

template <typename T>
System<T>::System(){
	root = new T ("\\", NULL);
}

template<typename T>
System<T>::~System(){
	delete root;
}

template<typename T>
bool System<T>::isValidPath(string path){
	if(path.length() >= 1 && path.substr(0,1) == "\\")
		return true;
	return false;
}

template<typename T>
Directory* System<T>::getRoot(){
	return root;
}

template<typename T>
Directory* System<T>::getDirectory(string path){
	Directory* dir = root;
	int pos = path.find("\\");
	if(path.length() == 1)
		return dir;
	else{
		while(pos != static_cast<int>(string::npos)){
			if(dir->getChild(path.substr(pos + 1, path.substr(pos + 1).find("\\")))){
				dir = dynamic_cast<Directory*>(dir->getChild(path.substr(pos + 1, path.substr(pos + 1).find("\\"))));
			}
			else{
				dir = NULL;
				break;
			}
			path.erase(0, pos + 1);
			pos = path.find("\\");
		}
		return dir;
	}
	return NULL;

}

template<typename T>
File* System<T>::getFile(string path, string name){
	if(getDirectory(path) /*&& !(getDirectory(path + "\\" + name))*/)
		return dynamic_cast<File*>(getDirectory(path)->getChild(name));
	return NULL;
}

template<typename T>
int System<T>::addDir(string path, string name){
	if(!(isValidPath(path)))
		return -1;
	else{
		if(!(getDirectory(path)))
			return -2;
		else{
			if(getDirectory(path)->addChild(true, name))
				return 0;
			else
				return -3;
		}
	}
}

template<typename T>
int System<T>::addFile(string path, string name, string content){
	if(!(isValidPath(path)))
		return -1;
	else{
		if(!(getDirectory(path)))
			return -2;
		else{
			if(getDirectory(path)->addChild(false, name)){
				dynamic_cast<File*>(getDirectory(path)->getChild(name))->setContent(content);
				return 0;
			}
			else
				return -3;
		}
	}
}

template<typename T>
string System<T>::list(string path){
	if(isValidPath(path)){
		if(getDirectory(path)){
			return getDirectory(path)->list();
		}
		else if(!(getDirectory(path)))
			return "<nope>";
	}
	return "";
}

template<typename T>
int System<T>::del(string path, string name){
	if(isValidPath(path)){
		if(getDirectory(path)){
			if(getDirectory(path)->removeChild(name))
				return 0;
			else
				return -3;
		}
		else{
			return -2;
		}
	}
	else{
		return -1;
	}
}

template<typename T>
int System<T>::move(string fromPath, string fromName, string toPath, string toName){
	if(!(isValidPath(fromPath)) || !(isValidPath(toPath))){
		return -1;
	}
	else{
		if(!(getDirectory(fromPath)) || !(getDirectory(toPath))){
			return -2;
		}
		else{
			if(fromPath == "\\"){
				if(getDirectory(fromPath + fromName)){
					addDir(toPath, toName);
					for(int i = 0 ; i < getDirectory(fromPath + fromName)->getCount(); i++){
						move(fromPath + fromName, getDirectory(fromPath + fromName)->getChild(i)->getName(), toPath + "\\" + toName, getDirectory(fromPath + fromName)->getChild(i)->getName());
					}
					del(fromPath, fromName);
				}
			}
			else{
				if(getDirectory(fromPath + "\\" + fromName)){
					addDir(toPath,toName);
					for(int i = 0 ; i < getDirectory(fromPath + "\\" + fromName)->getCount(); i++){
						move(fromPath + "\\" + fromName, getDirectory(fromPath + "\\" + fromName)->getChild(i)->getName(), toPath + "\\" + toName, getDirectory(fromPath + "\\" + fromName)->getChild(i)->getName());
					}
					del(fromPath + "\\", fromName);
				}
			}
			if(getFile(fromPath, fromName)){
				addFile(toPath, toName, getFile(fromPath, fromName)->getContent());
				if(fromPath == "\\")
					del(fromPath, fromName);
				else
					del(fromPath + "\\", fromName);
			}
		}
	}
	return 0;
}
