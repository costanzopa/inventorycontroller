/*
 * Matcher.h
 *
 *  Created on: 15/06/2015
 *      Author: pablito
 */

#ifndef MATCHER_H_
#define MATCHER_H_
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/core/cvstd.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/ptr.inl.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "../common/Directory.h"
#include "../common/Constants.h"

namespace opencv {

class Matcher {
public:
	Matcher();
	~Matcher();
	int templateMatching(const std::string& productPath,cv::Mat &ref);
};

} /* namespace opencv */
#endif /* MATCHER_H_ */
