/*
 * Matcher.cpp
 *
 *  Created on: 15/06/2015
 *      Author: pablito
 */

#include "Matcher.h"

namespace opencv {

Matcher::Matcher() {
	// TODO Auto-generated constructor stub
}


Matcher::~Matcher() {
	// TODO Auto-generated destructor stub
}

int Matcher::templateMatching(const std::string& pathProduct,cv::Mat &ref) {
	int counter = 0;
	cv::Mat gref;
	cv::cvtColor(ref, gref, CV_BGR2GRAY);
	try {
		utils::Directory dir(pathProduct);
		std::vector<std::string> fileNames = dir.getFileNames();
		std::vector<std::string>::iterator it = fileNames.begin();
		while (it != fileNames.end()) {
			cv::Mat tpl = cv::imread((*it));
			cv::Mat gtpl;
			cv::cvtColor(tpl, gtpl, CV_BGR2GRAY);
			cv::Mat res(ref.rows-tpl.rows+1, ref.cols-tpl.cols+1, CV_32FC1);
			cv::matchTemplate(gref, gtpl, res, CV_TM_CCOEFF_NORMED);
			cv::threshold(res, res, 0.9, 1., CV_THRESH_TOZERO);
			while (true) {
				double minval, maxval, threshold = 0.8;
			    cv::Point minloc, maxloc;
			    cv::minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);
			    if (maxval >= threshold) {
			            cv::rectangle(
			                ref,
			                maxloc,
			                cv::Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
			                CV_RGB(0,255,0), 2
			            );
			            cv::floodFill(res, maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));
			            counter++;
			        }
			        else
			            break;
			    }
		it++;
	}
} catch (std::exception& e) {
		std::cerr<<e.what()<<std::endl;
}
	return counter;
}

// parametro dirImagenCamara es la direccion a la imagen que contiene los objetos a detectar EJ: "./data/img/imagenCamara.png"
// parametro dirImagenesObjeto es un vector que contiene todas las imagenes de un objeto EJ: ("./data/img/coca1.png","./data/img/coca2.png",...)
// La funcion devuelve la cantidad de objetos encontrados en la imagen o, en caso de error, -1
int featureMatch(const std::string &dirImagenCamara,
                 const std::vector<std::string> &dirImagenesObjeto) {
  using namespace cv;
  using namespace std;

  const bool GRISES = false;
  const float FACTOR_CLUSTERING = 0.1;  //matches cuya distancia sean menores a este valor por el tamaño de la imagen seran agrupados
  const int CALIDAD_FEATURES = 800; // mientras mas alto, menos features tomara pero seran de mejor calidad
  const int MINIMA_DISTANCIA_MATCHES = 200;  // mientras mas chica mas parecidos deben ser los descriptors del match
  const int MULTIPLICADOR_DISTANCE_MATCHES = 8;

  Mat imagenCamara;
  if (!GRISES)
    imagenCamara = imread(dirImagenCamara);
  else
    imagenCamara = imread(dirImagenCamara, CV_LOAD_IMAGE_GRAYSCALE);
  if (imagenCamara.empty())
    return -1;

  vector<Mat> imgsObjeto;
  for (unsigned int i = 0; i < dirImagenesObjeto.size(); i++) {
    Mat img;
    if (!GRISES)
      img = imread(dirImagenesObjeto[i]);
    else
      img = imread(dirImagenesObjeto[i], CV_LOAD_IMAGE_GRAYSCALE);

    if (img.empty())
      return -1;
    else
      imgsObjeto.push_back(img);
  }

  Ptr<Feature2D> detector;
  detector = xfeatures2d::SIFT::create(CALIDAD_FEATURES);

  vector<vector<KeyPoint> > keypoints_object;
  vector<KeyPoint> keypoints_scene;

  detector->detect(imgsObjeto, keypoints_object);
  detector->detect(imagenCamara, keypoints_scene);

  vector<Mat> descriptors_object;
  Mat descriptors_scene;
  detector->compute(imgsObjeto, keypoints_object, descriptors_object);
  detector->compute(imagenCamara, keypoints_scene, descriptors_scene);

  FlannBasedMatcher matcher;
  //BFMatcher matcher(NORM_L2);
  std::vector<DMatch> matches;

  matcher.add(descriptors_object);

  matcher.match(descriptors_scene, matches);

  double maxDist = 0;
  double minDist = MINIMA_DISTANCIA_MATCHES;

  for (unsigned int i = 0; i < matches.size(); i++) {
    double dist = matches[i].distance;
    if (dist < minDist)
      minDist = dist;
    if (dist > maxDist)
      maxDist = dist;
  }

  std::vector<DMatch> buenosMatches;

  for (unsigned int i = 0; i < matches.size(); i++) {
    if (matches[i].distance < MULTIPLICADOR_DISTANCE_MATCHES * minDist) {
      buenosMatches.push_back(matches[i]);
    }
  }

  int total = buenosMatches.size();


  // no cuento los matches que estan cerca uno de otros ya que pertenecen al mismo objeto :
  int tamanioImgCamara = (imagenCamara.rows + imagenCamara.cols) / 2;

  std::vector<bool> validos(total, true);

  for (unsigned int i = 0; i < buenosMatches.size(); i++) {
    if (validos[i]) {
      Point2f a = keypoints_scene[buenosMatches[i].queryIdx].pt;

      for (unsigned int j = 0; j < i; j++) {
        if (validos[j]) {
          Point2f b = keypoints_scene[buenosMatches[j].queryIdx].pt;
          double dist = cv::norm(a - b);
          if (dist < tamanioImgCamara * FACTOR_CLUSTERING) {
            total--;
            validos[j] = false;
          }
        }
      }

    }
  }
  return total;
}

} /* namespace opencv */
