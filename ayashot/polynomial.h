#ifndef AYA_POLY_H
#define AYA_POLY_H

#include"common.h"
#include"random.h"

template <typename T>
class Poly{
    private:
        std::size_t length;
        vector <T> V;
    public:
        std::size_t size(){return length;}
        void clear(){length = 0 , V.clear();}

        void sequence(int n,int left,int right){
            
        }

        void distribute(int n,vector <int> weight){
            
        }

};

#endif