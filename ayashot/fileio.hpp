#pragma once

#include"common.hpp"

namespace Aya{

class fileio_t{
private:
    int32_t subtask, mode; FILE* file;
    std::vector<std::size_t> N, S, M, T;
    std::string P;
public:
    bool is_task   (){ return mode == 0; }
    bool is_subtask(){ return mode == 1; }
    bool is_stdio  (){ return mode == 2; }
private:
    void open(){
        if(is_subtask())
            file = fopen((P + std::to_string(SUBTASK) + "_"
                + std::to_string(NUMBER) + ".in").c_str(), "w");
        else
        if(is_task())
            file = fopen((P + std::to_string(NUMBER) + ".in").c_str(), "w");
    }
    void close(){ fclose(file); }
    char to_digit(int32_t n){
        return n <= 9?'0' + n:'A' + n - 10;
    }
    void write32(const uint32_t n, const int32_t b = 10){
        int32_t t = Aya::MAX_BUF; uint32_t m = n;
        do Aya::__aya_buf1[t--] = to_digit(m % b), m /= b; while (m);
        fwrite(Aya::__aya_buf1 + t + 1, 1, Aya::MAX_BUF - t, file);
    }
    void write64(const uint64_t n, const int32_t b = 10){
        int32_t t = Aya::MAX_BUF;  uint64_t m = n;
        do Aya::__aya_buf1[t--] = to_digit(m % b), m /= b; while (m);
        fwrite(Aya::__aya_buf1 + t + 1, 1, Aya::MAX_BUF - t, file);
    }
public:
    int32_t SUBTASK, NUMBER;
    void clear(){
        N.clear(), M.clear(), S.clear(), T.clear();
    }
    void regist_task(const int32_t cases, std::string _P = ""){
        //log here.
        subtask = 1, mode = 0, P = _P, clear();
        N.push_back(cases);
        SUBTASK = 0, NUMBER = 1, open();
    }
    void regist_subtask(const int32_t cases, std::string _P = ""){
        //log here.
        subtask = cases, mode = 1, P = _P, clear();
        N.reserve(subtask), S.reserve(subtask);
        M.reserve(subtask), T.reserve(subtask);
        for(int i = 0;i < subtask; ++i)
            N.push_back(1), S.push_back(100 / subtask), M.push_back(128000), T.push_back(1000);
        S[subtask - 1] = 100 - 100 / subtask * (subtask - 1);
        SUBTASK = 1, NUMBER = 1, open();
    }
    std::size_t calculate_KB(std::string t){
        std::size_t result = 0, type = 1, count = 0;
        for(auto &x:t){
            if(isupper(x)) x = x - 'A' + 'a';
            if(isdigit(x)) result = result * 10 + x -'0';
            if(x == 'k') type = 1;
            if(x == 'm') type = 1e3;
            if(x == 'g') type = 1e6;
            if(x == '.') ++count;
        }
        return 1ull * result * type / std::pow(10,count);
    }
    template <typename C, typename C::value_type = 0>
    void set_number(C V){
        int i = 0; for(auto &x:V){
            N[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    template <typename V, V = 0>
    void set_number(std::initializer_list<V> I){
        int i = 0; for(auto &x:I){
            N[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    template <typename C, typename C::value_type = 0>
    void set_memory(C V){
        int i = 0; for(auto &x:V){
            M[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    template <typename C,typename std::enable_if<
        std::is_same<typename C::value_type,std::string>::value,int>::type = 0
    >
    void set_memory(C V){
        int i = 0; for(auto &x:V){
            M[i++] = calculate_KB(x); if(i == subtask) break;
        }
    }
    template <typename V, V = 0>
    void set_memory(std::initializer_list<V> I){
        int i = 0; for(auto &x:I){
            M[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    void set_memory(std::initializer_list<std::string> I){
        int i = 0; for(auto &x:I){
            M[i++] = calculate_KB(x); if(i == subtask) break;
        }
    }
    template <typename C, typename C::value_type = 0>
    void set_score (C V){
        int i = 0; for(auto &x:V){
            S[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    template <typename V, V = 0>
    void set_score (std::initializer_list<V> I){
        int i = 0; for(auto &x:I){
            S[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    template <typename C, typename C::value_type = 0>
    void set_time  (C V){
        int i = 0; for(auto &x:V){
            T[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    template <typename V, V = 0>
    void set_time  (std::initializer_list<V> I){
        int i = 0; for(auto &x:I){
            T[i++] = static_cast<std::size_t>(x); if(i == subtask) break;
        }
    }
    void set_number(std::size_t n){
        for(int i = 0;i < subtask; ++i) N[i] = n;
    }
    void set_memory(std::size_t n){
        for(int i = 0;i < subtask; ++i) M[i] = n;
    }
    void set_score (std::size_t n){
        for(int i = 0;i < subtask; ++i) S[i] = n;
    }
    void set_time  (std::size_t n){
        for(int i = 0;i < subtask; ++i) T[i] = n;
    }
    void regist_stdio(){
        subtask = 0, mode = -1, file = stdout;
        SUBTASK = 1, NUMBER = 1;
    }
    bool next(){
        //log here.
        if (is_stdio()){
            //log here.
            return false;
        }
        close();
        if (NUMBER == N[SUBTASK - 1]){
            if (SUBTASK == subtask){
                //log here.
                return false;
            }
            ++SUBTASK, NUMBER = 1;
        } else ++NUMBER;
        open();
        return true;
    }
    void gen_config(const char *mode = "luogu"){
        if(is_stdio()){
            //log here.
            return;
        }
        if(!strcmp(mode, "luogu")){
            file = fopen("config.yml", "w");
            if(is_task())
                for(int i = 0;i < N[0]; ++i){
                    fprintf(file, "%d.in:\n",i + 1);
                    fprintf(file, "  timeLimit: %d\n", T[0]);
                    fprintf(file, "  memoryLimit: %d\n", M[0]);
                    fprintf(file, "  score: %d\n", S[0]);
                    fprintf(file, "  subtaskId: %d\n", 0);
                    fputc('\n', file);
            } else
            for(int i = 0;i < subtask; ++i){
                for(int j = 0;j < N[i]; ++j){
                    fprintf(file, "%d_%d.in:\n",i + 1, j + 1);
                    fprintf(file, "  timeLimit: %d\n", T[i]);
                    fprintf(file, "  memoryLimit: %d\n", M[i]);
                    fprintf(file, "  score: %d\n", S[i]);
                    fprintf(file, "  subtaskId: %d\n", i);
                    fputc('\n', file);
                }
            }
        } else {
            //log here.
        }
        
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
    void write(const std::string n){ write(n.c_str()); }

    template <typename T>
    void write(const T n);
    template <typename T>
    void writeln(const T& n){ write(n), write('\n'); }
};
    
} //namespace : Aya