#ifndef AYA_FILEIO_H
#define AYA_FILEIO_H

#include"common.h"

class fileio_t{
private:
    int subtask; FILE *file;
    __aya_vec N, S;
    __aya_str P;
    void open(){
        if(subtask == 1)
            file = fopen((P + std::to_string(SUBTASK) + "_"
                + std::to_string(NUMBER) + ".in").c_str(), "w");
        else
            file = fopen((P + std::to_string(NUMBER) + ".in").c_str(), "w");
    }
    void close(){fclose(file);}
    char to_digit(int n){
        return n<=9?'0'+n:'A'+n-10;
    }
    void write32(const __aya_u32 n, const int b = 10){
        int t=MAX_BUF; __aya_u32 m = n;
        do __aya_buf1[t--] = to_digit(m % b), m /= b; while(m);
        fwrite(__aya_buf1 + t + 1, 1, MAX_BUF - t, file);
    }
    void write64(const __aya_u64 n, const int b = 10){
        int t=MAX_BUF;  __aya_u64 m = n;
        do __aya_buf1[t--] = to_digit(m % b), m /= b; while(m);
        fwrite(__aya_buf1 + t + 1, 1, MAX_BUF - t, file);
    }
public:
    int SUBTASK, NUMBER;
    bool is_subtask(){return  subtask ==  1;}
    bool is_task   (){return !subtask ==  0;}
    bool is_stdio  (){return !subtask == -1;}
    
    void regist_task(const int cases, __aya_str _P = ""){
        //log here.
        subtask = 0, P = _P;
        N.clear(), N.push_back(cases);
        SUBTASK = 0, NUMBER = 1, open();
    }
    void regist_subtask(const int cases, __aya_vec _N,__aya_vec _S,__aya_str _P = ""){
        //log here.
        subtask = 1, P = _P ,N = _N, S = _S;
        SUBTASK = 0, NUMBER = 1, open();
    }
    void regist_stdio(){
        subtask = -1, file = stdout;
        N.clear(), N.push_back(1);
        SUBTASK = 0, NUMBER = 1;
    }
    bool next(){
        //log here.
        if(subtask == -1){
            //log here.
            return false;
        }
        close();
        if(NUMBER == N[SUBTASK]){
            if(SUBTASK == N.size() - 1){
                //log here.
                return false;
            }
            ++SUBTASK, NUMBER = 1;
        } else ++NUMBER;
        open();
        return true;
    }
    void write(const char  n){fputc(n, file);}
    void write(const char *n){fwrite(n, 1, strlen(n), file);}
    void write(const bool  n){fprintf(file, "%d", n);}
    void write(const __aya_i32 n, int b = 10){
        __aya_u32 m;
        if(n < 0) write('-'), m = - n; else m = n;
        write32(m, b);
    }
    void write(const __aya_u32 n, const int b = 10){write32(n, b);}
    void write(const __aya_i64 n, const int b = 10){
        __aya_u64 m;
        if(n < 0) write('-'), m = - n; else m = n;
        write64(m, b);
    }
    void writed(const __aya_f32 n, const int f = 6){
        fprintf(file, ("%." + std::to_string(f) + "f").c_str(), n);
    }
    void writed(const __aya_f64 n, const int f = 6){
        fprintf(file, ("%." + std::to_string(f) + "lf").c_str(), n);
    }
    void write(const __aya_u64 n, const int b = 10){write64(n, b);}
    void writef(const char *format, ...){
        va_list va; va_start(va, format); vfprintf(file, format, va); va_end(va);
    }
    void write(const __aya_str n){write(n.c_str());}

    template <typename T>
    void write(const T n);
    template <typename T>
    void writeln(const T &n){write(n), write('\n');}
};

#endif