#include <chrono>
#include <fstream>

struct String{
	char *cstr;
	unsigned len;
	unsigned memlen;
};

String new_string(){
	String tmp;
	tmp.len = 0;
	tmp.cstr = new char[2];
	tmp.cstr[0] = 0;
	tmp.memlen = 2; 
	return tmp;
}

void delete_string(String &str){
	delete [] str.cstr;
}

void append(String &dst, const char chr){
	if (dst.len + 1 < dst.memlen){
		dst.cstr[dst.len] = chr;
		dst.cstr[dst.len + 1] = 0;
	}else{
		dst.memlen = dst.len*2 + 1;
		char* tmp = new char[dst.memlen];
		for (int i = 0;i < dst.len - 1;i++){
			tmp[i] = dst.cstr[i];
		}
		tmp[dst.len] = chr;
		tmp[dst.len + 1] = 0;
		delete [] dst.cstr;
		dst.cstr = tmp;
	}
	dst.len = dst.len + 1;
}

int main(){
	std::ofstream myfile;
	myfile.open("data_array_amortised.csv");
	String str = new_string();
	int multiplier = 2;
	int max = 100000000;
	int expnum = 30;
	for (int counter = 2; counter < max; counter *= multiplier){
		for(int j = 0; j<expnum; j++){
			auto start = std::chrono::steady_clock::now();
			for (int i = 0; i<counter; i++){
				append(str, 'a');
			}
			auto stop = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
			delete_string(str);
			str = new_string();
			myfile << duration << ",";
		}
		myfile << "\n";
	}
}

