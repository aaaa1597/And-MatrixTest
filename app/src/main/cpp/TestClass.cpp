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
    /* x軸回転 */
    float xs = std::sin(angle*PI/180) * x;
    float xc = std::cos(angle*PI/180) * x;
    const float xrotateM[4][4] = {
        1,  0,   0, 0,
        0, xc, -xs, 0,
        0, xs,  xc, 0,
        0,  0,   0, 1,
    };
    Matrix::MultiMatrix(xrotateM, lhsm, retmat);

    /* y軸回転 */
    float ys = std::sin(angle*PI/180) * y;
    float yc = std::cos(angle*PI/180) * y;
    const float yrotateM[4][4] = {
       yc,  0, ys, 0,
        0,  1,  0, 0,
      -ys,  0, yc, 0,
        0,  0,  0, 1,
    };
    Matrix::MultiMatrix(yrotateM, retmat);

    /* z軸回転 */
    float zs = std::sin(angle*PI/180) * z;
    float zc = std::cos(angle*PI/180) * z;
    const float zrotateM[4][4] = {
        zc, -zs, 0, 0,
        zs,  zc, 0, 0,
         0,  0,  1, 0,
         0,  0,  0, 1,
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
	__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa m [0][0](%f) [0][1](%f) [0][2](%f) [0][3](%f)", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
	__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa m [1][0](%f) [1][1](%f) [1][2](%f) [1][3](%f)", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
	__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa m [2][0](%f) [2][1](%f) [2][2](%f) [2][3](%f)", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
	__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa m [3][0](%f) [3][1](%f) [3][2](%f) [3][3](%f)", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	for(size_t lpct = 0; lpct < nPoint; lpct++) {
		pDstVertex[lpct].x = pSrcVertex[lpct].x*mat[0][0] + pSrcVertex[lpct].y*mat[0][1] + mat[0][3];
		pDstVertex[lpct].y = pSrcVertex[lpct].x*mat[1][0] + pSrcVertex[lpct].y*mat[1][1] + mat[1][3];
		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa Ans(%6d) = pSrcVertex[%d].x(%5d)*mat[0][0](%f) + pSrcVertex[%d].y(%5d)*mat[0][1](%f) + [0][3](%f)", pDstVertex[lpct].x, lpct, pSrcVertex[lpct].x, mat[0][0], lpct, pSrcVertex[lpct].y, mat[0][1], mat[0][3]);
		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa Ans(%6d) = pSrcVertex[%d].x(%5d)*mat[1][0](%f) + pSrcVertex[%d].y(%5d)*mat[1][1](%f) + [1][3](%f)", pDstVertex[lpct].y, lpct, pSrcVertex[lpct].x, mat[1][0], lpct, pSrcVertex[lpct].y, mat[1][1], mat[1][3]);
		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa Ans(%6d) = pSrcVertex[%d].x*mat[0][0](%f) + pSrcVertex[%d].y*mat[0][1](%f) + [0][3](%f)", pDstVertex[lpct].x, lpct, pSrcVertex[lpct].x*mat[0][0], lpct, pSrcVertex[lpct].y*mat[0][1], mat[0][3]);
		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa Ans(%6d) = pSrcVertex[%d].x*mat[1][0](%f) + pSrcVertex[%d].y*mat[1][1](%f) + [1][3](%f)", pDstVertex[lpct].x, lpct, pSrcVertex[lpct].x*mat[1][0], lpct, pSrcVertex[lpct].y*mat[1][1], mat[1][3]);
		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa");
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
