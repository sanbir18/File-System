//SUBMIT this file
//complete all the missing LLDirectory implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "LLDirectory.h"

LLDirectory::LLDirectory(string name, FSObject* parent): Directory(name, parent), head(NULL){

}

LLDirectory::~LLDirectory(){
	LLNode* current = head;
	while(current != NULL){
		LLNode* temp = current->next;
		delete current->data;
		delete current;
		current = temp;
	}
}

bool LLDirectory::addChild(bool isDir, string name){
	if(!(getChild(name))){
		if(!head){
			head = new LLNode;
			if(isDir){
				head->data = new LLDirectory(name, this);
			}
			else{
				head->data = new File(name, this);
			}
			head->next = NULL;
			return true;
		}
		else{
			LLNode* previous = NULL;
			LLNode* current = head;
			while(current != NULL && name > current->data->getName()){
				previous = current;
				current = current->next;
			}
			LLNode* child = new LLNode;
			child->next = previous->next;
			previous->next = child;
			if(isDir)
				child->data = new LLDirectory(name, this);
			else
				child->data = new File(name, this);
		}
		return true;
	}
	return false;
}


bool LLDirectory::removeChild(string name){
	LLNode* previous = NULL;
	LLNode* current = head;
	if(getChild(name)){
		while(current->data->getName() != name && current != NULL){
			previous = current;
			current = current->next;
		}
		if(current != NULL){
			previous->next = current->next;
			delete current->data;
			delete current;
			return true;
		}
	}
	return false;
}

FSObject* LLDirectory::getChild(string name){
	for(LLNode* p = head; p != NULL; p = p->next){
		if(p->data->getName() == name){
			return p->data;
		}
	}
	return NULL;
}

FSObject* LLDirectory::getChild(int i){
	int count = 0;
	for(LLNode* p = head; p != NULL; p = p->next){
		if(count == i)
			return p->data;
		count += 1;
	}
	return NULL;
}

string LLDirectory::list(){
	if(this->getCount() == 0)
		return "<empty>";
	string list = "";
	for(LLNode* p = head; p != NULL; p = p->next){
		if(typeid(*(p->data)) == typeid(LLDirectory)){
			if(p->next == NULL)
				list +=  ("[" + p->data->getName() + "]");
			else
				list += ("[" + p->data->getName() + "] ");
		}
		else{
			if(p->next == NULL)
				list += (p->data->getName());
			else
				list += (p->data->getName() + " ");
		}
	}
	return list;
}

int LLDirectory::getCount(){
	int count = 0;
	for(LLNode* p = head; p != NULL; p = p->next){
		count += 1;
	}
	return count;
}
