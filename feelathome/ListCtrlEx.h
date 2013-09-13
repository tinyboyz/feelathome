#pragma once
#include "afxcmn.h"
class CListCtrlEx : public CListCtrl
{
public:
    CListCtrlEx(void);
    virtual ~CListCtrlEx(void);

    void Resize(int cx, int cy);
    BOOL AddResumes(set<ResumeItem>& setResumes);

protected:
    CStringArray m_strArrayHeader;
    CStringList m_strListFileNames;
    DECLARE_MESSAGE_MAP()

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

