#include <iostream>
#include <cmath>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <../fparser.hh>
#include <vector>
#include <complex>
#include <math.h>
#define _USE_MATH_DEFINES

int main()
{
	const int x0 = 0, y0 = 0, r = 1;
	const double pi = 4 * atan(1), dt = 0.05;
	bool success;
	std::string function;
	std::vector<double>xs;
	std::vector<double>ys;

	std::cout << "f(z)=";
	std::cin >> function;
	FunctionParser_cd fp;
	fp.Parse(function, "z");
	for (double t = pi * (-1 / 4); t <= pi * (7 / 4); t += dt) {
		if (t <= pi * (1 / 4))
		{
			std::complex<double>z = { 1, tan(t) };
			std::complex<double>f = fp.Eval(&z);
			xs.push_back(f.real());
			ys.push_back(f.imag());
		}
		if (t > pi * (1 / 4) && t <= pi * (3 / 4)) {
			std::complex<double>z = { 1 / tan(t), 1 };
			std::complex<double>f = fp.Eval(&z);
			xs.push_back(f.real());
			ys.push_back(f.imag());
		}
		if (t > pi * (3 / 4) && t <= pi * (5 / 4)) {
			std::complex<double>z = { -1, -tan(t) };
			std::complex<double>f = fp.Eval(&z);
			xs.push_back(f.real());
			ys.push_back(f.imag());
		}
		if (t > pi * (5 / 4))
		{
			std::complex<double>z = { -1 / tan(t), -1 };
			std::complex<double>f = fp.Eval(&z);
			xs.push_back(f.real());
			ys.push_back(f.imag());
		}
	}

	StringReference* errorMessage = new StringReference();
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;
	series->ys = &ys;
	series->linearInterpolation = true;
	series->lineType = toVector(L"solid");
	series->lineThickness = 2;
	series->color = GetGray(1);

	ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 600;
	settings->autoBoundaries = true;
	settings->autoPadding = true;

	settings->scatterPlotSeries->push_back(series);

	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "main.png");
	DeleteImage(imageReference->image);

	return 0;
}