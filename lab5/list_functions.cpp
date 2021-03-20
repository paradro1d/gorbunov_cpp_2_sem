#include <iostream>

struct ListPair{
	int num;
	ListPair *tail;
};

struct List{
	ListPair *head;
};

List new_list(){
	List out;
	out.head = nullptr;
	return out;
}

List new_list(List const &lst){
	List out;
	ListPair* pointer = new ListPair;
	ListPair* copy_pointer = lst.head;
	out.head = pointer;
	while ((*copy_pointer).tail != nullptr){
		(*pointer).num = (*copy_pointer).num;
		(*pointer).tail = new ListPair;
		pointer = (*pointer).tail;
		copy_pointer = (*copy_pointer).tail;
	}
	(*pointer).tail = nullptr;
	return out;
}

List push_list(List &lst, int num){
	ListPair* lstpr = new ListPair;
	(*lstpr).num = num;
	(*lstpr).tail = lst.head;
	lst.head = lstpr;
	return lst;
}

char pop_list(List &lst){
	int out = (*lst.head).num;
	ListPair* tmp = lst.head;
	lst.head = (*lst.head).tail;
	delete tmp;
	return out;
}

char peak_list(List const &lst){
	return (*lst.head).num;
}

void delete_list(List &lst){
	ListPair* pointer = lst.head;
	ListPair* tmp;
	while(pointer != nullptr){
		tmp = pointer;
		pointer = (*pointer).tail;
		delete tmp;
	}
}

bool is_empty(List const &lst){
	if (lst.head == nullptr){
		return true;
	}else{
		return false;
	}
}

List reverse_list(List &lst){
	ListPair* pointer = lst.head;
	ListPair* tmpNext;
	ListPair* tmpLast;
	tmpLast = nullptr;
	while (pointer != nullptr){
		tmpNext = (*pointer).tail;
		(*pointer).tail = tmpLast;
		tmpLast = pointer;
		pointer = tmpNext;
	}
	lst.head = tmpLast;
	return lst;
}

void print_list(List &lst){
	ListPair* pointer = lst.head;
	while(pointer !=nullptr){
		std::cout << (*pointer).num;
		pointer = (*pointer).tail;
	}
}
int main(){
	List lst = new_list();
	List cpy;
	print_list(lst);
	for (int i = 0; i <10; i++){
		push_list(lst, i);
	}
	print_list(lst);
	cpy = new_list(lst);
	reverse_list(cpy);
	print_list(cpy);
	delete_list(cpy);
	cpy = new_list();
	if (is_empty(lst)){
		std::cout << 'a';
	}
	delete_list(lst);
	return 0;
}
