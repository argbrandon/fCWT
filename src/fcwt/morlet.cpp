#include "morlet.h"

fcwt::Morlet::Morlet(const float bandwidth): fb(bandwidth) {
    fb2 = 2.0f * fb * fb;
    ifb = 1.0f / fb;
    imag_frequency = false;
    doublesided = false;
}

int fcwt::Morlet::getSupport(const float scale) const noexcept {
    return static_cast<int>(scale * 5.0f);
}

void fcwt::Morlet::generate(const int size) noexcept {
    // Frequency domain, because we only need size. Default scale is always 2
    width = size;
    const float toradians = 2 * PI / static_cast<float>(size);
    const float norm = CONST * sqrtPI_2;
    mother.resize(width);
    for(int w = 0; w < width; w++) {
        float tmp1 = (2.0f * (static_cast<float>(w) * toradians) - 5.0f);
        tmp1 = -(tmp1 * tmp1) / 2;
        float tmp2 = (2.0f * (static_cast<float>(w) * toradians) + 5.0f);
        tmp2 = -(tmp2 * tmp2) / 2;
        mother[w] = norm * (std::exp(tmp1) + std::exp(tmp2));
    }
}

void fcwt::Morlet::generate(std::vector<std::complex<float>>& pwav, const int size, const float scale) noexcept {
    // Time domain because we know size from scale
    width = getSupport(scale);
    std::vector<float> res(width * 2 + 1, 0);

    const float norm = static_cast<float>(size) * CONST;

    //cout << scale << " [";
    for(int t = 0; t < width * 2 + 1; t++) {
        const float tmp1 = static_cast<float>(t - width) / scale;
        const float tmp2 = std::exp(-tmp1 * tmp1 / 2.0f);
        pwav[t].real(norm * tmp2 * std::cos(5.0f * tmp1) / scale);
        pwav[t].imag(0.0f);
        //cout << real[t]*real[t]+imag[t]*imag[t] << ",";
    }

    //cout << "]" << endl;
}

void fcwt::Morlet::getWavelet(const float scale, std::vector<std::complex<float>>& pwav, const int pn) noexcept {
    generate(pwav, pn, scale);
}
