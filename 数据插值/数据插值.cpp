// 数据插值.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{
	//插值数据文件输入模块
	//输入已知x
	ifstream ifs;
	ifs.open("x.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	char buf[1024] = { 0 };
	double x[15] = { 0 };
	for (int i = 0;ifs >> buf;i++)
	{
		string a;
		a = buf;
		x[i] = stod(a);
	}
	ifs.close();
	//输入已知fx
	ifs.open("fx.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	char buf1[1024] = { 0 };
	double fx[15] = { 0 };
	for (int i = 0;ifs >> buf1;i++)
	{
		string a;
		a = buf1;
		fx[i] = stod(a);
	}
	ifs.close();
	//输入待求x
	ifs.open("xIn.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	char buf2[1024] = { 0 };
	double xIn[15] = { 0 };
	for (int i = 0;ifs >> buf2;i++)
	{
		string a;
		a = buf2;
		xIn[i] = stod(a);
	}
	ifs.close();
	//拉格朗日计算模块
	double laFx[15] = { 0 };
	for (int k = 0;k <= 4;k++)
	{
		double l[5] = { 1,1,1,1,1 };
		for (int i = 0;i <= 4;i++)
		{
			for (int j = 0;j <= 4 ;j++)
			{
				if (j != i)
				{
					l[i] *= ((xIn[k] - x[j]) / (x[i] - x[j]));
				}
			}
			laFx[k] += l[i] * fx[i];
		}
		//cout << laFx[k] << endl;
	}
	ofstream ofs;
	ofs.open("laFx.txt", ios::in);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	for (int i = 0;i <= 4;i++)
	{
		ofs << laFx[i]<<" ";
	}
	ofs.close();

	//牛顿插值计算模块
	double newFx[5] = { 0 };
	double cs[5] = { 0 };

	//求差商
	for (int n = 0;n <= 0;n++)
	{
		for (int k = 0;k <= 4;k++)
		{
			for (int i = 0;i <= k;i++)
			{
				double cha[5] = { 1,1,1,1,1 };
				for (int j = 0;j <= k;j++)
					if (j != i)
					{
						cha[i] *= (x[i] - x[j]);
					}
				//cout << cha[i] << endl;
				cs[k] += (fx[i] / (cha[i]));
			}
			//cout << cs[k] << endl;
		}
	}

	//求牛顿插值
	for (int i = 0;i <= 4;i++)
	{
		newFx[i] = cs[0]
			+ cs[1] * (xIn[i] - x[0])
			+ cs[2] * (xIn[i] - x[0]) * (xIn[i] - x[1])
			+ cs[3] * (xIn[i] - x[0]) * (xIn[i] - x[1]) * (xIn[i] - x[2])
			+ cs[4] * (xIn[i] - x[0]) * (xIn[i] - x[1]) * (xIn[i] - x[2]) * (xIn[i] - x[3]);
		//cout << newFx[i] << endl;
	}
	ofs.open("newFx.txt", ios::in);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	for (int i = 0;i <= 4;i++)
	{
		ofs << newFx[i]<<" ";
	}
	ofs.close();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
