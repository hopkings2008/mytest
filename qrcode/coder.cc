#include <coder.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>

#define INCHES_PER_METER (100.0/2.54)

namespace shiqi{
    namespace cis{
        static unsigned char fg_color[4] = {0, 0, 0, 255};
        static unsigned char bg_color[4] = {255, 255, 255, 255};

        static void PngWriteCallback(png_structp  png_ptr, png_bytep data, png_size_t length) {
            std::vector<unsigned char> *p = (std::vector<unsigned char>*)png_get_io_ptr(png_ptr);
            p->insert(p->end(), data, data + length);
        }

        Coder::Coder():m_casesensitive(1), m_eightbit(0), m_version(0), m_size(3), m_margin(2), m_dpi(72), m_micro(0), m_level(QR_ECLEVEL_L), m_hint(QR_MODE_8), m_type(PNG_TYPE){
        }

        Coder::~Coder(){
        }

        int Coder::create(const unsigned char *intext, int length, std::vector<unsigned char> &out){
            QRcode *code = encode(intext, length);
            int ret = writePNG(code, out);
            if (code != NULL){
                QRcode_free(code);
                code = NULL;
            }
            return ret;
        }

        void Coder::fillRow(unsigned char *row, int num, const unsigned char color[]){
            for(int i = 0; i < num; i++) {
                memcpy(row, color, 4);
                row += 4;
            }
        }

        int Coder::writePNG(const QRcode *qrcode, std::vector<unsigned char> &out){
            png_structp png_ptr;
            png_infop info_ptr;
            png_colorp palette = NULL;
            png_byte alpha_values[2];
            unsigned char *row, *p, *q;
            int x, y, xx, yy, bit;
            int realwidth;

            ImageType type = m_type;
            int margin = m_margin;
            int size = m_size;
            int dpi = m_dpi;

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

        QRcode *Coder::encode(const unsigned char *intext, int length){

            QRcode *code;

            int casesensitive = m_casesensitive;
            int micro = m_micro;
            int eightbit = m_eightbit;
            QRencodeMode hint = m_hint;
            int version = m_version;
            QRecLevel level = m_level;

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
    }
}
