#ifndef _IMAGE_H_
#define _IMAGE_H_

template<typename T>
struct image {
    image(int w, int h) : w(w), h(h), v(h*w) { }

    int width() const { return w; }
    int height() const { return h; }

    T& at(int i, int j) { return v[j*w+i]; }
    const T& at(int i, int j) const { return v[j*w+i]; }

private:
    int w, h;
    std::vector<T> v;
};

template<typename T>
inline T average(const image<T>& img) {
    T avg = T();
    for(int j = 0; j < img.width(); j ++) {
        for(int i = 0; i < img.width(); i ++) {
            avg = avg + img.at(i,j);
        }
    }
    return avg / (img.width() * img.height());
}

template<typename T>
inline T max(const image<T>& img) {
    T m = img.at(0,0);
    for(int j = 0; j < img.width(); j ++) {
        for(int i = 0; i < img.width(); i ++) {
            m = max(m, img.at(i,j));
        }
    }
    return m;
}

#endif
