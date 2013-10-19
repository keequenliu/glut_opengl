//#include "Utility.h"

//using namespace Utility;

//template<typename T>
//std::string ToString(T value)
//{
//    std::stringstream ss;
//    ss<<value;
//    return ss.str();
//}

//template<typename T>
//T FromString(std::string str)
//{
//    T value;
//    std::stringstream ss(str);
//    ss>>value;
//    return value;
//}

//std::vector<std::string> StringSplit(std::string str,char c)
//{
//    std::vector<std::string> list;
//    int prePos=0;
//    int currentPos=0;
//    while(currentPos<str.size())
//    {
//        if(currentPos==0)
//            currentPos= str.find(c,currentPos);
//        else
//            currentPos= str.find(c,currentPos+1);
//        list.push_back(str.substr(prePos,currentPos-prePos));
//        prePos=currentPos+1;
//    }

//    return list;
//}

//template<typename T>
//std::string ToHexString(const T value,bool upper_case=true)
//{
//    std::stringstream ss;
//    ss<<std::hex<< std::setw(2) << std::setfill('0')
//     <<(upper_case? std::uppercase: std::nouppercase);
//    ss<<value;
//    return ss.str();
//}

////把字符串转化为Asic码对应的数字，然后再转为十六进制
//std::string StringToHex(const std::string& in)
//{
//    std::stringstream ss;

//    ss << std::hex << std::setw(2) << std::setfill('0');
//    //一个个字符换成十六进制
//    for (size_t i = 0; in.length() > i; ++i)
//    {
//        ss << (int)(in[i]);
//        std::cout<<(int)in[i]<<std::endl;
//    }

//    return ss.str();
//}
