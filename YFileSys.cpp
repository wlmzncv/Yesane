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
        if(this->files.size()<TOTAL_FILE_NUM){
            this->files.push_back(f);
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
   void YFileSys::YDataTag::deleteFileData(size_t s){
        delete[] this->data.at(s);
        this->data[s] = nullptr;
        vector<id_t>::iterator i = this->files.begin();
        vector<tagData_t*>::iterator j = this->data.begin();
        while(s!=0){
            --s;
            ++j;
            ++i;
        }
        this->data.erase(j);
        this->files.erase(i);
   }
   void YFileSys::YDataTag::setTagName(byte* b){
        for(int i=0; i<TAG_LENGTH; ++i){
            this->tag[i] = b[i];
        }
   }
   void YFileSys::YTag::setTagName(byte* b){
        for(int i=0; i<TAG_LENGTH; ++i){
            this->tag[i] = b[i];
        }
   }
   YFileSys::size_t YFileSys::YTag::addFile(id_t f){
        if(this->files.size()<MAX_FILE_INCLUDE){
            this->files.push_back(f);
            return this->files.size()-1;
        }else{
            //error
            return -1;
        }
   }
   YFileSys::size_t YFileSys::YTag::addChildTag(id_t t){
        if(this->tags.size()<MAX_TAG_INCLUDE){
            this->tags.push_back(t);
            return this->tags.size()-1;
        }else{
            //error
            return -1;
        }
   }
   void YFileSys::YTag::deleteFile(id_t f){
        vector<id_t>::iterator i = this->files.begin();
        while(i!=this->files.end()){
            if(*i == f){
                this->files.erase(i);
                break;
            }
            ++i;
        }
   }
   void YFileSys::YTag::deleteChildTag(id_t t){
        vector<id_t>::iterator i = this->tags.begin();
        while(i!=this->tags.end()){
            if(*i == t){
                this->tags.erase(i);
                break;
            }
            ++i;
        }
   }
   bool YFileSys::YTag::hasFile(id_t f){
        vector<id_t>::iterator i = this->files.begin();
        while(i!=this->files.end()){
            if(*i == f){
                return true;
            }
            ++i;
        }
        return false;
   }
   bool YFileSys::YTag::hasChildTag(id_t t){
        vector<id_t>::iterator i = this->tags.begin();
        while(i!=this->tags.end()){
            if(*i == t){
                return true;
            }
            ++i;
        }
        return false;
   }
   bool YFileSys::YDataTag::hasFile(id_t f){
        vector<id_t>::iterator i = this->files.begin();
        while(i!=this->files.end()){
            if(*i == f){
                return true;
            }
            ++i;
        }
        return false;
   }
}