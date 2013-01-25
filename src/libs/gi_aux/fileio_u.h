#ifndef _FILE_IO_H_
#define _FILE_IO_H_

void save(const image<spectrum>& img, const string& filename, const real& s) {
    int w = img.width(), h = img.height();

	FILE* f = fopen(filename.c_str(), "wt");
	
	fprintf(f, "P3\n\n");
    fprintf(f, "%d %d\n", w, h);
	fprintf(f, "255\n");

    for(int j = 0; j < h; j ++) {
        for(int i = 0; i < w; i ++) {
            int red = min(255, (int)(255 * pow(img.at(i,h-1-j).r * s,1/2.2)));
            int green = min(255, (int)(255 * pow(img.at(i,h-1-j).g * s,1/2.2)));
            int blue = min(255, (int)(255 * pow(img.at(i,h-1-j).b * s,1/2.2)));
			fprintf(f, "%d %d %d\n", red, green, blue);
		}
	}

	fclose(f);
}

void save(const image<spectrum>& img, const string& filename) {
    save(img,filename,0.18 / averageCmp(average(img))); // average is middle gray
}

#endif // _FILE_IO_H_