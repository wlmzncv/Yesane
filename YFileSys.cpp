#include "YFileSys.h"

namespace Yesane {
   YFileSys::YDataTag::YDataTag(size_t s){
        if(s>MAX_TAG_DATA_SIZE){
            //error
            this->size = MAX_TAG_DATA_SIZE;
        }else{
            this->size = s;
        }
   } 

   YFileSys::size_t YFileSys::YDataTag::addFileData(id_t f, tagData_t* d){
        if(files.size()<MAX_FILE_INCLUDE){
            files.push_back(f);
        }else{
            //error
            return -1;
        }
        this->data.push_back(new tagData_t[this->size]);
        if(d!=nullptr){
            //复制数据
            for(size_t j=0; j<this->size*64;++j){
                *(((byte*)this->data.back())+j)=*(((byte*)d)+j);
            }
        }
        return this->data.size()-1;
   }

   void YFileSys::YDataTag::uploadFileData(size_t s, tagData_t* d){
        //复制数据
        for(size_t j=0; j<this->size*64;++j){
            *(((byte*)this->data.at(s))+j)=*(((byte*)d)+j);
        }
   }

   void YFileSys::YDataTag::deleteFileData(id_t f, size_t s){
        vector<id_t>::iterator i = this->files.begin();
        while(i!=this->files.end()){
            if(*i==s){
                this->files.erase(i);
                break;
            }
        }
        delete[] this->data.at(s);
        this->data[s] = nullptr;
        vector<tagData_t*>::iterator j = this->data.begin();
        while(s!=0){
            --s;
            ++j;
        }
        this->data.erase(j);
   }
}