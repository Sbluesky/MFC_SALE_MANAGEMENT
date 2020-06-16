#pragma once


// DL_ADD_ORDERS dialog

class DL_ADD_ORDERS : public CDialogEx
{
	DECLARE_DYNAMIC(DL_ADD_ORDERS)

public:
	DL_ADD_ORDERS(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DL_ADD_ORDERS();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DL_ADDORDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CEdit edit_costomerid;
	CEdit edit_billid;
	CDateTimeCtrl ctrl_datepicker;
	CEdit edit_goodname;
	CEdit edit_amount;
	CEdit edit_cost;
	CListCtrl listcontrol_orders;
public:
	afx_msg void OnBnClickedBtnAddorders();
	CButton BTN_ADDORDERS;
};
