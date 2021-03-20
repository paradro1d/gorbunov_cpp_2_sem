#include <chrono>
#include <fstream>

struct String{
	char *cstr;
	unsigned len;
};

String new_string(){
	String tmp;
	tmp.len = 0;
	tmp.cstr = new char[1];
	tmp.cstr[0] = 0;
	return tmp;
}

void delete_string(String &str){
	delete [] str.cstr;
}

void append(String &dst, const char chr){
	char* tmp = new char[dst.len + 2];
	for (int i = 0;i < dst.len;i++){
		tmp[i] = dst.cstr[i];
	}
	tmp[dst.len] = chr;
	tmp[dst.len + 1] = 0;
	dst.len = dst.len + 1;
	delete [] dst.cstr;
	dst.cstr = tmp;
}

int main(){
	std::ofstream myfile;
	myfile.open("data_array.csv");
	String str = new_string();
	int multiplier = 2;
	int max = 40000;
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

