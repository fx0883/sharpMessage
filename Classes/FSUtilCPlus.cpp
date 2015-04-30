//
//  FSUtilCPlus.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/4/28.
//
//

#include "FSUtilCPlus.h"
using namespace std;

void FSUtilCPlus::dfsFolder(std::string folderPath,std::vector<std::string>& fileList,int depth)
{

    
#ifdef WIN32
        _finddata_t FileInfo;
        string strfind = folderPath + "\\*";
        long Handle = _findfirst(strfind.c_str(), &FileInfo);
        
        if (Handle == -1L)
        {
            cerr << "can not match the folder path" << endl;
            exit(-1);
        }
        do{
            //判断是否有子目录
            if (FileInfo.attrib & _A_SUBDIR)
            {
                //这个语句很重要
                if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))
                {
                    string newPath = folderPath + "\\" + FileInfo.name;
                    dfsFolder(newPath);
                }
            }
            else
            {
                string filename = (folderPath + "\\" + FileInfo.name);
                fileList.push_back(filename);
                cout << folderPath << "\\" << FileInfo.name  << " " << endl;
            }
        }while (_findnext(Handle, &FileInfo) == 0);
        
        _findclose(Handle);
#else
        DIR *dp;
        struct dirent *entry;
        struct stat statbuf;
        if((dp = opendir(folderPath.c_str())) == NULL) {
            fprintf(stderr,"cannot open directory: %s\n", folderPath.c_str());
            return;
        }
        chdir(folderPath.c_str());
        while((entry = readdir(dp)) != NULL) {
            lstat(entry->d_name,&statbuf);
            if(S_ISDIR(statbuf.st_mode)) {
                
                if(strcmp(".",entry->d_name) == 0 ||
                   strcmp("..",entry->d_name) == 0)
                    continue;
                printf("%*s%s/\n",depth,"",entry->d_name);
                dfsFolder(entry->d_name,fileList,depth+4);
            } else {
                string filename = entry->d_name;
                fileList.push_back(filename);
                printf("%*s%s\n",depth,"",entry->d_name);
            }
        }
        chdir("..");
        closedir(dp);
#endif
    }