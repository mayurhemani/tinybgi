#include "graphics.hpp"

struct cplx {
    double real;
    double imag;
    cplx():real(0), imag(0) {}
    cplx(double r, double i):real(r), imag(i) {}
    double operator()(void) const {
        return (real * real + imag * imag);
    }
};

// This function determines the polynomial Z^2 + C
cplx evaluate(cplx const& z, cplx const& c)
{
    cplx res;
    res.real = z.real * z.real - z.imag * z.imag + c.real;
    res.imag = 2 * z.real * z.imag + c.imag;
    return res;
}

// typedef std::vector<cv::Vec3f> colors_v;
// typedef std::vector<size_t> members_t;
// typedef std::vector<members_t> members_v;


// inline float distance(cv::Vec3b const& c1, cv::Vec3b const& c2) {
//     return ( 
//             (c1[0] - c2[0]) * (c1[0] - c2[0]) +
//             (c1[1] - c2[1]) * (c1[1] - c2[1]) +
//             (c1[2] - c2[2]) * (c1[2] - c2[2]) 
//         );
// }

// inline size_t closest_idx(colors_v const& colors, cv::Vec3f c) {
//     return static_cast<size_t>(
//             std::min_element(std::begin(colors), std::end(colors), [c](cv::Vec3f d) {
//                 return distance(d, c);
//             }) - std::begin(colors));
// }

// void assign(colors_v const& palette, cv::Mat const& img, members_v& members) {
//     // clear membershup
//     std::for_each(std::beging(members), std::end(members), [](members_t& v) { v.clear(); });

//     // assign membership
//     for (auto i = 0; i < img.rows; ++i)
//         for (auto j = 0; j < img.cols; ++j)
//         {
//             auto pos = i * img.cols + j;
//             members[ closest_idx(palette, img.at<cv::Vec3f>(i, j)) ].push_back( pos );
//         }
// }

// cv::Vec3f cluster_mean(cv::Mat const& img, members_t const& m) {

// }


// cv::Mat kmeans(cv::Mat const& rgbimg, int k) {
//     cv::Mat lab;
//     cv::cvtColor(rgbimg, lab, cv::COLOR_BGR2LAB);
//     cv::Mat img;
//     labimg.convertTo(img, CV_32FC3);


//     return pal;
// }


struct colorpicker_t {
    colorpicker_t(size_t len):
    clr(len) {
        std::srand(std::time(nullptr));

        rgb_t red = RGB(255, 0, 0);
        rgb_t yellow = RGB(255, 255, 0);

        auto rand_interp = [red, yellow]() {
            double rnd = (std::rand() % 1000) / 1000.0;
            uint8_t r = static_cast<unsigned char>(red.r * (1. - rnd) + yellow.r * rnd);
            rnd = (std::rand() % 1000) / 1000.0;
            uint8_t g = static_cast<unsigned char>(red.g * (1. - rnd) + yellow.g * rnd);
            rnd = (std::rand() % 1000) / 1000.0;
            uint8_t b = static_cast<unsigned char>(red.b * (1. - rnd) + yellow.b * rnd);
            return RGB(r, g, b);
        };

        for (int i = 0; i < len; ++i) {
            clr[i] = rand_interp();
        }
     }

    inline rgb_t get(short cnt) const {
        return clr[cnt%clr.size()];
    }

    std::vector<rgb_t> clr;
};


rgb_t get_pix_color(long x, long y, colorpicker_t const& clr)
{
    double scaled_x = (x - 320.0)/320.0; // screen resolution's only 640x480
    double scaled_y = (y - 240.0)/240.0;
    cplx p(scaled_x, scaled_y);
    cplx z;
    short cnt = 0;
    while (z() < 4 && cnt < 30) {
        z = evaluate(z, p);
        cnt++;
    }
    return clr.get(cnt%64); // 'cause there'll only 16 colors (duh!!)
}


int main(int argc, char* argv[]) {

    tinybgi::initgraph(nullptr, nullptr);
    colorpicker_t clr(64);

    for (short x = 0; x < 640; ++x) {
        for (short y = 0; y < 480; ++y) {
            tinybgi::putpixel(x, y, get_pix_color(x, y, clr));
        }
    }

    tinybgi::closegraph();
    tinybgi::save("mandelbrot.png");
    return 0;
}