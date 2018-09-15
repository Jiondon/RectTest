//工具的头文件
#include "XVBase.h"

enum XVBorderPosition //圆环创建模式
{
	Internal,  //圆内部
	External,  //圆外部
	Centered   //圆居中
};

enum XVCreateRegionType
{
	Box1,          //框
	Rectangle,     //矩形
	Circle,        //圆
	Ellipse,       //椭圆
	Ring,          //环
	Segment,       //线段 
	Location1      //点集
};

typedef struct XVCreateRegionIn
{
	XVCreateRegionType inType;
	int   inFrameWidth;
	int   inFrameHeight;
	XVCoordinateSystem2D inAlignment; //可选

	//box
	XVBox inBox;

	//rectangle
	XVRectangle2D        inRectangle;

	//Circle or ring
	XVCircle2D           inCircle2D;

	//ring
	float				inRingWidth;
	XVBorderPosition	inBorderPosition;

	//Segment
	XVSegment2D			inSegment;
	int					inWidth;
	bool				inRound;

	//location
	vector<XVLocation>  inLocation;

}XVCreateRegionIn;


typedef struct XVCreateRegionOut
{
	XVRegion     outregion;
	XVCreateRegionType outType;

	//Rectangle or Ellipse
	XVRectangle2D outAlignedRectangle;

	//Circle or Ring
	XVCircle2D    outAlignedCircle;

	//Segment
	XVSegment2D   outAlignedSegment;
}XVCreateRegionOut;

void XVCreateRegion(XVCreateRegionIn& CreateRegionIn, XVCreateRegionOut& CreateRegionOut);
