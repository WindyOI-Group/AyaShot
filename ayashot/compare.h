#ifndef AYA_COMPARE_H
#define AYA_COMPARE_H

#include"common.h"

const int MAX_BUF = 1 << 20;
char __aya_buf1[MAX_BUF];
char __aya_buf2[MAX_BUF];
class Comparator{
	private:
		FILE *ayain, *ayaout, *ayaans;
		bool open(std::string outf, std::string ansf){
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
	public:
		bool compare_bits(std::string outf, std::string ansf){
			if(!open(outf, ansf)){
				//log here.
				return false;
			}
			bool stop1 = false; int p1;
			bool stop2 = false; int p2;
			while(!stop1 && ! stop2){
				p1 = fread(__aya_buf1, 1, MAX_BUF, ayaout);
				p2 = fread(__aya_buf2, 1, MAX_BUF, ayaans);
				if(strcmp(__aya_buf1, __aya_buf2)) return false;
				if(!p1) stop1 = true;
				if(!p2) stop2 = true;
			}
			//log here.
			return true;
		}
		bool compare_noip(std::string outf, std::string ansf){
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
						return false;
					}
					if(__aya_buf1[p1] != __aya_buf2[p2]){
						//log here.
						return false;
					}
					find1 = find2 = false;
				}
				if(find1 && stop2){
					//log here.
					return false;
				}
				if(find2 && stop1){
					//log here.
					return false;
				}
				if(!find1 && !stop1) ++ p1;
				if(!find2 && !stop2) ++ p2;
			}
			if(find1 || find2){
				//log here.
				return false;
			}
			//log here.
			return true;
		}
};

#endif