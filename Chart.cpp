/*************************************************************************
**	Name:  Troy Jones
**	Date:  8/28/16
**	Class:  CSCI-211
**	Program:  Chart (Program 1)
*************************************************************************/
//#include "Chart.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

class Chart
{
public:
	Chart();
	const static int MAX = 100;
	void buildChart();
	void getData(int);
private:
	int height;
	int values[MAX];
	int width;
	int findLargestValue(int[], int);
};

Chart::Chart()
{
	height = 0;
	width = -1;
}

void Chart::buildChart()
{
	height = findLargestValue(values, width);	// finds largest value in array

	for (int i = height; i > 0; i--)
	{
		for (int j = 0; j < (width + 1); j++)
		{
			if (values[j] >= i)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
}

int Chart::findLargestValue(int arr[], int size)
{
	if (size == -1)
		return height;
	else
	{
		if (arr[size] > height)
		{
			height = arr[size];
			findLargestValue(arr, (--size));
		}
		else
			findLargestValue(arr, (--size));
	}
}

void Chart::getData(int num)
{
	if (num != 0)
	{
		width++;
		values[width] = num;
	}
}

int main()
{
	Chart chart;
	int input = -1;

	// retrieves data and stores in array
	while (input != 0 && input < chart.MAX)
	{
		cin >> input;
		chart.getData(input);
	}

	chart.buildChart();

	return 0;
}