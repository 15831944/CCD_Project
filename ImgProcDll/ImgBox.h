#pragma once

#include "atlbase.h"
#include "Windows.h"
#include "afxmt.h"
#include "SmartImage.h"

#include "..\\StaticCtrlDll\\CtrlBase.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\StaticCtrlDll.lib")
#else
#pragma comment(lib, "..\\Release\\StaticCtrlDll.lib")
#endif

// CImgBox
static UINT gMsgColMarkPoint    = RegisterWindowMessage(_T("gMsgColMarkPoint"));//�ɫ��ӛ�c����
static UINT gMsgImgPointMove    = RegisterWindowMessage(_T("gImgColMarkMove"));// ����Ƅӣ����r�l�͈D������
static UINT gMsgColMarkFinish    = RegisterWindowMessage(_T("gMsgColMarkFinish"));//�ɫ��ӛ���


enum
{
	ZOOM_DISABLE = 0,
	ZOOM_CTRL,
	ZOOM_ROLL,
	ZOOM_MODES
};

#define IMG_MONO  0//��ͨ���D��
#define IMG_COL  1//��ɫ�D��

#define RGB_IMG_BOX_BACK		RGB(64, 64, 64)		// ����ɫ
#define RGB_IMG_BOX_BORDER		RGB(0, 190, 190)	// �߿���ɫ
#define RGB_IMG_BOX_GRAY		RGB(128, 128, 128)	// �߿���ɫ

class AFX_EXT_CLASS CImgBox : public CCtrlBase
{
	DECLARE_DYNAMIC(CImgBox)

public:
	CImgBox();
	virtual ~CImgBox();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int m_nIndex;			// ͼ����ʾ�����
	int m_nZoomMode;		// �Ŵ�ģʽ, 0: ������Ŵ�, 1: ��Ҫ��סCtrl�����ſ��ԷŴ�, 3: ֱ�ӹ������־Ϳ��ԷŴ�
	CString m_strTitle;		// ͼ����ʾ����

	BOOL m_bTopLeft;		// �Ƿ�����Ͻ���ʾ
	BOOL m_bKeepScale;		// �Ƿ񱣳ֱ���
	BOOL m_bDbClickEnable;	// �Ƿ�����˫��

	virtual void DrawElement(CDC * pDC, CRect rcDraw);

	virtual void SetImage(CSmartImage * pImgSrc, const CString * pTitle = nullptr);
	void SetImage(CSmartImage * pImgSrc, const CString & pTitle);
	void SetImgEmpty(void);

	AFX_INLINE BOOL IsImgEmpty(void);
	AFX_INLINE CSmartImage * GetImage(void);
protected:
	CRect m_rcDc;			// �Ŵ�DC����
	CRect m_rcView;			// �Ŵ����ʾ����ʾ����ľ���
	CRect m_rcScale;		// ������ʾ������ľ���
	CRect m_rcDcScale;		// �Ŵ��ı�������

	double m_dMagnify;		// �Ŵ���
	double m_dStep;			// �Ŵ���������
	CPoint m_ptMouse;		// ���λ��

	CSemaphore m_seDraw;

	CSmartImage m_Image;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

public:
	Point2i m_ptCurImage;//��ǰ�D���ϵČ��H����

	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
};


