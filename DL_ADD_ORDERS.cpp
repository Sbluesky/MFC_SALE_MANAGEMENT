// DL_ADD_ORDERS.cpp : implementation file
//

#include "pch.h"
#include "MFCGoodsManagement.h"
#include "DL_ADD_ORDERS.h"
#include "afxdialogex.h"
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

#import "C:\\Program files\\Common Files\\System\\Ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

// DL_ADD_ORDERS dialog

IMPLEMENT_DYNAMIC(DL_ADD_ORDERS, CDialogEx)

DL_ADD_ORDERS::DL_ADD_ORDERS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DL_ADDORDER, pParent)
{

}

DL_ADD_ORDERS::~DL_ADD_ORDERS()
{
}

void DL_ADD_ORDERS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_CUSTOMERID, edit_costomerid);
	DDX_Control(pDX, IDC_EDT_BILLID, edit_billid);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, ctrl_datepicker);
	DDX_Control(pDX, IDC_EDT_GOODSNAME, edit_goodname);
	DDX_Control(pDX, IDC_EDT_AMOUNT, edit_amount);
	DDX_Control(pDX, IDC_EDT_GOODSCOST, edit_cost);
	DDX_Control(pDX, IDC_BTN_ADDORDERS, BTN_ADDORDERS);
}


BEGIN_MESSAGE_MAP(DL_ADD_ORDERS, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADDORDERS, &DL_ADD_ORDERS::OnBnClickedBtnAddorders)
END_MESSAGE_MAP()


// DL_ADD_ORDERS message handlers


void DL_ADD_ORDERS::OnBnClickedBtnAddorders()
{
	_bstr_t strName;
	_ConnectionPtr pConn = NULL;
	_bstr_t strCon("testDNS");
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	//create the connection pointer
	hr = pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
	{
		MessageBox(_T("Error instantiating Connection objectn"));
	}
	//open the sql server connection
	hr = pConn->Open(strCon, "", "", 0);
	if (FAILED(hr))
	{
		MessageBox(_T("Error to open database using ADO"));

	}
	hr = Cmd1.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
	{
		MessageBox(_T("Error creating command instance"));
	}
	try
	{

		//create the connection pointer

		UpdateData();
		CString str_cid, str_billid, str_time, str_cost, str_amount, str_name, str_totalcost;
		edit_costomerid.GetWindowTextW(str_cid);
		edit_billid.GetWindowTextW(str_billid);
		edit_cost.GetWindowText(str_cost);
		edit_goodname.GetWindowText(str_name);
		edit_amount.GetWindowText(str_amount);
		CTime timeTime;
		DWORD dwResult = ctrl_datepicker.GetTime(timeTime);
		str_time = timeTime.Format(_T("20%y-%m-%d"));
		int totalcost = _ttoi(str_cost) * _ttoi(str_amount);
		str_totalcost.Format(_T("%d"), totalcost);

		if (!str_cost.IsEmpty() || !str_name.IsEmpty() || !str_cid.IsEmpty() || !str_billid.IsEmpty() || !str_time.IsEmpty() || !str_amount.IsEmpty() )
		{
			CString query = _T("use GoodsManager; Insert into G_Bill Values (") + str_cid + _T(",") + str_billid + _T(",'") + str_time + _T("','") + str_name + _T("',") + str_amount + _T(",") + str_cost + _T(",") + str_totalcost + _T(",0);");
			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);
			MessageBox(_T("Data added successfully"));

			//update data vao list control

		}
		//Close the database
		pConn->Close();
		UpdateData(TRUE);

	}
	catch (_com_error &ce)
	{
		MessageBox(_T("You failed, haha. Don't let any fields empty"));

	}
}
