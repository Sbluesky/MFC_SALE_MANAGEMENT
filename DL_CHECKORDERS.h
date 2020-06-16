#pragma once


// DL_CHECKORDERS dialog

class DL_CHECKORDERS : public CDialogEx
{
	DECLARE_DYNAMIC(DL_CHECKORDERS)

public:
	DL_CHECKORDERS(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DL_CHECKORDERS();
	BOOL OnInitDialog();

	CString m_scheckid;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHECKORDERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CListCtrl edltlistctrl_checkorders;
private:
	CEdit edit_cid;
	CEdit edit_time;
	CEdit edit_billid;
	CEdit edit_cost;
};
