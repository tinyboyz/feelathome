#include "stdafx.h"
#include "RecruitExpert.h"

CRecruitExpert::CRecruitExpert(void)
{
}


CRecruitExpert::~CRecruitExpert(void)
{
}

void CRecruitExpert::ImportResumes(CString strFolderPath)
{
    CFileFind finder;
    BOOL bworking = finder.FindFile(strFolderPath + _T("\\*.doc"));   //查询该文件夹下的所有图片
    while (bworking)
    {
        bworking = finder.FindNextFile();
        m_setResumes.insert(ResumeItem(finder.GetFileName(), strFolderPath));
    }
    AfxMessageBox(_T("Import resume done!"));
}

void CRecruitExpert::AddSingleResume(CString strFileName, CString strFolderPath)
{
    m_setResumes.insert(ResumeItem(strFileName, strFolderPath));
}

set<ResumeItem>& CRecruitExpert::GetAllResumes()
{
    return m_setResumes;
}

void CRecruitExpert::ClearResumes()
{
    m_setResumes.clear();
}
