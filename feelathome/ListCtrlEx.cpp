#include "stdafx.h"
#include "ListCtrlEx.h"


CListCtrlEx::CListCtrlEx(void)
{
    m_strArrayHeader.Add(_T("文件名"));
    m_strArrayHeader.Add(_T("路径"));
}


CListCtrlEx::~CListCtrlEx(void)
{
}

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
    //{{AFX_MSG_MAP(CListCtrlEx)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListCtrlEx::Resize(int cx, int cy)
{
    CRect Rect(0, 0, cx, cy);
    MoveWindow(&Rect);
    InvalidateRect(Rect);
    SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

int CListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CListCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    SetExtendedStyle (LVS_EX_GRIDLINES);
    for (int i=0;i<m_strArrayHeader.GetSize();++i)
    {
        InsertColumn(i+1, m_strArrayHeader.GetAt(i), LVCFMT_CENTER, 100);
    }
    return 0;
}

BOOL CListCtrlEx::UpdateResumes(set<ResumeItem>& setResumes)
{
    int nRow = 0;
    int nIndex = 0;
    set<ResumeItem>::iterator iter;
    LVFINDINFO info;
    info.flags = LVFI_STRING;

    for (iter=setResumes.begin();iter != setResumes.end();++iter)
    {
        info.psz = iter->m_strFileName;
        if ((nIndex = FindItem(&info)) != -1)
        {
            SetItemText(nIndex, 0, iter->m_strFileName);
            SetItemText(nIndex, 1, iter->m_strPathName);
        } 
        else
        {
            nRow = InsertItem(0, _T(""));
            SetItemText(nRow, 0, iter->m_strFileName);
            SetItemText(nRow, 1, iter->m_strPathName);
        }
    }
    SetRedraw(TRUE);
    Invalidate();
    UpdateWindow();
    return TRUE;
}