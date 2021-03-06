#pragma once
 
#include"common.hpp"

namespace Aya{

class Comparator{
private:
    FILE* ayain, * ayaout, * ayaans;
    bool del_tempfile = true;
    bool gen_in, gen_out, gen_ans;
    const std::string temp = "__aya_template_file";
public:

private:
    void pre_program(std::string std_program, std::string bf_program, std::string gen_program){
        std::string cmd;
        int exit_code; bool stop = false, ok = false;
        gen_in = gen_out = gen_ans = false;
        cmd = gen_program + " > " + temp + ".in";
        if (exit_code = system(cmd.c_str())){
            //log here.
            stop = true;
        } else gen_in = true;
        cmd = std_program + " < " + temp + ".in"
            + " > " + temp + ".out";
        if (exit_code = system(cmd.c_str())){
            //log here.
            stop = true;
        } else gen_out = true;
        cmd = bf_program + " < " + temp + ".in"
            + " > " + temp + ".ans";
        if (exit_code = system(cmd.c_str())){
            //log here.
            stop = true;
        } else gen_ans = true;
    }
    void suf_program(){
        std::string temp = "__aya_template_file", cmd;
        if (del_tempfile){
            if (gen_in ) cmd = "del " + temp + ".in" , system(cmd.c_str());
            if (gen_out) cmd = "del " + temp + ".out", system(cmd.c_str());
            if (gen_ans) cmd = "del " + temp + ".ans", system(cmd.c_str());
        }
    }
public:
    bool open(const std::string outf, const std::string ansf){
        ayaout = fopen(outf.c_str(), "r");
        ayaans = fopen(ansf.c_str(), "r");
        if (ayaout == NULL){
            //log here.
            return false;
        }
        if (ayaans == NULL){
            //log here.
            return false;
        }
        return true;
    }
    void close(const std::string outf, const std::string ansf){
        fclose(ayaout), fclose(ayaans);
    }
    bool compare_bits(const std::string outf, const std::string ansf){
        if (!open(outf, ansf)){
            //log here.
            return false;
        }
        bool stop1 = false; int p1;
        bool stop2 = false; int p2;
        while (!stop1 && !stop2){
            p1 = fread(Aya::__aya_buf1, 1, Aya::MAX_BUF, ayaout);
            p2 = fread(Aya::__aya_buf2, 1, Aya::MAX_BUF, ayaans);
            if (strcmp(Aya::__aya_buf1, Aya::__aya_buf2)){
                close(outf, ansf);
                return false;
            }
            if (!p1) stop1 = true;
            if (!p2) stop2 = true;
        }
        //log here.
        close(outf, ansf);
        return true;
    }
    bool compare_noip(const std::string outf, const std::string ansf){
        if (!open(outf, ansf)){
            //log here.
            return false;
        }
        bool stop1 = false; int p1 = 0, q1 = 0;
        bool stop2 = false; int p2 = 0, q2 = 0;
        int blank1 = 0, endline1 = 0;
        int blank2 = 0, endline2 = 0;
        bool find1 = false, find2 = false;
        while (!stop1 || !stop2){
            if (p1 == q1){
                p1 = 0;
                q1 = fread(Aya::__aya_buf1, 1, Aya::MAX_BUF, ayaout);
                if (p1 == q1) stop1 = true;
            }
            if (p2 == q2){
                p2 = 0;
                q2 = fread(Aya::__aya_buf2, 1, Aya::MAX_BUF, ayaans);
                if (p2 == q2) stop2 = true;
            }
            if (!stop1){
                if (isblank(Aya::__aya_buf1[p1])) blank1++; else
                    if (isspace(Aya::__aya_buf1[p1])){
                        endline1++, blank1 = 0;
                    } else find1 = true;
            }
            if (!stop2){
                if (isblank(Aya::__aya_buf2[p2])) blank2++; else
                    if (isspace(Aya::__aya_buf2[p2])){
                        endline2++, blank2 = 0;
                    } else find2 = true;
            }
            if (find1 && find2){
                if (endline1 != endline2 || blank1 != blank2){
                    //log here.
                    close(outf, ansf);
                    return false;
                }
                if (Aya::__aya_buf1[p1] != Aya::__aya_buf2[p2]){
                    //log here.
                    close(outf, ansf);
                    return false;
                }
                find1 = find2 = false;
            }
            if (find1 && stop2){
                //log here.
                close(outf, ansf);
                return false;
            }
            if (find2 && stop1){
                //log here.
                close(outf, ansf);
                return false;
            }
            if (!find1 && !stop1) ++p1;
            if (!find2 && !stop2) ++p2;
        }
        if (find1 || find2){
            //log here.
            close(outf, ansf);
            return false;
        }
        //log here.
        close(outf, ansf);
        return true;
    }
    bool compare_custom(const std::string outf, const std::string ansf);
    bool program(std::string std_program, std::string bf_program, std::string gen_program,
        bool(Comparator::* compare)(const std::string, const std::string) = compare_noip){
        pre_program(std_program, bf_program, gen_program);
        if ((this->*compare)(temp + ".out", temp + ".ans")){
            //log here.
            suf_program();
            return true;
        }
        return false;
    }
    bool program_n(int n, std::string std_program, std::string bf_program, std::string gen_program,
        bool(Comparator::* compare)(const std::string, const std::string) = compare_noip){
        //log here.
        bool del_tempfile0 = del_tempfile;
        del_tempfile = false;
        for(size_t TEST_CASE = 0; TEST_CASE < n; ++TEST_CASE){
            if (!program(std_program, bf_program, gen_program, compare))
                system("pause");
        }
        del_tempfile = del_tempfile0;
        if (!program(std_program, bf_program, gen_program, compare))
            system("pause");
        return true;
    }
    bool program(std::string std_program, std::string bf_program, std::string gen_program,
        bool(compare)(const std::string, const std::string)){
        pre_program(std_program, bf_program, gen_program);
        if ((compare)(temp + ".out", temp + ".ans")){
            //log here.
            suf_program();
            return true;
        }
        return false;
    }
    bool program_n(int n, std::string std_program, std::string bf_program, std::string gen_program,
        bool(*compare)(const std::string, const std::string)){
        //log here.
        bool del_tempfile0 = del_tempfile;
        del_tempfile = false;
        for(size_t TEST_CASE = 0; TEST_CASE < n; ++TEST_CASE){
            if (!program(std_program, bf_program, gen_program, compare))
                system("pause");
        }
        del_tempfile = del_tempfile0;
        if (!program(std_program, bf_program, gen_program, compare))
            system("pause");
        return true;
    }
};
} //namespace : Aya