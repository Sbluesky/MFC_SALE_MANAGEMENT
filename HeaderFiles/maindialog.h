#pragma once

// maindialog dialog

class maindialog : public CDialogEx
{
	DECLARE_DYNAMIC(maindialog)

public:
	maindialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~maindialog();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGl();
protected:
	CButton btn_gl;
public:
	afx_msg void OnBnClickedBtnGm();
	afx_msg void OnBnClickedBtnGb();
};
