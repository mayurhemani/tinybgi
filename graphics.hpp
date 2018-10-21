#ifndef TINY_BGI_H
#define TINY_BGI_H

#ifdef __APPLE_CC__
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#else
#include "opencv/cv.h"
#endif

#include <iostream>
#include <string>


struct rgb_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};



#define RGB(r, g, b) rgb_t{static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)}
#define WINWIDTH 640
#define WINHEIGHT 480


struct tinybgi {

  static void initgraph(int*, int*) {
    auto x = get();
    cv::namedWindow("tinybgi");
    cv::resizeWindow("tinybgi", WINHEIGHT, WINWIDTH);
    cv::imshow("tinybgi", x.img);
  }

  static void putpixel(int x, int y, rgb_t color) {
    auto t = get();
    if (x >= 0 && y >= 0 && x < WINWIDTH && y < WINHEIGHT) {
      t.img.at<cv::Vec3b>(y, x) = cv::Vec3b(color.b, color.g, color.r);
      //std::cout << color.b << " " << color.g << " " << color.r << "\n";
    }
    //cv::imshow("tinybgi", t.img);
    //cv::waitKey(1);
  }

  static void closegraph(int delay=0) {
    auto t = get();
    cv::imshow("tinybgi", t.img);
    cv::waitKey(delay);
  }

  static void setcolor(rgb_t color) {
    auto t = get();
    t.clr = cv::Scalar(color.r, color.g, color.b);
  }

  static void setfill(rgb_t color) {
    auto x = get();
    x.fill = cv::Scalar(color.r, color.g, color.b);
  }

  static void line(int x1, int y1, int x2, int y2) {
    auto x = get();
    cv::line(x.img, cv::Point(x1, y1), cv::Point(x2, y2), x.clr, 1);
  }

  static void rectangle(int left, int top, int right, int bottom) {
    auto x = get();
    cv::rectangle(x.img, cv::Point(left, top), cv::Point(right, bottom), x.fill, -1);
  }

  static void save(std::string const& fname) {
    auto x = get();
    cv::imwrite(fname, x.img);
  }

private:
    cv::Mat img;
    cv::Scalar clr;
    cv::Scalar fill;

    tinybgi():
    clr(0, 0, 0),
    fill(0, 0, 0)
    {
      img = cv::Mat(480, 640, CV_8UC3, cv::Scalar(0));
    }

    static tinybgi& get() {
      static tinybgi t;
      return t;
    }
};

#endif

