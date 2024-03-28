#pragma once
#ifndef YFILESYS_H
#define YFILESYS_H

#include "Base.h"
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

using std::vector;
using std::string;

/*
文件系统类
也作为创建一个文件的工厂
一个文件可以有多个标签
标签间可形成树状组织关系
文件夹用标签代替
有些标签带有值（如文件大小，日期，整数值），可用于给文件排序
*/
class Yesane::YFileSys {
public:
    using byte = unsigned char; //字节数组的元素类型
    using id_t = unsigned long long; //标签id以及文件id的类型
    using tagData_t = byte[64]; //数据标签的数据所占大小以tagData_t为单位递增
    using size_t = std::uint32_t; //除文件大小以外的计数
    using size_f = std::uint64_t; //表示文件所占字节数量
    static const size_t TAG_LENGTH = 32; //文字标签的占用字节数
    static const size_t MAX_TAG_NUM = 16; //单个文件所能拥有的纯文本标签数量
    static const size_t MAX_DATATAG_NUM = 8; //单个文件所能拥有的带数据标签数量
    static const size_t MAX_TAG_INCLUDE = 64; //单个标签包含的子标签数量 即一个文件夹中所拥有的子文件夹数
    static const size_t MAX_FILE_INCLUDE = 512; //单个标签包含的文件数量 即一个文件夹中所拥有的文件数
    static const size_t TOTAL_FILE_NUM = 102400; //文件系统中存在的文件总数量最大值 每个数据标签包含的文件数受此限制
    static const size_t MAX_TAG_DATA_SIZE = 16; //数据标签能用的最大字节数据 此处16*64为1KB
    //TOTAL_FILE_NUM*MAX_DATATAG_NUM为数据标签总数，单个若为1KB，则总占用空间为800MB
    class YFile;
    class YTag;
    class YDataTag;
    /*
    文件类
    */
    class YFile{
    public:
        YFile()=delete;
        YFile(id_t t):id(t){}
        ~YFile(){}
        void clearAllTags(vector<YTag>& gs,vector<YDataTag>& ds);
    private:
        id_t id; //文件唯一id
        vector<id_t> tags; //文件所拥有的纯文本标签 受MAX_TAG_NUM限制
        vector<id_t> dataTags; //文件所拥有的带数据标签 受MAX_DATATAG_NUM限制
        vector<size_t> dataIndex; //与dataTags维持同样大小 新增数据标签时 保存文件对应的标签数据在YDataTag对象内data成员中的索引值
        void clearTags(vector<YTag>& gs);
        void clearDataTags(vector<YDataTag>& ds);
    };

    /*
    纯文字标签
    */
    class YTag{
    public:
        YTag()=delete;
        YTag(id_t t, byte* b=nullptr);
        ~YTag(){}
        //设置标签名
        void setTagName(byte* b);
        //添加文件 返回该文件在files中的下标
        size_t addFile(id_t f);
        //添加子标签 返回该标签在tags中的下标
        size_t addChildTag(id_t t);
        //删除文件
        void deleteFile(id_t f);
        //删除子标签
        void deleteChildTag(id_t t);
        //检查是否含有某文件
        bool hasFile(id_t f) const;
        //检查是否含有某标签
        bool hasChildTag(id_t t) const;
    private:
        id_t id; //唯一id
        vector<id_t> tags; //包含的子标签 受MAX_TAG_INCLUDE限制
        vector<id_t> files; //包含的文件 受MAX_FILE_INCLUDE限制
        byte tag[TAG_LENGTH]{0}; //标签名 使用utf-8编码
    };

    /*
    带数据标签
    */
    class YDataTag{
    public:
        YDataTag(size_t s, id_t t, byte*b=nullptr);
        ~YDataTag(){}
        //为一个文件添加标签数据
        size_t addFileData(id_t f, tagData_t* d);
        //更新标签数据
        void uploadFileData(size_t s, tagData_t* d);
        //删除标签数据 危险操作
        void deleteFileData(size_t s);
        //设置标签名
        void setTagName(byte* b);
        //检查是否含有某文件
        bool hasFile(id_t f);
    private:
        id_t id; //唯一id
        vector<id_t> files; //包含的文件 受TOTAL_FILE_NUM限制
        vector<tagData_t*> data; //存储的数据 vector长度与files一致 下标位置也与files共通
        size_t size; //数据所占大小 以tagData_t为单位
        byte tag[TAG_LENGTH]{0}; //标签名 使用utf-8编码
    };
private:
    id_t max_file_id=0; //系统内文件id最大值 第1个文件的id为1
    id_t max_tag_id=0; //系统内文本标签id最大值 第1个标签的id为1
    id_t max_datatag_id=0; //系统内数据标签id最大值 第1个标签的id为1
    size_t min_file_size=1024*512; //文件块 也即每个文件所用空间的递增单元大小 单位字节
    size_t expand=3; //
    vector<size_f> fileArrayHard={0}; //存储所有文件在硬盘上的结束位置 假设硬盘空间像内存那样是连续递增的
    vector<byte> valid_list={0}; //记录所有文件id的失效情况 若不为0则说明该id的文件已被删除
    id_t min_deleted=max_file_id+1; //最靠前的被删除文件id
    vector<YFile> files; //注意 第1个文件的索引是0
    vector<YTag> tags; //注意 第1个标签的索引是0
    vector<YDataTag> dataTags; //注意 第1个标签的索引是0
public:
    id_t createFile(size_t n=1); //创建新文件 n表示文件块数量
    void deleteFile(id_t f); //删除文件
    id_t createTag(); //创建新标签
    id_t createDataTag(size_t s); //创建新数据标签
    bool checkState(); //检查文件系统是否有错误
    YFile& getYFile(id_t d){return files.at(d);}
    YTag& getYTag(id_t d){return tags.at(d);}
    YDataTag& getYDataTag(id_t d){return dataTags.at(d);}

public:
    YFileSys(){}
    ~YFileSys(){}
    void set_min_file_size(size_t s){min_file_size=s;}
    void set_expand(size_t t){expand=t;}
    size_t get_min_file_size()const{return min_file_size;}
    size_t get_expand()const{return expand;}
private:
    unsigned long long begin_time; //时间戳 单位秒 文件系统建立时间
    
    
};

#endif