#ifndef AYA_COMPARE_H
#define AYA_COMPARE_H

#include "../common.h"

namespace Comparator{
	const int MAX_BUF = 1 << 20;
	char __aya_buf1[MAX_BUF];
	char __aya_buf2[MAX_BUF];
	FILE *ayain, *ayaout, *ayaans;
	bool del_tempfile = true;
	bool open(const string outf, const string ansf){
		ayaout = fopen(outf.c_str(), "r");
		ayaans = fopen(ansf.c_str(), "r");
		if(ayaout == NULL){
			//log here.
			return false;
		}
		if(ayaans == NULL){
			//log here.
			return false;
		}
		return true;
	}
	void close(const string outf, const string ansf){
		fclose(ayaout), fclose(ayaans);
	}
	bool compare_bits(const string outf, const string ansf){
		if(!open(outf, ansf)){
			//log here.
			return false;
		}
		bool stop1 = false; int p1;
		bool stop2 = false; int p2;
		while(!stop1 && ! stop2){
			p1 = fread(__aya_buf1, 1, MAX_BUF, ayaout);
			p2 = fread(__aya_buf2, 1, MAX_BUF, ayaans);
			if(strcmp(__aya_buf1, __aya_buf2)){
				close(outf, ansf);
				return false;
			}
			if(!p1) stop1 = true;
			if(!p2) stop2 = true;
		}
		//log here.
		close(outf, ansf);
		return true;
	}
	bool compare_noip(const string outf, const string ansf){
		if(!open(outf, ansf)){
			//log here.
			return false;
		}
		bool stop1 = false; int p1 = 0, q1 = 0;
		bool stop2 = false; int p2 = 0, q2 = 0;
		int blank1 = 0, endline1 = 0;
		int blank2 = 0, endline2 = 0;
		bool find1 = false, find2 = false;
		while(!stop1 || !stop2){
			if(p1 == q1){
				p1 = 0;
				q1 = fread(__aya_buf1, 1, MAX_BUF, ayaout);
				if(p1 == q1) stop1 = true;
			}
			if(p2 == q2){
				p2 = 0;
				q2 = fread(__aya_buf2, 1, MAX_BUF, ayaans);
				if(p2 == q2) stop2 = true;
			}
			if(!stop1){
				if(isblank(__aya_buf1[p1])) blank1 ++; else 
				if(isspace(__aya_buf1[p1])){
					endline1 ++, blank1 = 0;
				} else find1 = true;
			}
			if(!stop2){
				if(isblank(__aya_buf2[p2])) blank2 ++; else 
				if(isspace(__aya_buf2[p2])){
					endline2 ++, blank2 = 0;
				} else find2 = true;
			}
			if(find1 && find2){
				if(endline1 != endline2 || blank1 != blank2){
					//log here.
					close(outf, ansf);
					return false;
				}
				if(__aya_buf1[p1] != __aya_buf2[p2]){
					//log here.
					close(outf, ansf);
					return false;
				}
				find1 = find2 = false;
			}
			if(find1 && stop2){
				//log here.
				close(outf, ansf);
				return false;
			}
			if(find2 && stop1){
				//log here.
				close(outf, ansf);
				return false;
			}
			if(!find1 && !stop1) ++ p1;
			if(!find2 && !stop2) ++ p2;
		}
		if(find1 || find2){
			//log here.
			close(outf, ansf);
			return false;
		}
		//log here.
		close(outf, ansf);
		return true;
	}
	bool program(string std_program, string bf_program, string gen_program,
		bool(*compare)(const string,const string) = compare_noip){
		printf("BEGIN\n");
		string temp = "__aya_template_file", cmd;
		int exit_code; bool stop = false , ok = false;
		bool gen_in = false , gen_out =false , gen_ans = false;
		cmd = gen_program + " > " + temp + ".in";
		if(exit_code = system(cmd.c_str())){
			//log here.
			stop = true;
		} else gen_in = true;
		cmd = std_program + " < " + temp + ".in"
			+ " > " + temp + ".out";
		if(exit_code = system(cmd.c_str())){
			//log here.
			stop = true;
		} else gen_out = true;
		cmd = bf_program  + " < " + temp + ".in"
			+ " > " + temp + ".ans";
		if(exit_code = system(cmd.c_str())){
			//log here.
			stop = true;
		} else gen_ans = true;
		
		if(exit_code = compare(temp + ".out", temp + ".ans")){
			//log here.
			ok = true;
		}

		if(ok && del_tempfile){
			if(gen_in ) cmd = "del " + temp + ".in"  ,system(cmd.c_str());
			if(gen_out) cmd = "del " + temp + ".out" ,system(cmd.c_str());
			if(gen_ans) cmd = "del " + temp + ".ans" ,system(cmd.c_str());
		}
		return ok;
	}
	bool program_n(int n, string std_program, string bf_program, string gen_program,
		bool(*compare)(const string,const string) = compare_noip){
		//log here.
		bool del_tempfile0 = del_tempfile;
		del_tempfile = false;
		__aya_up(0, n - 2, TEST_CASE){
			if(!program(std_program, bf_program, gen_program, compare))
				system("pause");
		}
		del_tempfile = del_tempfile0;
		if(!program(std_program, bf_program, gen_program, compare))
			system("pause");
		return true;
	}
};
bool cmp(const string a,const string b){
	return 1;
}
int main(){
	Comparator::del_tempfile=false;
	Comparator::program_n(100,"std.exe","bf.exe","gen.exe");
	return 0;
}