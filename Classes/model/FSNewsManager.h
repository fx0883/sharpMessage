//
//  FSNewsManager.h
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#ifndef __SharpMessage__FSNewsManager__
#define __SharpMessage__FSNewsManager__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "AppMacros.h"
#include "ChapterInfo.h"
#include "NewsInfo.h"
#include "BookMarkInfo.h"

//class sqlite3;
class SqliteCursor
{
    int m_nPos;
    std::list<std::vector<std::string>*> m_listvecData;
    std::vector<std::vector<std::string>*> m_vecvecData;
    std::vector<std::string> m_vecTitle;
public:
    SqliteCursor()
    {
        m_nPos = 0;
    }
    ~SqliteCursor()
    {
        for ( std::list<std::vector<std::string>*>::iterator it = m_listvecData.begin() ; it != m_listvecData.end() ; it ++ )
            delete (*it);
    }
    void AddRowData( int n_column, char ** column_value, char ** column_name )
    {
        if ( m_listvecData.size() == 0 )
        {
            m_vecTitle.resize( n_column );
            for ( int i = 0 ; i < n_column ; i ++ ) m_vecTitle[i] = column_name[i];
        }
        std::vector<std::string>* vec = new std::vector<std::string>();
        vec->resize( n_column );
        for ( int i = 0 ; i < n_column ; i ++ ) if ( column_value[i] != NULL ) (*vec)[i] = column_value[i];
        m_listvecData.push_back( vec );
    }
    void MakeData()
    {
        if ( m_vecvecData.size() != m_listvecData.size() )
        {
            m_vecvecData.resize( m_listvecData.size() );
            int i = 0;
            for ( std::list<std::vector<std::string>*>::iterator it = m_listvecData.begin() ; it != m_listvecData.end() ; it ++ , i ++ )
                m_vecvecData[i] = (*it);
        }
    }
    int GetRowCount()
    {
        return (int)m_listvecData.size();
    }
    int GetColumnCount()
    {
        return (int)m_vecTitle.size();
    }
    std::vector<std::string> &GetCurRow()
    {
        return (*m_vecvecData[m_nPos]);
    }
    const char* GetData( int column )
    {
        MakeData();
        std::vector<std::string> &row = GetCurRow();
        if ( column < 0 || column >= (int)row.size() ) return "";
        return row[column].c_str();
    }
    const char* GetColumData( int column )
    {
        if ( column < 0 || column >= (int)m_vecTitle.size() ) return "";
        return m_vecTitle[column].c_str();
    }
    int GetPos()
    {
        return m_nPos;
    }
    bool SetPos( int pos )
    {
        if ( GetRowCount() == 0 ) return false;
        MakeData();
        if ( pos < 0 ) pos = 0;
        else if ( pos > GetRowCount() - 1 ) pos = GetRowCount() - 1;
        m_nPos = pos;
        return true;
    }
};


class FSNewsManager:public CAObject
{
public:
    CREATE_FUNC(FSNewsManager)
public:
    bool init();
    ~FSNewsManager();
public:
    CC_SYNTHESIZE_PASS_BY_REF2(CCArray, aryNewsListOrderbyReadTimes, AryNewsListOrderbyReadTimes);
    CC_SYNTHESIZE_PASS_BY_REF2(CCArray, arynewsList, ArynewsList);
    CC_SYNTHESIZE_PASS_BY_REF2(ChapterInfo*, curChapterInfo, CurChapterInfo);
    CC_SYNTHESIZE_PASS_BY_REF2(CCDictionary, dicChapterInfo, DicChapterInfo);
    CC_SYNTHESIZE_PASS_BY_REF2(CCDictionary, dicBookMarkInfo, DicBookMarkInfo);
public:
    bool removeBookMarkForNewsId(int newsID);
    int getCurChapterID(int newsID);
    void setCurChapterID(int newsID,int chapterID);
    CCArray* getChapterInfoAry(int newsID);
    float getPageProgress(int chapterID);
    void setPageProgress(int chapterID,string progress);
    void updateNewsReadTimes();
    bool updateNewsInfo(NewsInfo *newsinfo);
    
public:
    static bool greaterNews( NewsInfo*  const s1, NewsInfo* const  s2);
public:
    void loadNewsList();
    CCArray* loadNewsListOrderbyReadTimes();
    CCArray* loadNewsListOrderbyReadTimes2();
    void loadCurChapterInfo(int newsID,int chapterNubmer);
    void loadCurChapterInfo(int newsID);
    void loadChapterDic(int newsID);
    
    CCArray* loadBookMarkInfo(int newsID);
    bool addBookMarkInfo(BookMarkInfo*& bookmarkinfo);
    bool insertbookmarkToDB(BookMarkInfo*& bookmarkinfo);
    
    bool deleteBookmarkInDB(int newsID);
    
    ChapterInfo* getChapterInfoOrientation(ChapterInfo* chapterinfo,bool bIsNext);
    ChapterInfo* getNextChapterInfo(ChapterInfo* chapterinfo);
    ChapterInfo* getPreChapterInfo(ChapterInfo* chapterinfo);
public:
    NewsInfo* getNewsInfoByNewsId(int newsId);
    

    
protected:
    sqlite3 *_sqlite3;
    SqliteCursor* SqliteQurey( sqlite3 *pSql , std::string sql );
    static int QueryResult( void * para, int n_column, char ** column_value, char ** column_name )
    {
        ((SqliteCursor*)para)->AddRowData(n_column , column_value , column_name );
        return 0;
    }
};

#endif /* defined(__SharpMessage__FSNewsManager__) */
