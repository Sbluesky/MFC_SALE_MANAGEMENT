// GLdialog.cpp : implementation file
//

#include "pch.h"
#include "MFCGoodsManagement.h"
#include "GLdialog.h"
#include "afxdialogex.h"
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

#import "C:\\Program files\\Common Files\\System\\Ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

// GLdialog dialog

IMPLEMENT_DYNAMIC(GLdialog, CDialogEx)

GLdialog::GLdialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLDIALOG, pParent)
{

}

GLdialog::~GLdialog()
{
}

void ConnecttoDatabase(_ConnectionPtr &pConn, _CommandPtr &Cmd1, HRESULT &hr)
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

BOOL GLdialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//list control code 
	
		listcontrol_gl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
		listcontrol_gl.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 50);
		listcontrol_gl.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 200);
		listcontrol_gl.InsertColumn(2, _T("Cost"), LVCFMT_LEFT, 100);
		listcontrol_gl.InsertColumn(3, _T("Note"), LVCFMT_LEFT, 100);
	
	
	_ConnectionPtr pConn = NULL;
	_bstr_t strCon = ("testDNS");
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);

	try
	{
		ConnecttoDatabase(pConn, Cmd1, hr);

		_RecordsetPtr pRstEmployee = NULL;
		HRESULT hr1 = pRstEmployee.CreateInstance(__uuidof(Recordset));

		if (FAILED(hr1))
		{
			MessageBox(_T("Failed creating record set instancen"));
		}


		pRstEmployee->Open("use GoodsManager; SELECT * FROM GoodsList", strCon, adOpenForwardOnly, adLockReadOnly, adCmdText);

		_bstr_t val_name;
		_bstr_t val_note;
		int val_cost;

		pRstEmployee->MoveFirst();

		//Loop through the Record set
		if (!pRstEmployee->EndOfFile)
		{
			while (!pRstEmployee->EndOfFile)
			{
				val_name = pRstEmployee->Fields->GetItem("GL_Name")->Value;
				val_cost = pRstEmployee->Fields->GetItem("GL_Cost")->Value.intVal;
				val_note = pRstEmployee->Fields->GetItem("GL_Note")->Value;

				//Add data vao list control
				CString str_cost;
				str_cost.Format(_T("%d"), val_cost);
				addDatainListControl((LPCTSTR) val_name, str_cost, (LPCTSTR) val_note);

				pRstEmployee->MoveNext();
			}
		}		

		//Close the database
		pConn->Close();
		UpdateData(TRUE);



	}
	catch (_com_error &ce)
	{
		MessageBox(_T("You failed, haha. Don't let any fields empty"));

	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void GLdialog::addDatainListControl(CString str_name, CString str_cost, CString str_note)
{
	CString str_Number_Order;
	str_Number_Order.Format(_T("%d"), Number_Order);
	listcontrol_gl.InsertItem(Number_Order, str_Number_Order);
	listcontrol_gl.SetItemText(Number_Order, 1, str_name);
	listcontrol_gl.SetItemText(Number_Order, 2, str_cost);
	listcontrol_gl.SetItemText(Number_Order, 3, str_note);
	Number_Order += 1;
}

void GLdialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CNT_GL, listcontrol_gl);
	DDX_Control(pDX, IDC_EDT_GOODNAME, edit_goodname);
	DDX_Control(pDX, IDC_EDT_GOODCOST, edit_goodcost);
	DDX_Control(pDX, IDC_EDT_GOODNOTE, edit_note);
}


BEGIN_MESSAGE_MAP(GLdialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &GLdialog::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &GLdialog::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &GLdialog::OnBnClickedBtnUpdate)
END_MESSAGE_MAP()


// GLdialog message handlers


void GLdialog::OnBnClickedBtnAdd()
{
	//DL_GL_ADD gladd;
	//gladd.DoModal();
	_bstr_t strName;
	_ConnectionPtr pConn = NULL;
	_bstr_t strCon("testDNS");
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	ConnecttoDatabase(pConn, Cmd1, hr);

	try
	{

		//create the connection pointer

		UpdateData();
		CString str_cost, str_note, str_name;
		edit_goodcost.GetWindowText(str_cost);
		edit_goodname.GetWindowText(str_name);
		edit_note.GetWindowText(str_note);

		if (!str_cost.IsEmpty() || !str_name.IsEmpty() || !str_note.IsEmpty())
		{
			CString query = _T("use GoodsManager; Insert into GoodsList Values ('") + str_name + _T("',") + str_cost + _T(",'") + str_note + _T("');");
			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);
			MessageBox(_T("Data added successfully"));
			
			//update data vao list control
			addDatainListControl(str_name, str_cost, str_note);


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


void GLdialog::OnBnClickedBtnDelete()
{
	//delete item in database
	_ConnectionPtr pConn = NULL;
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	ConnecttoDatabase(pConn, Cmd1, hr);
	
	for (int i = 0; i < listcontrol_gl.GetItemCount(); i++)
	{
		BOOL bCheck = listcontrol_gl.GetCheck(i);
		if (bCheck)
		{			

			CString get_val_delete = listcontrol_gl.GetItemText(i,1);
			CString query = _T("use GoodsManager; DELETE FROM GoodsList WHERE GL_Name='") + get_val_delete + _T("';");
			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);

			// item is checked

			listcontrol_gl.DeleteItem(i);
			


		}
	}
	pConn->Close();
}

void GLdialog::OnBnClickedBtnUpdate()
{
	CString str_cost, str_note, str_name;

	_ConnectionPtr pConn = NULL;
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	ConnecttoDatabase(pConn, Cmd1, hr);
	
	for (int i = 0; i < listcontrol_gl.GetItemCount(); i++)
	{
		BOOL bCheck = listcontrol_gl.GetCheck(i);
		if (bCheck)
		{
			
			//Set edit control thanh cac item da chon
			UpdateData();
			edit_goodname.GetWindowText(str_name);
			edit_goodcost.GetWindowText(str_cost);
			edit_note.GetWindowText(str_note);
			CString get_val_update = listcontrol_gl.GetItemText(i, 1);
			CString query = _T("use GoodsManager; UPDATE GoodsList SET GL_Name = '") + str_name + _T("', GL_Cost = '") + str_cost + _T("', GL_Note = '") + str_note + _T("' WHERE GL_Name='") + get_val_update + _T("';");
			
			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);
			MessageBox(_T("Update Data Successfully!"));
			listcontrol_gl.SetItemText(i, 1, str_name);
			listcontrol_gl.SetItemText(i, 2, str_cost);
			listcontrol_gl.SetItemText(i, 3, str_note);

			break;
		}
	}
	edit_goodname.SetWindowTextW(_T(""));
	edit_goodcost.SetWindowTextW(_T(""));
	edit_note.SetWindowTextW(_T(""));
	pConn->Close();

}

//function to getItem from list control
CString GLdialog::CheckItem()
{
	CString cstr;
	for (int i = 0; i < GLdialog::listcontrol_gl.GetItemCount(); i++)
	{
		BOOL bCheck = GLdialog::listcontrol_gl.GetCheck(i);
		if (bCheck)
		{
			for (int j = 1; i < 4; j++)
			{
				cstr += GLdialog::listcontrol_gl.GetItemText(i, j) + _T("|");

			}

			break;

		}
	}
	return cstr;
}