#pragma once


// GLdialog dialog

class GLdialog : public CDialogEx 
{
	DECLARE_DYNAMIC(GLdialog)

public:
	GLdialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~GLdialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLDIALOG };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CEdit edit_test;
public:
	CListCtrl listcontrol_gl;
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnUpdate();
	CString CheckItem();
	
	
protected:
	CEdit edit_goodname;
	CEdit edit_goodcost;
	CEdit edit_note;

private:
	int Number_Order =0;
	void addDatainListControl(CString str_name, CString str_cost, CString str_note);
};
