#include <iostream>
#include <chrono>
#include <fstream>

struct ListPair{
	char num;
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
	while (copy_pointer != nullptr){
		(*pointer).num = (*copy_pointer).num;
		(*pointer).tail = new ListPair;
		pointer = (*pointer).tail;
		copy_pointer = (*copy_pointer).tail;
	}
	(*pointer).tail = nullptr;
	return out;
}

List push_list(List &lst, char num){
	ListPair* lstpr = new ListPair;
	(*lstpr).num = num;
	(*lstpr).tail = lst.head;
	lst.head = lstpr;
	return lst;
}

char pop_list(List &lst){
	char out = (*lst.head).num;
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

int main(){
	std::ofstream myfile;
	myfile.open("data_list.csv");
	List lst = new_list();
	int multiplier = 2;
	int max = 100000000;
	int expnum = 30;
	for (int counter = 2; counter < max; counter *= multiplier){
		for(int j = 0; j<expnum; j++){
			auto start = std::chrono::steady_clock::now();
			for (int i = 0; i<counter; i++){
				push_list(lst, 'a');
			}
			auto stop = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
			delete_list(lst);
			lst = new_list();
			myfile << duration << ",";
		}
		myfile << "\n";
	}
}

