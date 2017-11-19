#ifndef WORKSPACE_TESTCLASS_H
#define WORKSPACE_TESTCLASS_H

class Matrix {
public:
	typedef struct {
		float x;
		float y;
	} Pointf;
	typedef struct {
		short x;
		short y;
	} Point16;
	typedef struct {
		int x;
		int y;
	} Point32;
	typedef struct {
		short left;
		short top;
		short right;
		short bottom;
	} Rect16;
	typedef struct {
		int left;
		int top;
		int right;
		int bottom;
	} Rect32;
	typedef struct {
		float left;
		float top;
		float right;
		float bottom;
	} Rectf;
public:
    static void LoadIdentity(float mat[4][4]);
    static void TranslateMatrix(float x, float y, float z, float iomat[4][4]);
    static void TranslateMatrix(float x, float y, float z, const float lhsm[4][4], float retmat[4][4]);
    static void ScaleMatrix(float x, float y, float z, float iomat[4][4]);
    static void ScaleMatrix(float x, float y, float z, const float lhsm[4][4], float retmat[4][4]);
    static void RotateMatrix(int angle, float x, float y, float z, float iomat[4][4]);
    static void RotateMatrix(int angle, float x, float y, float z, const float lhsm[4][4], float retmat[4][4]);
    static void MultiMatrix( const float lhsm[4][4], float iomat[4][4]);
    static void MultiMatrix( const float lhs[4][4], const float rhs[4][4], float retmat[4][4]);

	static void ConvRect(const Rect16 &SrcRect, const float mat[4][4], Rect16 &DstRect);
	static void ConvRect(const Rectf &SrcRect, const float mat[4][4], Rectf &DstRect);
	static void ConvVertex(int nPoint, const Point16 *pSrcVertex, const float mat[4][4], Point16 *pDstVertex);
	static void ConvVertex(int nPoint, const Point32 *pSrcVertex, const float mat[4][4], Point32 *pDstVertex);
	static void ConvVertex(int nPoint, const Pointf *pSrcVertex, const float mat[4][4], Pointf *pDstVertex);
};

#endif //WORKSPACE_TESTCLASS_H
