#include "graphics.hpp"
#include <string>

int main() {
  tinybgi::initgraph(nullptr, nullptr);

  typedef std::pair<int, int> point2D;
  typedef std::vector<point2D> pointVec;

  pointVec triangle(3);

  triangle[0] = std::make_pair(300, 20);
  triangle[1] = std::make_pair(0, 450);
  triangle[2] = std::make_pair(600, 450);

  point2D p(std::make_pair(140, 50));

  for (int i = 0; i < 15000; ++i) {
    short j = rand()  % 3;

    tinybgi::putpixel(p.first, p.second, RGB(205, p.first%255, 120));

    p = std::make_pair((triangle[j].first + p.first) / 2, (triangle[j].second + p.second) / 2);
  }

  tinybgi::closegraph();
  tinybgi::save(std::string("sierpinski.png"));
  return 0;
}