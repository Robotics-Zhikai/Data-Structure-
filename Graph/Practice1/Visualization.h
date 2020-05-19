#ifndef VISUALIZATION
#define VISUALIZATION

#include <algorithm>
#include <GL/glut.h>
#include <math.h>
#include <vector>
using namespace std;

//ģ��Buffer,�洢���Ƶĵ�
extern vector<double> GLplotPointsXData;
extern vector<double> GLplotPointsYData;
extern vector<double> GLplotPointsZData;
extern vector<float> GLplotPointsize;//��Ӧ�ĵ�Ĵ�С

//ģ��Buffer���洢���Ƶ�ֱ��
extern vector<double> GLplotLineXData;
extern vector<double> GLplotLineYData;
extern vector<double> GLplotLineZData;
extern vector<float> GLplotLineWidth;//��Ӧ��ֱ�ߵĿ��
extern vector<int> GLplotLineType;//�ߵ����� 

void OpenGLplot(void);
void CloseGLplot();

void AddBufferPoints(vector<Point> Points, float sizepoint);
void AddBufferLines(vector<Point> Points, float LineWidth);

#endif