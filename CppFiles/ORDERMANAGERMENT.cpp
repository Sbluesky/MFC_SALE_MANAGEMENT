// ORDERMANAGERMENT.cpp : implementation file
//

#include "pch.h"
#include "MFCGoodsManagement.h"
#include "ORDERMANAGERMENT.h"
#include "afxdialogex.h"
#include "DL_ADD_ORDERS.h"
#include "DL_CHECKORDERS.h"
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

#import "C:\\Program files\\Common Files\\System\\Ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

// ORDERMANAGERMENT dialog

IMPLEMENT_DYNAMIC(ORDERMANAGERMENT, CDialogEx)

ORDERMANAGERMENT::ORDERMANAGERMENT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ORDERMANAGERMENT, pParent)
{

}

ORDERMANAGERMENT::~ORDERMANAGERMENT()
{
}

void ORDERMANAGERMENT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ORDER, ctrllistorder);
}


BEGIN_MESSAGE_MAP(ORDERMANAGERMENT, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADDORDER, &ORDERMANAGERMENT::OnBnClickedBtnAddorder)
	ON_BN_CLICKED(IDC_BTN_CHECKORDER2, &ORDERMANAGERMENT::OnBnClickedBtnCheckorder2)
END_MESSAGE_MAP()


void ConnecttoDatabase2(_ConnectionPtr &pConn, _CommandPtr &Cmd1, HRESULT &hr)
{
	_bstr_t strCon("testDNS");
	//create the connection pointer
	hr = pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
	{
		printf("Error instantiating Connection objectn");
	}
	//open the sql server connection
	hr = pConn->Open(strCon, "", "", 0);
	if (FAILED(hr))
	{
		printf("Error to open database using ADO");

	}
	hr = Cmd1.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
	{
		printf("Error creating command instance");
	}


}

BOOL ORDERMANAGERMENT::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ctrllistorder.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	ctrllistorder.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 50);
	ctrllistorder.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100);
	ctrllistorder.InsertColumn(2, _T("ID"), LVCFMT_LEFT, 50);

	Updatedailog();
	return TRUE;
}

void ORDERMANAGERMENT::Updatedailog()
{

	_RecordsetPtr pRstEmployee = NULL;
	HRESULT hr1 = pRstEmployee.CreateInstance(__uuidof(Recordset));
	_bstr_t strCon("testDNS");
	if (FAILED(hr1))
	{
		MessageBox(_T("Failed creating record set instancen"));

	}


	pRstEmployee->Open("use GoodsManager; SELECT GB_IdBill FROM G_Bill ORDER BY GB_Time, GB_IdBill", strCon, adOpenForwardOnly, adLockReadOnly, adCmdText);
	int val_id;
	int val_id_temp = -1; //check bill id to show only number orders

	pRstEmployee->MoveFirst();
	//Loop through the Record set
	if (!pRstEmployee->EndOfFile)
	{
		while (!pRstEmployee->EndOfFile)
		{
			val_id = pRstEmployee->Fields->GetItem("GB_IdBill")->Value.intVal;
			if (val_id != val_id_temp)
			{
				//Add data vao list control
				CString str_id;
				str_id.Format(_T("%d"), val_id);
				addDatainListControl(str_id);
			}
			val_id_temp = val_id;

			pRstEmployee->MoveNext();
		}
	}

	//Close the database
	pRstEmployee->Close();
	UpdateData(TRUE);
}

void ORDERMANAGERMENT::addDatainListControl(CString str_id)
{
	CString str_Number_Order;
	str_Number_Order.Format(_T("%d"), Number_Order);
	ctrllistorder.InsertItem(Number_Order, str_Number_Order);
	ctrllistorder.SetItemText(Number_Order, 1, _T("Orders Number "));
	ctrllistorder.SetItemText(Number_Order, 2, str_id);

	Number_Order += 1;
}
// ORDERMANAGERMENT message handlers


void ORDERMANAGERMENT::OnBnClickedBtnAddorder()
{
	DL_ADD_ORDERS dl_add;
	if (dl_add.DoModal() == IDOK)
	{
		ctrllistorder.DeleteAllItems();
		Number_Order = 0;
		Updatedailog();

	}
	
}

void ConnecttoDatabase3(_ConnectionPtr &pConn, _CommandPtr &Cmd1, HRESULT &hr)
{
	_bstr_t strCon("testDNS");
	//create the connection pointer
	hr = pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
	{
		printf("Error instantiating Connection objectn");
	}
	//open the sql server connection
	hr = pConn->Open(strCon, "", "", 0);
	if (FAILED(hr))
	{
		printf("Error to open database using ADO");

	}
	hr = Cmd1.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
	{
		printf("Error creating command instance");
	}
}


void ORDERMANAGERMENT::OnBnClickedBtnCheckorder2()
{
	_ConnectionPtr pConn = NULL;
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	ConnecttoDatabase3(pConn, Cmd1, hr);
	CString get_idbill_check, query, str_time;

	for (int i = 0; i < ctrllistorder.GetItemCount(); i++)
	{
		BOOL bCheck = ctrllistorder.GetCheck(i);
		if (bCheck)
		{

			get_idbill_check = ctrllistorder.GetItemText(i, 2);
			query = _T("use GoodsManager; UPDATE G_Bill SET GB_Check = 1 WHERE GB_IdBill=") + get_idbill_check + _T(";");
			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);

		}
	}
	pConn->Close();

	DL_CHECKORDERS dlcheck;
	//xem lại cái này nha.
	//dlcheck.m_scheckid = get_idbill_check;
	dlcheck.DoModal();
}
