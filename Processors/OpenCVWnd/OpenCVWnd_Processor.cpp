/*!
 * \file RGBtoHSV_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-05-15
 */

#include <memory>
#include <string>
#include <iostream>

#include "OpenCVWnd_Processor.hpp"

namespace Processors {
namespace OpenCVWnd {

OpenCVWnd_Processor::OpenCVWnd_Processor() {
	cout<<"Hello RGBtoHSV_Processor\n";
}

OpenCVWnd_Processor::~OpenCVWnd_Processor() {
	cout<<"Good bye RGBtoHSV_Processor\n";
}

bool OpenCVWnd_Processor::initialize() {
	std::cout << "RGBtoHSV_Processor::initialize\n";

	h_onNewImage.setup(this, &OpenCVWnd_Processor::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	return true;
}

bool OpenCVWnd_Processor::finish() {
	std::cout << "RGBtoHSV_Processor::finish\n";

	return true;
}

int OpenCVWnd_Processor::step()
{
	cout<<"RGBtoHSV_Processor::step\n";
	return 0;
}

void OpenCVWnd_Processor::onNewImage() {
	imshow( props.title, in_img.read() );
	waitKey( 2 );
}


}//: namespace OpenCVWnd
}//: namespace Processors
