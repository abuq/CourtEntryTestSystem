
// 0141120997_hupengDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <string>

using namespace std;

// CMy0141120997_hupengDlg �Ի���
class CMy0141120997_hupengDlg : public CDialogEx
{
// ����
public:
	CMy0141120997_hupengDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY0141120997_HUPENG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CString et_zkz;
	CString et_zkz;
	CString et_sfz;
	afx_msg void OnBnClickedBtnBeginTest();
	int check_zkz(CString zkz);
	// ������֤����Ч�ԣ�����ֵ��0������
	int check_sfz(CString sfz);
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnSubmit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString tv_time_left;
	CString tv_show_time_lable;
	CString getFormatTime(int time_left);
	int time_sum;
	void readConfigureFile(void);
	int total_minutes;
	int total_questions;
	CString audio_format;
	int max_speed;
	double percentage_accuracy;
	double percentage_speed;
	CString answer;
	CComboBox cb_select_test;
	int test_select;
	CString et_test_content;
	int write_pdf(CString zkz, CString sfz, double zhun_que_lv, double da_zi_su_du, double cheng_ji, CString nei_rong);

	void  OnPlay(int test_select);
	DWORD getinfo(UINT wDeviceID,DWORD item);
	void OnStop();

	int my_min(int a, int b);
	int my_min(int a, int b, int c);
	int my_max(int a, int b);
	float similarity(string str1, string str2);
	afx_msg void OnBnClickedBtnPrint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CString encode(CString cstr);
	CString decode(CString cstr);
	CEdit ct_content_text;
	afx_msg void OnBnClickedBtnConfig();

//	int write_answer(void);
	void write_answer(int file_id, CString answer);
	CString read_answer(int file_id);
	CString login(CString sfz, CString zkz);
};
