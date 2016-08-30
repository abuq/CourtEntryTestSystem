// MyConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0141120997_hupeng.h"
#include "MyConfigDlg.h"
#include "afxdialogex.h"
#include "0141120997_hupengDlg.h"
#include <Windows.h>



IMPLEMENT_DYNAMIC(MyConfigDlg, CDialogEx)

MyConfigDlg::MyConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyConfigDlg::IDD, pParent)
	, et_total_time(0)
	, et_media_format(_T(""))
	, et_max_speed(0)
	, et_percentage_accuracy(0)
	, et_percentage_speed(0)
	, et_total_questions(0)


	, et_right_answer(_T(""))
	, test_select(-1)
	, eb_file(_T(""))
{
	for (int i = 0 ; i< 1000 ; i++)
	{
		answers[i] = L"";
		file_paths[i] = L"";
	}
}

MyConfigDlg::~MyConfigDlg()
{
}

void MyConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TOTAL_TIME, et_total_time);
	DDX_Text(pDX, IDC_EDIT_MEDIA_FORMAT, et_media_format);
	DDX_Text(pDX, IDC_EDIT_MAX_SPEED, et_max_speed);
	DDX_Text(pDX, IDC_EDIT_ZQLQZ, et_percentage_accuracy);
	DDX_Text(pDX, IDC_EDIT_SLQZ, et_percentage_speed);
	DDX_Control(pDX, IDC_COMBO_TEST_NUM, cb_test_num);
	DDX_Text(pDX, IDC_EDIT_TOTAL_QUESTIONS, et_total_questions);
	DDX_Text(pDX, IDC_EDIT_RIGHT_ANSWER, et_right_answer);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, eb_file);
}


BEGIN_MESSAGE_MAP(MyConfigDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_TOTAL_QUESTIONS, &MyConfigDlg::OnChangeEditTotalQuestions)
	ON_BN_CLICKED(IDOK, &MyConfigDlg::OnBnClickedOk)
	ON_WM_DROPFILES()
	ON_EN_CHANGE(IDC_EDIT_RIGHT_ANSWER, &MyConfigDlg::OnEnChangeEditRightAnswer)
	ON_CBN_SELCHANGE(IDC_COMBO_TEST_NUM, &MyConfigDlg::OnCbnSelchangeComboTestNum)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &MyConfigDlg::OnEnChangeMfceditbrowse1)
END_MESSAGE_MAP()




//响应用户修改总题数的操作，在下拉框中动态加载
void MyConfigDlg::OnChangeEditTotalQuestions()
{

	UpdateData(TRUE);
	cb_test_num.ResetContent();
	for (int i = 1 ; i <= et_total_questions ; i++)
	{
		CString cs;
		cs.Format(L"%d",i);
		cb_test_num.AddString(cs);
	}
}

//初始化界面是初始化变量
BOOL MyConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	et_media_format = _T("mp3");
	et_percentage_accuracy = 0.7;
	et_percentage_speed = 0.3;
	et_max_speed = 100;
	et_total_time = 15;
	et_total_questions = 0;

	UpdateData(FALSE);

	return TRUE;
}





//响应用户对于文本框的输入操作
void MyConfigDlg::OnEnChangeEditRightAnswer()
{

	UpdateData(TRUE);
	if (cb_test_num.GetCurSel() == -1)
	{
		MessageBox(L"请先选择试题编号");
		et_right_answer = L"";
		UpdateData(FALSE);
		return;
	}
	
}


void MyConfigDlg::OnCbnSelchangeComboTestNum()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (test_select != -1)
	{
		answers[test_select] = et_right_answer;
		file_paths[test_select] = eb_file;
	}

	test_select = cb_test_num.GetCurSel();
	eb_file = file_paths[test_select];
	et_right_answer = answers[test_select];
	UpdateData(FALSE);
}


void MyConfigDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (test_select != -1)
	{
		answers[test_select] = et_right_answer;
		file_paths[test_select] = eb_file;
	}

	for(int i = 0 ; i < et_total_questions ; i++)
	{
		if (answers[i] =="" || file_paths[i] == "")
		{
			CString cs;
			cs.Format(L"第%d题试题信息不完整",i+1);
			MessageBox(cs);
			return;
		}
	}
	if (et_total_questions == 0)
	{
		MessageBox(L"请至少添加一道题");
		return;
	}
	UpdateData(TRUE);
	CString cs;
	cs.Format(L"%d",et_total_time);
	WritePrivateProfileStringW(_T("ExamInfo"),_T("total_minutes"),cs,_T("d://work.ini"));
	cs.Format(L"%d",et_total_questions);
	WritePrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),cs,_T("d://work.ini"));

	WritePrivateProfileStringW(_T("ExamInfo"),_T("audio_format"),et_media_format,_T("d://work.ini"));
	cs.Format(L"%d",et_max_speed);
	WritePrivateProfileStringW(_T("ExamInfo"),_T("max_speed"),cs,_T("d://work.ini"));
	cs.Format(L"%f",et_percentage_accuracy);
	WritePrivateProfileStringW(_T("ExamInfo"),_T("percentage_accuracy"),cs,_T("d://work.ini"));
	cs.Format(L"%f",et_percentage_speed);
	WritePrivateProfileStringW(_T("ExamInfo"),_T("percentage_speed"),cs,_T("d://work.ini"));
	for(int i = 0 ; i < et_total_questions ; i ++)
	{
		//cs.Format(L"answer%d",i);
		CMy0141120997_hupengDlg cDlg;
		//WritePrivateProfileStringW(_T("ExamInfo"),cs,cDlg.encode(answers[i]),_T("ini/work.ini"));
		cDlg.write_answer(i+1,cDlg.encode(answers[i]));
	}
	MessageBox(L"恭喜你，配置写入成功！");
	CDialogEx::OnOK();
}


void MyConfigDlg::OnEnChangeMfceditbrowse1()
{
	
	UpdateData(TRUE);
	
	if (test_select == -1)
	{
		MessageBox(L"请先选择试题编号");
		return;
	}
	//文件复制操作
	CString source = eb_file;
	source = L"\"" + source + L"\"";
	CString target;
	USES_CONVERSION;

	target.Format(L"\"d:\\%d.",test_select+1);
	target = target + et_media_format ;
	target = target + L"\"";

	CString comm = L"copy /y " + source + L" " + target;

	string str_comm = T2A(comm.GetBuffer());
	comm.ReleaseBuffer();
	system(str_comm.c_str());
}
