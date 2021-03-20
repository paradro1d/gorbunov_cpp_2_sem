#include <cstring>
#include <iostream>

struct String{
	char *cstr;
	unsigned len;
	unsigned memlen;
};

String new_string(char const *cstr){
	String tmp;
	tmp.len = strlen(cstr);
	tmp.memlen = tmp.len * 2 + 1;
	tmp.cstr = new char[tmp.memlen];
	strcpy(tmp.cstr, cstr);
	return tmp;
}

String new_string(){
	String tmp;
	tmp.len = 0;
	tmp.cstr = new char[2];
	tmp.cstr[0] = 0;
	tmp.memlen = 2;
	return tmp;
}

String new_string(String const &src){
	String tmp;
	tmp.len = src.len;
	tmp.memlen = tmp.len*2 + 1;
	tmp.cstr = new char[tmp.memlen];
	for (int i = 0; i < tmp.len + 1; i++){
		tmp.cstr[i] = src.cstr[i];
	}
	return tmp;
}

void delete_string(String &str){
	delete [] str.cstr;
}

unsigned length(String const &str){
	return str.len;
}

String& copy(String &dst, String const &src){
	dst.len = length(src);
	delete_string(dst);
	dst.memlen = dst.len *2 +1;
	dst.cstr = new char[dst.memlen];
	for (int i=0;i<=dst.len;i++){
		dst.cstr[i] = src.cstr[i];
	}
	return dst;
}

char get_char_at(String const &str, unsigned pos){
	return str.cstr[pos - 1];
}
	
String& set_char_at(String &str, unsigned pos, char c){
	str.cstr[pos - 1] = c;
	return str;
}

String& append(String &dst, String const &src){
	if (dst.memlen > dst.len + src.len){
		for (int i = 0; i <= src.len; i++){
			dst.cstr[i + dst.len] = src.cstr[i];
		}
		dst.len = dst.len + src.len;
	}else{
		char* tmp = new char[(dst.len + src.len)*2 +1];
		for (int i = 0;i < dst.len;i++){
			tmp[i] = dst.cstr[i];
		}
		for (int i = 0;i <=src.len;i++){
			tmp[i + dst.len] = src.cstr[i];
		}
		dst.memlen = (dst.len + src.len)*2 +1;
		dst.len = dst.len + src.len;
		delete_string(dst);
		dst.cstr = tmp;
	}
	return dst;
}

String& append(String &dst, char const *cstr){
	String tmp = new_string(cstr);
	dst = append(dst, tmp);
	delete_string(tmp);
	return dst;
}

void print(String const &str){
	for (int i = 0; i< str.len; i++){
		std::cout << str.cstr[i];
	}
}

int main(){
	String str;
	String cpy;
	cpy = new_string();
	str = new_string("abababab");
	copy(cpy, str);
	append(cpy, str);
	append(cpy, "vvvvvvvv");
	print(cpy);
	return 0;
}

