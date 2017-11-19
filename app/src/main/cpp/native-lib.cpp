#include <jni.h>
#include <string>
#include <android/log.h>
#include "TestClass.h"

#define N 4

void matrixmultiply(float a[N][N],float b[N][N],float c[N][N]);
void matrixmultiply(float a[N][N],float b[N][N],float c[N][N])
//void matrixmultiply(double a[N][N],double b[N][N],double c[N][N]);
//void matrixmultiply(double a[N][N],double b[N][N],double c[N][N])
{
	int i,j,k;

//受け取った２つの行列の掛け算を行う。
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			c[i][j] = 0;
			for(k=0;k<N;k++) {
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}

	float dumyret[4][4] = {0};
	Matrix::MultiMatrix((const float(*)[4])a, (const float(*)[4])b, dumyret);
	return;
}

extern "C" JNIEXPORT jstring JNICALL Java_com_test_aaa_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */) {
	int i,j;
	float A[N][N],B[N][N],C[N][N];
//	double A[N][N],B[N][N],C[N][N];

	//計算を行う行列の値を格納する。
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			A[i][j]=B[i][j]=i*N+j;
			B[i][j]++;
			C[i][j]=0.0;
		}
	}

	matrixmultiply(A,B,C);          //関数を呼び出し行列の掛け算を行う。
	matrixmultiply(B,A,C);          //関数を呼び出し行列の掛け算を行う。

	//結果を表示する。
	for(i=0;i<N;i++) {
		char logaaa[256] = {0};
		for(j=0;j<N;j++) {
			sprintf(logaaa, "%f ",C[i][j]);
		}
		sprintf(logaaa, "\n");
		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "%s", logaaa);
	}
//	結果は次のようになる。
//	5.000000 8.000000 11.000000
//	8.000000 14.000000 20.000000
//	11.000000 20.000000 29.000000

	float fujim[4][4] = {0};
    Matrix::LoadIdentity(fujim);
	Matrix::TranslateMatrix(-100, -100, 0, fujim);
	Matrix::ScaleMatrix(10, 10, 0, fujim);
	Matrix::TranslateMatrix(100, 100, 0, fujim);

	Matrix::Point32 srctestval[6] = {{0,0},{4096,4096},{6144,6144},{100,100},{8192,8192},{12288,12288}};
//  Matrix::Point16 srctestval[4] = {{0,0},{1,1},{2,2},{3,3}};
    Matrix::Point32 dsttestval[6] = {0};

	Matrix::ConvVertex(6, srctestval, (const float(*)[4])fujim, dsttestval);

//	Matrix::ConvVertex(4, dsttestval, (const float(*)[4])scaleM, dsttestval);
//	Matrix::ConvVertex(4, dsttestval, (const float(*)[4])rtransM, dsttestval);


    float mat[4][4] = {0};
    /* Std4096→Dot */
    Matrix::LoadIdentity(mat);                             /* 行列初期化 */
    Matrix::TranslateMatrix(1280/2, 720/2, 0, mat);        /* 移動 */
    Matrix::ScaleMatrix(1, -1, 1, mat);                    /* y軸反転 */
    Matrix::ScaleMatrix(1.1, 1, 0, mat);                   /* アスペクト比 */
    Matrix::RotateMatrix(360,0,0,1,mat);                   /* 回転 */
    Matrix::ScaleMatrix(800/4096.f, 650/4096.f, 1, mat);   /* 正規化4096 */
    Matrix::TranslateMatrix(-4096, -4096, 0, mat);         /* 移動 */
    for(int lpcti = 0; lpcti < 4; lpcti++) {
        for(int lpctj = 0; lpctj < 4; lpctj++) {
            __android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa [%d][%d]=%f", lpcti, lpctj,  mat[lpcti][lpctj]);
        }
    }

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

