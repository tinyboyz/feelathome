#pragma once

#include <set>

using std::set;

#ifdef RECRUITEXPERT_EXPORTS
#define RECRUITEXPERTAPI __declspec(dllexport)
#else
#define RECRUITEXPERTAPI __declspec(dllimport)
#endif

typedef struct RECRUITEXPERTAPI __tagResumeItem
{
    __tagResumeItem(CString& strFileName, CString& strPathName)
        :m_strFileName(strFileName)
        ,m_strPathName(strPathName)
    {

    }

    CString m_strFileName;
    CString m_strPathName;

    bool operator<(const __tagResumeItem& resumeitem) const
    {
        return ((m_strFileName + m_strPathName) < (resumeitem.m_strFileName + resumeitem.m_strPathName));
    }

    bool operator==(const __tagResumeItem& resumeitem) const
    {
        return ((m_strFileName + m_strPathName) == (resumeitem.m_strFileName + resumeitem.m_strPathName));
    }

    bool operator!=(const __tagResumeItem& resumeitem) const
    {
        return !(*this == resumeitem);
    }
} ResumeItem;

class RECRUITEXPERTAPI CRecruitExpert
{
public:
    CRecruitExpert(void);
    virtual ~CRecruitExpert(void);

    void ImportResumes(CString strFolderPath);
    void AddSingleResume(CString strFileName, CString strFilePath);
    void ClearResumes();
    set<ResumeItem>& GetAllResumes();

protected:
    set<ResumeItem> m_setResumes;
};

