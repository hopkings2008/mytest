#include <png.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <qrencode.h>
#include <png.h>


typedef unsigned char ui8;
#define ASSERT_EX(cond, error_message) do { if (!(cond)) { std::cerr << error_message; exit(1);} } while(0)

#define INCHES_PER_METER (100.0/2.54)


static int casesensitive = 1;
static int eightbit = 0;
static int version = 0;
static int size = 3;
static int margin = -1;
static int dpi = 72;
static int micro = 0;
static QRecLevel level = QR_ECLEVEL_L;
static QRencodeMode hint = QR_MODE_8;
static unsigned char fg_color[4] = {0, 0, 0, 255};
static unsigned char bg_color[4] = {255, 255, 255, 255};

enum imageType {
	PNG_TYPE,
	PNG32_TYPE,
	EPS_TYPE,
	SVG_TYPE,
	XPM_TYPE,
	ANSI_TYPE,
	ANSI256_TYPE,
	ASCII_TYPE,
	ASCIIi_TYPE,
	UTF8_TYPE,
	ANSIUTF8_TYPE,
	UTF8i_TYPE,
	ANSIUTF8i_TYPE
};


static void PngWriteCallback(png_structp  png_ptr, png_bytep data, png_size_t length) {
    std::vector<ui8> *p = (std::vector<ui8>*)png_get_io_ptr(png_ptr);
    p->insert(p->end(), data, data + length);
}

struct TPngDestructor {
    png_struct *p;
    TPngDestructor(png_struct *p) : p(p)  {}
    ~TPngDestructor() { if (p) {  png_destroy_write_struct(&p, NULL); } }
};

void WritePngToMemory(size_t w, size_t h, const ui8 *dataRGBA, std::vector<ui8> *out) {
    out->clear();
    png_structp p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    ASSERT_EX(p, "png_create_write_struct() failed");
    TPngDestructor destroyPng(p);
    png_infop info_ptr = png_create_info_struct(p);
    ASSERT_EX(info_ptr, "png_create_info_struct() failed");
    ASSERT_EX(0 == setjmp(png_jmpbuf(p)), "setjmp(png_jmpbuf(p) failed");
    png_set_IHDR(p, info_ptr, w, h, 8,
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

    std::vector<ui8*> rows(h);
    for (size_t y = 0; y < h; ++y)
        rows[y] = (ui8*)dataRGBA + y * w * 4;
    png_set_rows(p, info_ptr, &rows[0]);
    png_set_write_fn(p, out, PngWriteCallback, NULL);
    png_write_png(p, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
}

static void fillRow(unsigned char *row, int num, const unsigned char color[])
{
	int i;

	for(i = 0; i < num; i++) {
		memcpy(row, color, 4);
		row += 4;
	}
}

static int writePNG(const QRcode *qrcode, std::vector<ui8> &out, enum imageType type)
{
	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette = NULL;
	png_byte alpha_values[2];
	unsigned char *row, *p, *q;
	int x, y, xx, yy, bit;
	int realwidth;

	realwidth = (qrcode->width + margin * 2) * size;
	if(type == PNG_TYPE) {
		row = (unsigned char *)malloc((realwidth + 7) / 8);
	} else if(type == PNG32_TYPE) {
		row = (unsigned char *)malloc(realwidth * 4);
	} else {
		fprintf(stderr, "Internal error.\n");
		exit(EXIT_FAILURE);
	}
	if(row == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG writer.\n");
		exit(EXIT_FAILURE);
	}

    png_set_write_fn(png_ptr, &out, PngWriteCallback, NULL);

	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG write.\n");
		exit(EXIT_FAILURE);
	}

	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fprintf(stderr, "Failed to write PNG image.\n");
		exit(EXIT_FAILURE);
	}

	if(type == PNG_TYPE) {
		palette = (png_colorp) malloc(sizeof(png_color) * 2);
		if(palette == NULL) {
			fprintf(stderr, "Failed to allocate memory.\n");
			exit(EXIT_FAILURE);
		}
		palette[0].red   = fg_color[0];
		palette[0].green = fg_color[1];
		palette[0].blue  = fg_color[2];
		palette[1].red   = bg_color[0];
		palette[1].green = bg_color[1];
		palette[1].blue  = bg_color[2];
		alpha_values[0] = fg_color[3];
		alpha_values[1] = bg_color[3];
		png_set_PLTE(png_ptr, info_ptr, palette, 2);
		png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);
	}

	//png_init_io(png_ptr, fp);
	if(type == PNG_TYPE) {
		png_set_IHDR(png_ptr, info_ptr,
				realwidth, realwidth,
				1,
				PNG_COLOR_TYPE_PALETTE,
				PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_DEFAULT,
				PNG_FILTER_TYPE_DEFAULT);
	} else {
		png_set_IHDR(png_ptr, info_ptr,
				realwidth, realwidth,
				8,
				PNG_COLOR_TYPE_RGB_ALPHA,
				PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_DEFAULT,
				PNG_FILTER_TYPE_DEFAULT);
	}
	png_set_pHYs(png_ptr, info_ptr,
			dpi * INCHES_PER_METER,
			dpi * INCHES_PER_METER,
			PNG_RESOLUTION_METER);
	png_write_info(png_ptr, info_ptr);

	if(type == PNG_TYPE) {
	/* top margin */
		memset(row, 0xff, (realwidth + 7) / 8);
		for(y = 0; y < margin * size; y++) {
			png_write_row(png_ptr, row);
		}

		/* data */
		p = qrcode->data;
		for(y = 0; y < qrcode->width; y++) {
			memset(row, 0xff, (realwidth + 7) / 8);
			q = row;
			q += margin * size / 8;
			bit = 7 - (margin * size % 8);
			for(x = 0; x < qrcode->width; x++) {
				for(xx = 0; xx < size; xx++) {
					*q ^= (*p & 1) << bit;
					bit--;
					if(bit < 0) {
						q++;
						bit = 7;
					}
				}
				p++;
			}
			for(yy = 0; yy < size; yy++) {
				png_write_row(png_ptr, row);
			}
		}
		/* bottom margin */
		memset(row, 0xff, (realwidth + 7) / 8);
		for(y = 0; y < margin * size; y++) {
			png_write_row(png_ptr, row);
		}
	} else {
	/* top margin */
		fillRow(row, realwidth, bg_color);
		for(y = 0; y < margin * size; y++) {
			png_write_row(png_ptr, row);
		}

		/* data */
		p = qrcode->data;
		for(y = 0; y < qrcode->width; y++) {
			fillRow(row, realwidth, bg_color);
			for(x = 0; x < qrcode->width; x++) {
				for(xx = 0; xx < size; xx++) {
					if(*p & 1) {
						memcpy(&row[((margin + x) * size + xx) * 4], fg_color, 4);
					}
				}
				p++;
			}
			for(yy = 0; yy < size; yy++) {
				png_write_row(png_ptr, row);
			}
		}
		/* bottom margin */
		fillRow(row, realwidth, bg_color);
		for(y = 0; y < margin * size; y++) {
			png_write_row(png_ptr, row);
		}
	}

	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	free(row);
	free(palette);

	return 0;
}

static QRcode *encode(const unsigned char *intext, int length)
{
	QRcode *code;

	if(micro) {
		if(eightbit) {
			code = QRcode_encodeDataMQR(length, intext, version, level);
		} else {
			code = QRcode_encodeStringMQR((char *)intext, version, level, hint, casesensitive);
		}
	} else if(eightbit) {
		code = QRcode_encodeData(length, intext, version, level);
	} else {
		code = QRcode_encodeString((char *)intext, version, level, hint, casesensitive);
	}

	return code;
}


int main(int argc, const char *argv[]){
    int ret = 0;
    std::string msg = "https://stage-res.shiqichuban.com/v1/image/get/7XREUL5TGgTcc_MvHVSAer9SlD7yZwSCuaBValMuOUQruIf3rwkGq0J4RTVcMcFZAt1mopDae8s5jPaWxcpM2Q";

    margin = 4;

    QRcode *code = encode((const unsigned char *)msg.c_str(), msg.length());
    std::vector<ui8> out;
    writePNG(code, out, PNG_TYPE); 
    std::ofstream outfile ("out.png",std::ofstream::binary);
    outfile.write((const char *)out.data(), out.size());
    outfile.close();
    return ret;
}


