/*!
 * \file BlobExtractor_Processor.cpp
 * \brief Declaration of an example class,
 * responsible for image processing.
 * - methods definitions
 * \author tkornuta
 * \date 11.03.2008
 */

#include <memory>
#include <string>
#include <iostream>

#include "BlobExtractor_Processor.hpp"
#include "ComponentLabeling.hpp"

#include "Logger.hpp"
#include "Timer.hpp"
#include "BlobOperators.hpp"

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Processors {
namespace BlobExtractor {

BlobExtractor_Processor::BlobExtractor_Processor(const std::string & name) : Base::Component(name) {
	LOG(TRACE)<<"Hello BlobExtractor_Processor\n";
}

BlobExtractor_Processor::~BlobExtractor_Processor() {
	LOG(TRACE)<<"Good bye BlobExtractor_Processor\n";
}

bool BlobExtractor_Processor::onInit() {
	LOG(TRACE) << "BlobExtractor_Processor::initialize\n";

	newBlobs = registerEvent("newBlobs");

	newImage = registerEvent("newImage");

	h_onNewImage.setup(this, &BlobExtractor_Processor::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	registerStream("out_blobs", &out_blobs);

	bkg_color = 0;

	return true;
}

bool BlobExtractor_Processor::onFinish() {
	LOG(TRACE) << "BlobExtractor_Processor::finish\n";

	return true;
}

bool BlobExtractor_Processor::onStep()
{
	LOG(TRACE) << "BlobExtractor_Processor::step\n";
	return true;
}

bool BlobExtractor_Processor::onStop()
{
	return true;
}

bool BlobExtractor_Processor::onStart()
{
	return true;
}

void BlobExtractor_Processor::onNewImage() {
	LOG(TRACE) << "BlobExtractor_Processor::onNewImage() called!\n";

	Common::Timer timer;
	timer.restart();

	cv::Mat in = in_img.read();

	IplImage * img = &IplImage(in);
	cv::Mat out = cv::Mat::zeros(in.size(), CV_8UC3);

	Types::Blobs::Blob_vector res;
	bool success;

	try
	{
		success = ComponentLabeling( img, NULL, bkg_color, res );
	}
	catch(...)
	{
		success = false;
		LOG(WARNING) << "blob find error\n";
	}

	if( !success ) {
		LOG(ERROR) << "Blob find error\n";
	} else {
		Types::Blobs::BlobResult result(res);

		result.Filter( result, B_EXCLUDE, Types::Blobs::BlobGetArea(), B_LESS, 100 );

		//out_blobs.write(result);

		//newBlobs->raise();

		result.draw(&IplImage(out), CV_RGB(255, 0, 0), 0, 0);
		out_img.write(out);
		newImage->raise();
	}

	LOG(INFO) << "Blobing took " << timer.elapsed() << " seconds\n";
}

}//: namespace BlobExtractor
}//: namespace Processors