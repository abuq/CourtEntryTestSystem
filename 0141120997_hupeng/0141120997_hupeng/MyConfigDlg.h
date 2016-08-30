#pragma once
#include "afxwin.h"


// MyConfigDlg 对话框

class MyConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MyConfigDlg)

public:
	MyConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyConfigDlg();

// 对话框数据
	enum { IDD = IDD_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int et_total_time;
//	CString et_total_questions;
	CString et_media_format;
	int et_max_speed;
	double et_percentage_accuracy;
	double et_percentage_speed;
	afx_msg void OnChangeEditTotalQuestions();
	CComboBox cb_test_num;
	int et_total_questions;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	CString answers[1000];

	CString file_paths[1000];
	afx_msg void OnEnChangeEditRightAnswer();
	CString et_right_answer;
	afx_msg void OnCbnSelchangeComboTestNum();
	int test_select;
	afx_msg void OnEnChangeMfceditbrowse1();
	CString eb_file;
};
