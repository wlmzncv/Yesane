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
    using size_t = std::uint32_t;
    static const size_t TAG_LENGTH = 32; //文字标签的占用字节数
    static const size_t MAX_TAG_NUM = 16; //单个文件所能拥有的纯文本标签数量
    static const size_t MAX_DATATAG_NUM = 8; //单个文件所能拥有的带数据标签数量
    static const size_t MAX_TAG_INCLUDE = 64; //单个标签包含的子标签数量 即一个文件夹中所拥有的子文件夹数
    static const size_t MAX_FILE_INCLUDE = 512; //单个标签包含的文件数量 即一个文件夹中所拥有的文件数
    static const size_t MAX_TAG_DATA_SIZE = 16; //数据标签能用的最大字节数据
    /*
    文件类
    */
    class YFile{
    public:
        YFile();
        ~YFile();
    private:
        id_t id; //文件唯一id
        vector<id_t> tags; //文件所拥有的纯文本标签 受MAX_TAG_NUM限制
        vector<id_t> dataTags; //文件所拥有的带数据标签 受MAX_DATATAG_NUM限制
        vector<size_t> dataIndex; //与dataTags维持同样大小 新增数据标签时 保存文件对应的标签数据在YDataTag对象内data成员中的索引值
    };

    /*
    纯文字标签
    */
    class YTag{
    public:
        YTag();
        ~YTag();
    private:
        id_t id; //唯一id
        vector<id_t> tags; //包含的子标签 受MAX_TAG_INCLUDE限制
        vector<id_t> files; //包含的文件 受MAX_FILE_INCLUDE限制
        byte tag[TAG_LENGTH]; //标签名 使用utf-8编码
    };

    /*
    带数据标签
    */
    class YDataTag{
    public:
        YDataTag(size_t s);
        ~YDataTag();
        //为一个文件添加标签数据
        size_t addFileData(id_t f, tagData_t* d);
        //更新标签数据
        void uploadFileData(size_t s, tagData_t* d);
        //删除标签数据 危险操作
        void deleteFileData(id_t f, size_t s);
    private:
        id_t id; //唯一id
        vector<id_t> files; //包含的文件 受MAX_FILE_INCLUDE限制
        vector<tagData_t*> data; //存储的数据 vector长度与files一致
        size_t size; //数据所占大小 以tagData_t为单位
        byte tag[TAG_LENGTH]; //标签名 使用utf-8编码
    };

public:
    YFileSys();
    ~YFileSys();
private:
    const unsigned long long begin_time; //时间戳 单位秒 文件系统建立时间
    
    
};

#endif