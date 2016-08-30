


#include "stdafx.h"
#include "0141120997_hupeng.h"
#include "0141120997_hupengDlg.h"
#include "afxdialogex.h"
#include "pdflib.h"
#include <Windows.h>
#include  <mmsystem.h>
#include <string>
#include <sstream>
#include "winsock2.h"
#include "winsock.h"//��Ϊ���ݿ���ͨ���������ӵģ���������������ͷ�ļ�
#include "mysql.h"//���ûʲô��˵�ģ�mysqlͷ�ļ���ȻҪ����  

#include "MyConfigDlg.h"


using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"ws2_32.lib")
#pragma   comment(lib, "winmm.lib")
#pragma comment(lib, "PDFLib.lib")
#pragma comment(lib,"libmySQL.lib")//���������Ҳ�����ڹ�������������
// CMy0141120997_hupengDlg �Ի���


MCI_OPEN_PARMS op;

CMy0141120997_hupengDlg::CMy0141120997_hupengDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0141120997_hupengDlg::IDD, pParent)
	, et_zkz(_T(""))
	, et_sfz(_T(""))
	, tv_time_left(_T(""))
	, tv_show_time_lable(_T(""))
	, time_sum(0)
	, total_minutes(0)
	, et_test_content(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy0141120997_hupengDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ET_ZKZ, et_zkz);
	DDV_MaxChars(pDX, et_zkz, 10);
	DDX_Text(pDX, IDC_ET_SFZ, et_sfz);
	DDV_MaxChars(pDX, et_sfz, 18);
	DDX_Text(pDX, IDC_TV_TIME_LEFT, tv_time_left);
	DDX_Text(pDX, IDC_TV_SHOW_TIME_LABLE, tv_show_time_lable);
	DDX_Control(pDX, IDC_COMBO_SELECT_TEST, cb_select_test);
	DDX_Text(pDX, IDC_ET_TEST_CONTENT, et_test_content);
	DDX_Control(pDX, IDC_ET_TEST_CONTENT, ct_content_text);
}

BEGIN_MESSAGE_MAP(CMy0141120997_hupengDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BEGIN_TEST, &CMy0141120997_hupengDlg::OnBnClickedBtnBeginTest)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CMy0141120997_hupengDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_SUBMIT, &CMy0141120997_hupengDlg::OnBnClickedBtnSubmit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PRINT, &CMy0141120997_hupengDlg::OnBnClickedBtnPrint)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CONFIG, &CMy0141120997_hupengDlg::OnBnClickedBtnConfig)
END_MESSAGE_MAP()




BOOL CMy0141120997_hupengDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	


	readConfigureFile();
	time_sum = 0;
	CWnd *pWnd = GetDlgItem(IDC_BTN_SUBMIT);
	if (pWnd->IsWindowEnabled())
	{
		pWnd->EnableWindow(FALSE);

	}
	pWnd = GetDlgItem(IDC_BTN_PRINT);
	if (pWnd->IsWindowEnabled())
	{
		pWnd->EnableWindow(FALSE);

	}
	pWnd = GetDlgItem(IDC_ET_TEST_CONTENT);
	if (pWnd->IsWindowEnabled())
	{
		pWnd->EnableWindow(FALSE);

	}

	pWnd = GetDlgItem(IDC_TV_SHOW_TIME_LABLE);
	if (pWnd->IsWindowEnabled())
	{
		CFont * cFont=new CFont;  
		cFont->CreateFont(16,0,0,0,FW_SEMIBOLD,FALSE,FALSE,0,   
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,  
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,  
			DEFAULT_PITCH&FF_SWISS,L"Arial"); 
		pWnd->SetFont(cFont);
		

	}


	

	return TRUE;  
}



void CMy0141120997_hupengDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy0141120997_hupengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��Ӧ�����ʼ�����¼�
void CMy0141120997_hupengDlg::OnBnClickedBtnBeginTest()
{
	// ��ʼ����
	//��ȡ����ֵ
	UpdateData(TRUE);
	if(check_zkz(et_zkz) == 1)
	{
		MessageBox(L"׼��֤Ϊ10λ����");
		return;
	}
	int check_sfz_result = check_sfz(et_sfz);
	if (check_sfz_result==1)
	{
		MessageBox(L"���֤����Ϊ18Ϊ���֣����һλ����Ϊ��X��֧�ִ�Сд��");
		return;
	}
	if (check_sfz_result == 2)
	{
		MessageBox(L"����������֤�Ų���ȷ");
		return;
	}
	CString name = login(et_sfz,et_zkz);
	if (name == "")
	{
		MessageBox(L"���������Ϣ������");
		return;
	}
	else
	{
		CString msg;
		msg = L"��ã�";
		msg = msg + name;
		msg = msg + L"����ӭ�μӿ���";
		MessageBox(msg);
	}
	//У�����
	//�ؼ�״̬����
	CWnd *pWnd = GetDlgItem(IDC_ET_SFZ);
	pWnd->EnableWindow(FALSE);
	pWnd = GetDlgItem(IDC_ET_ZKZ);
	pWnd->EnableWindow(FALSE);//
	pWnd = GetDlgItem(IDC_COMBO_SELECT_TEST);
	pWnd->EnableWindow(FALSE);//
	pWnd = GetDlgItem(IDC_BTN_BEGIN_TEST);
	pWnd->EnableWindow(FALSE);//
	
	test_select = cb_select_test.GetCurSel();

	pWnd = GetDlgItem(IDC_BTN_SUBMIT);
	pWnd->EnableWindow(TRUE);
	pWnd = GetDlgItem(IDC_ET_TEST_CONTENT);
	pWnd->EnableWindow(TRUE);
	//����ʱ
	tv_show_time_lable = "ʣ��ʱ�䣺";
	tv_time_left.Format(L"%d��%d��",total_minutes,0);
	UpdateData(FALSE);
	SetTimer(1,1000,NULL);

	readConfigureFile();

	OnPlay(test_select+1);
	Invalidate();
	
}


//���׼��֤����ȷ�ԣ���ȷ���أ�0������ȷ������1

int CMy0141120997_hupengDlg::check_zkz(CString zkz)
{
	if (zkz.GetLength() == 10)
	{
		return 0;
	}
	return 1;
}


// ������֤����Ч�ԣ�����ֵ��0������
int CMy0141120997_hupengDlg::check_sfz(CString sfz)
{
	//��鳤���Լ����
	if (sfz.GetLength() != 18)
	{
		return 1;//���֤���ȳ���
	}
	USES_CONVERSION;
	string str_sfz = T2A(sfz.GetBuffer());
	for(int i = 0 ; i < 18 ; i++)
	{
		
		if (!(str_sfz.at(i)>='0' && str_sfz.at(i) <= '9'))
		{
			if (!(i == 17 && (str_sfz.at(i) == 'X' || str_sfz.at(i) == 'x')))
			{
				return 1;
			}
		}
	}
	//�������
	
	//У�����֤����
	int jiaoyanxishu[] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };
	int jiaoyanjieguo[] = {1,0,-1,9,8,7,6,5,4,3,2};
	int sum = 0;
	for (int i = 0 ; i< 17 ;i ++)
	{
		sum += (str_sfz[i]-'0')*jiaoyanxishu[i];
	}
	sum = sum % 11;
	sum = jiaoyanjieguo[sum];
	if ( !((sum==str_sfz[17]-'0')||((sum == -1 && (str_sfz[17]=='X' || str_sfz[17] == 'x')))))
	{
		return 2;
	}

	return 0;
}


void CMy0141120997_hupengDlg::OnBnClickedBtnCancel()
{
	 CDialog::OnOK(); 
}

//��Ӧ�ύ�𰸽���
void CMy0141120997_hupengDlg::OnBnClickedBtnSubmit()
{
	int nRes = MessageBox(L"�ύ֮�����ı��ο��Խ�������\n��ȷ��Ҫ�ύ��",L"��ʾ",MB_ICONASTERISK|MB_OKCANCEL);
	if (IDOK == nRes)
	{
		OnStop();
		KillTimer(1);
		tv_show_time_lable = "���Ŀ�������ʱ";
		tv_time_left.Format(L"%d��%d��",time_sum/60,time_sum%60);
		UpdateData(FALSE);
		CWnd *pWnd = GetDlgItem(IDC_BTN_PRINT);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BTN_SUBMIT);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_ET_TEST_CONTENT);
		pWnd->EnableWindow(FALSE);
	}
}

//����ʱ�ӣ�ÿ�����һ��ʣ��ʱ��
void CMy0141120997_hupengDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(TRUE);
	tv_time_left = getFormatTime(++time_sum);
	tv_show_time_lable = "ʣ��ʱ�䣺";
	if (time_sum == total_minutes*60)
	{
		KillTimer(1);
		CWnd *pWnd = GetDlgItem(IDC_ET_TEST_CONTENT);
		pWnd->EnableWindow(FALSE);
	}

	et_test_content.ReleaseBuffer();
	int text_length = et_test_content.GetLength();
	ct_content_text.SetSel( text_length, text_length, TRUE );

	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}

//�õ�ʣ��ʱ��Ľ��
CString CMy0141120997_hupengDlg::getFormatTime(int time_left)
{
	int sum = total_minutes*60 - time_left;
	int second = sum % 60;
	int minute = sum / 60;
	CString t;
	t.Format(L"%d��%d��",minute,second);
	return t;
}



// ��ȡ�����ļ�
void CMy0141120997_hupengDlg::readConfigureFile(void)
{
	total_minutes = GetPrivateProfileInt(L"ExamInfo",L"total_minutes",0,L"d://work.ini");
	total_questions = GetPrivateProfileInt(L"ExamInfo",L"total_questions",0,L"d://work.ini");

	GetPrivateProfileString(L"ExamInfo",L"audio_format",L"",audio_format.GetBuffer(MAX_PATH),MAX_PATH,L"d://work.ini");
	max_speed = GetPrivateProfileInt(L"ExamInfo",L"max_speed",0,L"d://work.ini");
	CString tmp;
	string str_tmp;
	USES_CONVERSION;
	stringstream oss;

	GetPrivateProfileString(L"ExamInfo",L"percentage_accuracy",L"",tmp.GetBuffer(MAX_PATH),MAX_PATH,L"d://work.ini");
	str_tmp = T2A(tmp.GetBuffer());
	oss<<str_tmp;
	oss>>percentage_accuracy;

	oss.clear();

	GetPrivateProfileString(L"ExamInfo",L"percentage_speed",L"",tmp.GetBuffer(MAX_PATH),MAX_PATH,L"d://work.ini");
	str_tmp = T2A(tmp.GetBuffer());
	oss<<str_tmp;
	oss>>percentage_speed;


	if (cb_select_test.GetCurSel() + 1 > 0)
	{
		answer = decode(read_answer(cb_select_test.GetCurSel() + 1));
	}
	

	cb_select_test.ResetContent();
	for (int i = 1 ;i <= total_questions ; i++)
	{
		CString tmp;
		tmp.Format(L"0%d",i);
		cb_select_test.AddString(tmp);
	}
	cb_select_test.SetCurSel(0);
	return;
}

//��ӡ�ɼ���
int CMy0141120997_hupengDlg::write_pdf(CString zkz, CString sfz, double zhun_que_lv, double da_zi_su_du, double cheng_ji, CString nei_rong)
{
	remove("�ɼ���.pdf");

	PDF *p;

	if ((p = PDF_new()) == (PDF *) 0){
		printf("Couldn't create PDFlib object (out of memory)!/n");
		return 1;
	}

	PDF_TRY(p) {
		/* This means we must check return values of load_font() etc. */
		//PDF_set_parameter(p, "errorpolicy", "return");

		if (PDF_begin_document(p, "d://�ɼ���.pdf", 0, "") == -1) {
			printf("Error: %s/n", PDF_get_errmsg(p));
			return 2;
		}

		/* This line is required to avoid problems on Japanese systems */
		PDF_set_parameter(p, "hypertextencoding", "host");
		//PDF_set_parameter(p, "fakebold", "true");
		//PDF_set_parameter( p,"license","X600605-009100-4E7661-329E0C");//ȥ��ˮӡ����ע���д�롣  


		PDF_set_info(p, "Creator", "hello.c");
		PDF_set_info(p, "Author", "Thomas Merz");
		PDF_set_info(p, "Title", "Hello, world (C)!");

		PDF_begin_page_ext(p, a4_width, a4_height, "");

		int font_song = PDF_findfont(p,"STSong-Light", "GB-EUC-H", 0);
		PDF_setfont(p,font_song, 12);
		PDF_set_text_pos(p,50, a4_height - 50);



		USES_CONVERSION;
		string s = T2A(( zkz.GetBuffer()));
		s = "׼��֤�ţ�" + s;
		PDF_show(p,s.c_str());

		PDF_set_text_pos(p,50, a4_height - 65);
		s = T2A(( sfz.GetBuffer()));
		s = "���֤�ţ�" + s;
		PDF_show(p,s.c_str());

		PDF_setfont(p,font_song, 8);
		PDF_set_text_pos(p,50, a4_height - 85);
		CString cs;
		cs.Format(L"�����ֵ���ȷ����%f���ٶ���%f��/���ӣ����ο��Եĳɼ���%f��",zhun_que_lv,da_zi_su_du,cheng_ji);
		s = T2A(cs.GetBuffer());
		PDF_show(p,s.c_str());

		PDF_setfont(p,font_song, 8);
		PDF_set_text_pos(p,50, a4_height - 100);
		s="�����������ο���¼�������:";
		PDF_show(p,s.c_str());

		s = T2A(nei_rong.GetBuffer());
		for (int i = 0 ; i <= s.length()/60 ; i++)
		{
			PDF_set_text_pos(p,50, a4_height - 120 - i * 10);
			
			int begin = 0+60*i;
			int end = 60;
			if (60 + 60 * i >= s.length())
			{
				end = s.length()-begin;
			}else{
				end = 60 ;
			}
			string tmp = s.substr(begin,end);
			PDF_show(p,tmp.c_str());
		}

		PDF_end_page_ext(p, "");
		PDF_end_document(p, "");
	}

	PDF_CATCH(p) {
		printf("PDFlib exception occurred in sample:/n");
		printf("[%d] %s: %s/n",
			PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		CString cs; 
		cs.Format(L"[%d] %s: %s/n",
			PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		PDF_delete(p);
		return 3;
	}

	PDF_delete(p);
	return 0;
}

//��������
void  CMy0141120997_hupengDlg::OnPlay(int test_select)
{

	DWORD cdlen;//��Ƶ�ļ�����

	op.dwCallback=NULL;
	op.lpstrAlias=NULL;
	op.lpstrDeviceType=_T("MPEGAudio");  //�豸���ͣ�������ļ�������������
	CString file_name;
	file_name.Format(L"d://%d.",test_select);
	audio_format.ReleaseBuffer();
	file_name = file_name + audio_format;

	op.lpstrElementName= file_name; //�ļ�·��
	op.wDeviceID=NULL;      //���豸�ɹ��Ժ󱣴�����豸�ű���
	UINT rs;        //���ܺ������ؽ��
	//����������豸���ɹ�����0�����򷵻ش���ţ������������������MCI_OPEN_ELEMENT  
	rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&op);

	mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL);

	cdlen=getinfo(op.wDeviceID,MCI_STATUS_LENGTH);//��ȡ��Ƶ�ļ�����

	if(rs==0)        //�豸�򿪳ɹ��Ͳ����ļ�
	{
		MCI_PLAY_PARMS pp;
		pp.dwCallback=NULL;
		pp.dwFrom=0;      //��ʼ���ŵ�λ��
		mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
		//�����ļ������������������ΪMCI_WAIT����򴰿ڻᱻ������Ϊ�˱����������������ΪMCI_NOTIFY
	}

	//Sleep(cdlen);//�����ļ����ȵȴ�����MCI_WAITЧ��һ����cdlen�������Կ��Ʋ���ʱ��
	//OnStop();        //�ر���Ƶ�ļ� 
}

DWORD  CMy0141120997_hupengDlg::getinfo(UINT wDeviceID,DWORD item)
{
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
	mcistatusparms.dwItem=item;
	mcistatusparms.dwReturn=0;
	mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}

//ֹͣ��������
void  CMy0141120997_hupengDlg::OnStop()
{
	//��WM_CLOSE��Ϣ��������з���MCI_CLOSE����ر��豸
	MCI_GENERIC_PARMS gp;
	gp.dwCallback=NULL;
	mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);  
}

int CMy0141120997_hupengDlg::my_min(int a, int b)
{
	return a<b?a:b;
}


int CMy0141120997_hupengDlg::my_min(int a, int b, int c)
{
	return my_min(my_min(a,b),c);
}


int CMy0141120997_hupengDlg::my_max(int a, int b)
{
	return a>b?a:b;
}

//�������ƶ�
float CMy0141120997_hupengDlg::similarity(string str1, string str2)
{
	//���������ַ����ĳ��ȡ�
	int len1 = str1.length();
	int len2 = str2.length();
	//�������飬���ַ����ȴ�һ���ռ�
	int **dif;
	dif = new int*[len1+1];

	for (int i = 0 ; i < len1+1 ; i++)
	{
		dif[i] = new int[len2+1];
	}

	//����ֵ������B��
	for (int a = 0; a <= len1; a++) {
		dif[a][0] = a;
	}
	for (int a = 0; a <= len2; a++) {
		dif[0][a] = a;
	}
	//���������ַ��Ƿ�һ�����������ϵ�ֵ
	int temp;
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (str1.at(i - 1) == str2.at(j - 1)) {
				temp = 0;
			} else {
				temp = 1;
			}
			//ȡ����ֵ����С��
			dif[i][j] = my_min(dif[i - 1][j - 1] + temp, dif[i][j - 1] + 1,
				dif[i - 1][j] + 1);
		}
	}
	return 1 - (float) dif[len1][len2] / my_max(str1.length(), str2.length());
}

//��ӡ�ɼ���
void CMy0141120997_hupengDlg::OnBnClickedBtnPrint()
{
	UpdateData(TRUE);
	double speed = (et_test_content.GetLength()*1.00) / time_sum * 60;
	if (speed > max_speed)
	{
		speed = max_speed;
	}
	USES_CONVERSION;
	string str_content = T2A(et_test_content.GetBuffer());
	string str_answer = T2A(answer.GetBuffer());
	double zhun_que_lv = similarity(str_answer,str_content)*100;
	double grade = percentage_accuracy * zhun_que_lv + percentage_speed * speed;
	write_pdf(et_zkz,et_sfz,zhun_que_lv,speed,grade,et_test_content);
	ShellExecute(NULL,L"open",L"d://�ɼ���.pdf",NULL,NULL,SW_SHOWNORMAL); 

	CWnd *pWnd = GetDlgItem(IDC_BTN_PRINT);
	pWnd->EnableWindow(FALSE);
}


//�ı�ʣ��ʱ��Ŀؼ���ɫ
HBRUSH CMy0141120997_hupengDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_TV_SHOW_TIME_LABLE || pWnd->GetDlgCtrlID() == IDC_TV_TIME_LEFT)
	{
		pDC->SetTextColor(RGB(255,0,0));
	}
	return hbr;
}



//�����㷨
CString CMy0141120997_hupengDlg::encode(CString cstr)
{
	CString tmp = L"";
	int str_len = cstr.GetLength();
	int setpLength = (str_len & 7)+1;
	for(int i = 0 ; i < cstr.GetLength() ; i ++ )
	{

		wchar_t wc = cstr.GetAt(i);
		wc = wc + setpLength;
		tmp = tmp + wc;
	}
	return tmp;
}



//�����㷨
CString CMy0141120997_hupengDlg::decode(CString cstr)
{
	CString tmp = L"";
	int str_len = cstr.GetLength();
	int setpLength = (str_len & 7)+1;
	for(int i = 0 ; i < str_len ; i ++ )
	{
		wchar_t wc = cstr.GetAt(i);
		wc = wc - setpLength;
		tmp = tmp + wc;
	}
	return tmp;
}


//¼�������ļ�
void CMy0141120997_hupengDlg::OnBnClickedBtnConfig()
{
	MyConfigDlg myConfigDlg;
	myConfigDlg.DoModal();
	readConfigureFile();
}





void CMy0141120997_hupengDlg::write_answer(int file_id, CString answer)
{
	
	answer.ReleaseBuffer();
	CFile c_file;
	CString file_name;
	file_name.Format(L"d://%d.txt",file_id);
	c_file.Open(file_name,CFile::modeCreate|CFile::modeWrite);
	USES_CONVERSION;
	char * ss = T2A(answer); 
	c_file.Write(ss,strlen(ss));

	c_file.Close();
}



CString CMy0141120997_hupengDlg::read_answer(int file_id)
{
	
	CString file_name;
	file_name.Format(L"d://%d.txt",file_id);
	CFile pfile(file_name,CFile::modeRead);
	char* pBuf;
	DWORD dwFileLen;
	dwFileLen = pfile.GetLength();
	pBuf=new char[dwFileLen+1];
	pBuf[dwFileLen]=0;
	pfile.Read(pBuf,dwFileLen);
	CString cstr(pBuf);

	pfile.Close();
	return cstr;
}




CString CMy0141120997_hupengDlg::login(CString sfz, CString zkz)
{
	USES_CONVERSION;
	string str_sfz=T2A(sfz.GetBuffer());
	sfz.ReleaseBuffer();
	string str_zkz=T2A(zkz.GetBuffer());
	zkz.ReleaseBuffer();

	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);//��ʼ�����ݿ����
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root", "", "fyxt", 3306, NULL, 0))//localhost:��������ַ������ֱ������IP;root:�˺�;123:����;test:���ݿ���;3306:����˿�  
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
		return NULL;
	}
	else//���ӳɹ�������������ݿ⣬֮�����ز�����������Ƿ����������
	{
		//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
		
		mysql_query(&m_sqlCon, "SET NAMES 'GB2312'");//�������ݿ��ַ���ʽ�����������������'

		string str_query = "select * from user where sfz='" +str_sfz+ "' and zkz='" + str_zkz + "'";

		if (mysql_real_query(&m_sqlCon, str_query.c_str(), (unsigned long)strlen(str_query.c_str())))// ��ѯ���ݿ��е�"��������"��  
		{
			return NULL;
		}
		MYSQL_RES *     STDCALL res = mysql_store_result(&m_sqlCon);//�õ��洢�����  
		MYSQL_ROW	STDCALL row;
		if (NULL == res)//���Ϊ���򷵻�
		{ 
			return NULL; 
		}
		int listrow = 0;
		if (row = mysql_fetch_row(res))//�ظ���ȡ�У������ݷ����б��У�ֱ��rowΪNULL 
		{
			for (int rols = 0; rols < 4; rols++)
			{
				if ( rols == 3 )
				{
					CString myreaddata(row[rols]);
					return myreaddata;
				}
			}
			listrow++;
		}
		else
		{
			//MessageBox(L"���޴���");
			return NULL;
		}
	}
	mysql_close(&m_sqlCon);//�ر�Mysql����
	return NULL;
}
