#pragma once
#include <vector>
using namespace std;
struct  tagItemImage 
{
      //CImageEx	*pImage;
      int	nItem;
};
typedef vector<tagItemImage>	CItemImgArray;
// CListCtrlEx

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	virtual ~CListCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	void PositionScrollBars();
};
