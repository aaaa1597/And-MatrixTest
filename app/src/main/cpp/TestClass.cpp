#include <cmath>
#include <string.h>
#include <android/log.h>
#include "TestClass.h"

void Matrix::LoadIdentity(float mat[4][4]) {
	memset(mat, 0x00, sizeof(float[4][4]));
	mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1.0f;
	return;
}

void Matrix::TranslateMatrix(float x, float y, float z, float iomat[4][4]) {
	const float lhs[4][4] = {
		iomat[0][0],iomat[0][1],iomat[0][2],iomat[0][3],
		iomat[1][0],iomat[1][1],iomat[1][2],iomat[1][3],
		iomat[2][0],iomat[2][1],iomat[2][2],iomat[2][3],
		iomat[3][0],iomat[3][1],iomat[3][2],iomat[3][3],
	};
	Matrix::TranslateMatrix(x, y, z, lhs, iomat);
	return;
}

void Matrix::TranslateMatrix(float x, float y, float z, const float lhsm[4][4], float retmat[4][4]) {
	const float translateM[4][4] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1,
	};
	Matrix::MultiMatrix(translateM, lhsm, retmat);
	return;
}

void Matrix::ScaleMatrix(float x, float y, float z, float iomat[4][4]) {
	const float lhsm[4][4] = {
		iomat[0][0],iomat[0][1],iomat[0][2],iomat[0][3],
		iomat[1][0],iomat[1][1],iomat[1][2],iomat[1][3],
		iomat[2][0],iomat[2][1],iomat[2][2],iomat[2][3],
		iomat[3][0],iomat[3][1],iomat[3][2],iomat[3][3],
	};
	Matrix::ScaleMatrix(x, y, z, lhsm, iomat);
	return;
}

void Matrix::ScaleMatrix(float x, float y, float z, const float lhsm[4][4], float retmat[4][4]) {
	const float scaleM[4][4] = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1,
	};
	Matrix::MultiMatrix(scaleM, lhsm, retmat);
	return;
}

void Matrix::RotateMatrix(int angle, float x, float y, float z, float iomat[4][4]) {
	const float lhs[4][4] = {
		iomat[0][0],iomat[0][1],iomat[0][2],iomat[0][3],
		iomat[1][0],iomat[1][1],iomat[1][2],iomat[1][3],
		iomat[2][0],iomat[2][1],iomat[2][2],iomat[2][3],
		iomat[3][0],iomat[3][1],iomat[3][2],iomat[3][3],
	};
	Matrix::RotateMatrix(angle, x, y, z, lhs, iomat);
	return;
}

#define PI 3.141592653589793
void Matrix::RotateMatrix(int angle, float x, float y, float z, const float lhsm[4][4], float retmat[4][4]) {
	double theta = angle*PI/180;
	/* x軸回転 */
	float sx = std::sin(theta*x);
	float cx = std::cos(theta*x);
	const float xrotateM[4][4] = {
		1,  0,   0, 0,
		0, cx, -sx, 0,
		0, sx,  cx, 0,
		0,  0,   0, 1,
	};
	Matrix::MultiMatrix(xrotateM, lhsm, retmat);

	/* y軸回転 */
	float sy = std::sin(theta*y);
	float cy = std::cos(theta*y);
	const float yrotateM[4][4] = {
		 cy,  0, sy, 0,
		  0,  1,  0, 0,
		-sy,  0, cy, 0,
		  0,  0,  0, 1,
	};
	Matrix::MultiMatrix(yrotateM, retmat);

	/* z軸回転 */
	float sz = std::sin(theta*z);
	float cz = std::cos(theta*z);
	const float zrotateM[4][4] = {
		cz, -sz, 0, 0,
	    sz,  cz, 0, 0,
		 0,   0, 1, 0,
		 0,   0, 0, 1,
	};
	Matrix::MultiMatrix(zrotateM, retmat);
	return;
}

void Matrix::MultiMatrix( const float lhsm[4][4], float iomat[4][4]) {
	const float rhsm[4][4] = {
		iomat[0][0],iomat[0][1],iomat[0][2],iomat[0][3],
		iomat[1][0],iomat[1][1],iomat[1][2],iomat[1][3],
		iomat[2][0],iomat[2][1],iomat[2][2],iomat[2][3],
		iomat[3][0],iomat[3][1],iomat[3][2],iomat[3][3],
	};
	Matrix::MultiMatrix(lhsm, rhsm, iomat);
	return;
}

void Matrix::MultiMatrix( const float lhs[4][4], const float rhs[4][4], float retmat[4][4]) {
    retmat[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
    retmat[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
    retmat[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
    retmat[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3];

    retmat[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
    retmat[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
    retmat[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
    retmat[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3];

    retmat[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
    retmat[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
    retmat[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];
    retmat[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3] + lhs[2][3]*rhs[3][3];

    retmat[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0];
    retmat[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1];
    retmat[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2] + lhs[3][3]*rhs[3][2];
    retmat[3][3] = lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3] + lhs[3][2]*rhs[2][3] + lhs[3][3]*rhs[3][3];

	return;
}

void Matrix::ConvRect(const Rect16 &SrcRect, const float mat[4][4], Rect16 &DstRect) {
	const Point16 SrcVertex[4] = {{SrcRect.left, SrcRect.top},{SrcRect.right, SrcRect.top},{SrcRect.right, SrcRect.bottom},{SrcRect.left, SrcRect.bottom}};
	Point16 DstVertex[4] = {0};
	Matrix::ConvVertex(4, SrcVertex, mat, DstVertex);
	DstRect.left	= DstVertex[0].x;
	DstRect.right	= DstVertex[1].x;
	DstRect.top		= DstVertex[0].y;
	DstRect.bottom	= DstVertex[2].y;
	return;
}

void Matrix::ConvRect(const Rectf &SrcRect, const float mat[4][4], Rectf &DstRect) {
	const Pointf SrcVertex[4] = {{SrcRect.left, SrcRect.top},{SrcRect.right, SrcRect.top},{SrcRect.right, SrcRect.bottom},{SrcRect.left, SrcRect.bottom}};
	Pointf DstVertex[4] = {0};
	Matrix::ConvVertex(4, SrcVertex, mat, DstVertex);
	DstRect.left	= DstVertex[0].x;
	DstRect.right	= DstVertex[1].x;
	DstRect.top		= DstVertex[0].y;
	DstRect.bottom	= DstVertex[2].y;
	return;
}

void Matrix::ConvVertex(int nPoint, const Point16 *pSrcVertex, const float mat[4][4], Point16 *pDstVertex) {
	for(size_t lpct = 0; lpct < nPoint; lpct++) {
		pDstVertex[lpct].x = pSrcVertex[lpct].x*mat[0][0] + pSrcVertex[lpct].y*mat[0][1] + mat[0][3];
		pDstVertex[lpct].y = pSrcVertex[lpct].x*mat[1][0] + pSrcVertex[lpct].y*mat[1][1] + mat[1][3];
	}
	return;
}

void Matrix::ConvVertex(int nPoint, const Point32 *pSrcVertex, const float mat[4][4], Point32 *pDstVertex) {
	for(size_t lpct = 0; lpct < nPoint; lpct++) {
		pDstVertex[lpct].x = pSrcVertex[lpct].x*mat[0][0] + pSrcVertex[lpct].y*mat[0][1] + mat[0][3];
		pDstVertex[lpct].y = pSrcVertex[lpct].x*mat[1][0] + pSrcVertex[lpct].y*mat[1][1] + mat[1][3];
	}
	return;
}

void Matrix::ConvVertex(int nPoint, const Pointf *pSrcVertex, const float mat[4][4], Pointf *pDstVertex) {
	for(size_t lpct = 0; lpct < nPoint; lpct++) {
		pDstVertex[lpct].x = pSrcVertex[lpct].x*mat[0][0] + pSrcVertex[lpct].y*mat[0][1] + mat[0][3];
		pDstVertex[lpct].y = pSrcVertex[lpct].x*mat[1][0] + pSrcVertex[lpct].y*mat[1][1] + mat[1][3];
	}
	return;
}
