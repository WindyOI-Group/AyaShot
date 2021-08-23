#pragma once

#include"common.h"

class fileio_t{
private:
    int32_t subtask; FILE* file;
    __aya_vec N, S;
    __aya_str P;
    void open(){
        if (subtask == 1)
            file = fopen((P + std::to_string(SUBTASK) + "_"
                + std::to_string(NUMBER) + ".in").c_str(), "w");
        else
            file = fopen((P + std::to_string(NUMBER) + ".in").c_str(), "w");
    }
    void close(){ fclose(file); }
    char to_digit(int32_t n){
        return n <= 9?'0' + n:'A' + n - 10;
    }
    void write32(const uint32_t n, const int32_t b = 10){
        int32_t t = MAX_BUF; uint32_t m = n;
        do __aya_buf1[t--] = to_digit(m % b), m /= b; while (m);
        fwrite(__aya_buf1 + t + 1, 1, MAX_BUF - t, file);
    }
    void write64(const uint64_t n, const int32_t b = 10){
        int32_t t = MAX_BUF;  uint64_t m = n;
        do __aya_buf1[t--] = to_digit(m % b), m /= b; while (m);
        fwrite(__aya_buf1 + t + 1, 1, MAX_BUF - t, file);
    }
public:
    int32_t SUBTASK, NUMBER;
    bool is_subtask(){ return  subtask == 1; }
    bool is_task(){ return !subtask == 0; }
    bool is_stdio(){ return !subtask == -1; }

    void regist_task(const int32_t cases, __aya_str _P = ""){
        //log here.
        subtask = 0, P = _P;
        N.clear(), N.push_back(cases);
        SUBTASK = 0, NUMBER = 1, open();
    }
    void regist_subtask(const int32_t cases, __aya_vec _N, __aya_vec _S, __aya_str _P = ""){
        //log here.
        subtask = 1, P = _P, N = _N, S = _S;
        SUBTASK = 0, NUMBER = 1, open();
    }
    void regist_stdio(){
        subtask = -1, file = stdout;
        N.clear(), N.push_back(1);
        SUBTASK = 0, NUMBER = 1;
    }
    bool next(){
        //log here.
        if (subtask == -1){
            //log here.
            return false;
        }
        close();
        if (NUMBER == N[SUBTASK]){
            if (SUBTASK == N.size() - 1){
                //log here.
                return false;
            }
            ++SUBTASK, NUMBER = 1;
        } else ++NUMBER;
        open();
        return true;
    }
    void write(const char  n){ fputc(n, file); }
    void write(const char* n){ fwrite(n, 1, strlen(n), file); }
    void write(const bool  n){ fprintf(file, "%d", n); }
    void write(const int32_t n, int32_t b = 10){
        uint32_t m;
        if (n < 0) write('-'), m = -n; else m = n;
        write32(m, b);
    }
    void write(const uint32_t n, const int32_t b = 10){ write32(n, b); }
    void write(const int64_t  n, const int32_t b = 10){
        uint64_t m;
        if (n < 0) write('-'), m = -n; else m = n;
        write64(m, b);
    }
    void writed(const float_t  n, const int32_t f = 6){
        fprintf(file, ("%." + std::to_string(f) + "f").c_str(), n);
    }
    void writed(const double_t n, const int32_t f = 6){
        fprintf(file, ("%." + std::to_string(f) + "lf").c_str(), n);
    }
    void write(const uint64_t n, const int32_t b = 10){ write64(n, b); }
    void writef(const char* format, ...){
        va_list va; va_start(va, format); vfprintf(file, format, va); va_end(va);
    }
    void write(const __aya_str n){ write(n.c_str()); }

    template <typename T>
    void write(const T n);
    template <typename T>
    void writeln(const T& n){ write(n), write('\n'); }
}; 