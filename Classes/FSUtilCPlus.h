//
//  FSUtilCPlus.h
//  SharpMessage
//
//  Created by 冯璇 on 15/4/28.
//
//

#ifndef __SharpMessage__FSUtilCPlus__
#define __SharpMessage__FSUtilCPlus__

#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#endif

class FSUtilCPlus
{
public:
    static void dfsFolder(std::string folderPath,std::vector<std::string>& fileList,int depth = 0);
    
};
#endif /* defined(__SharpMessage__FSUtilCPlus__) */
