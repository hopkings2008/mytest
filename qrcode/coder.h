#ifndef _CIS_QRCODE_CODER_H
#define _CIS_QRCODE_CODER_H

#include <vector>
#include <qrencode.h>

namespace shiqi{
    namespace cis{

        enum ImageType {
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


        class Coder{
            public:
                Coder();
                ~Coder();

                int create(const unsigned char *intext, int length, std::vector<unsigned char> &out);

            protected:
                void fillRow(unsigned char *row, int num, const unsigned char color[]);

                int writePNG(const QRcode *qrcode, std::vector<unsigned char> &out);

                QRcode *encode(const unsigned char *intext, int length);

            protected:
                int m_casesensitive;
                int m_eightbit;
                int m_version;
                int m_size;
                int m_margin;
                int m_dpi;
                int m_micro;
                QRecLevel m_level;
                QRencodeMode m_hint;
                ImageType m_type;
        };
    }
}

#endif
