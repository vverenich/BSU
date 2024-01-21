#include "colorconverter.h"

#include <QDebug>

#include "math.h"

QColor ColorConverter::getColor() const
{
    return m_Color.rgb();
}

uint8_t ColorConverter::getRed() const
{
    return m_Color.red();
}

uint8_t ColorConverter::getGreen() const
{
    return m_Color.green();
}

uint8_t ColorConverter::getBlue() const
{
    return m_Color.blue();
}

std::tuple<float, float, float> ColorConverter::getHSV() const
{
    // R, G, B values are divided by 255
    // to change the range from 0..255 to 0..1
    float r = m_Color.red() / 255.0;
    float g = m_Color.green() / 255.0;
    float b = m_Color.blue() / 255.0;

    // h, s, v = hue, saturation, value
    double cmax = std::max(r, std::max(g, b)); // maximum of r, g, b
    double cmin = std::min(r, std::min(g, b)); // minimum of r, g, b
    double diff = cmax - cmin; // diff of cmax and cmin.
    double h = -1, s = -1;

    // if cmax and cmax are equal then h = 0
    if (cmax == cmin)
        h = 0;
    // if cmax equal r then compute h
    else if (cmax == r)
        h = std::fmod(60 * ((g - b) / diff) + 360, 360);

    // if cmax equal g then compute h
    else if (cmax == g)
        h = fmod(60 * ((b - r) / diff) + 120, 360);

    // if cmax equal b then compute h
    else if (cmax == b)
        h = fmod(60 * ((r - g) / diff) + 240, 360);

    // if cmax equal zero
    if (cmax == 0)
        s = 0;
    else
        s = (diff / cmax) * 100;

    // compute v
    double v = cmax * 100;

    return std::make_tuple(h, s, v);
}

std::tuple<float, float, float> ColorConverter::getLAB() const
{
    float var_R = m_Color.red()/255.0;
    float var_G = m_Color.green()/255.0;
    float var_B = m_Color.blue()/255.0;


    if ( var_R > 0.04045 ) var_R = pow( (( var_R + 0.055 ) / 1.055 ), 2.4 );
    else                   var_R = var_R / 12.92;
    if ( var_G > 0.04045 ) var_G = pow( ( ( var_G + 0.055 ) / 1.055 ), 2.4);
    else                   var_G = var_G / 12.92;
    if ( var_B > 0.04045 ) var_B = pow( ( ( var_B + 0.055 ) / 1.055 ), 2.4);
    else                   var_B = var_B / 12.92;

    var_R = var_R * 100.;
    var_G = var_G * 100.;
    var_B = var_B * 100.;

    //Observer. = 2°, Illuminant = D65
    float X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    float Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    float Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;


    float var_X = X / 95.047 ;         //ref_X =  95.047   Observer= 2°, Illuminant= D65
    float var_Y = Y / 100.000;          //ref_Y = 100.000
    float var_Z = Z / 108.883;          //ref_Z = 108.883

    if ( var_X > 0.008856 ) var_X = pow(var_X , ( 1./3. ) );
    else                    var_X = ( 7.787 * var_X ) + ( 16. / 116. );
    if ( var_Y > 0.008856 ) var_Y = pow(var_Y , ( 1./3. ));
    else                    var_Y = ( 7.787 * var_Y ) + ( 16. / 116. );
    if ( var_Z > 0.008856 ) var_Z = pow(var_Z , ( 1./3. ));
    else                    var_Z = ( 7.787 * var_Z ) + ( 16. / 116. );

    float l = ( 116. * var_Y ) - 16.;
    float a = 500. * ( var_X - var_Y );
    float b = 200. * ( var_Y - var_Z );

    return std::make_tuple(l, a, b);
}

std::tuple<float, float, float> ColorConverter::getHSL() const
{
    float h{};
    float s{};
    float l{};

    float r = (m_Color.red() / 255.0f);
    float g = (m_Color.green() / 255.0f);
    float b = (m_Color.blue() / 255.0f);

    float min = std::min(std::min(r, g), b);
    float max = std::max(std::max(r, g), b);
    float delta = max - min;

    l = (max + min) / 2;

    if (delta == 0)
    {
        h = 0;
        s = 0.0f;
    }
    else
    {
        s = (l <= 0.5) ? (delta / (max + min)) : (delta / (2 - max - min));

        float hue;

        if (r == max)
        {
            hue = ((g - b) / 6) / delta;
        }
        else if (g == max)
        {
            hue = (1.0f / 3) + ((b - r) / 6) / delta;
        }
        else
        {
            hue = (2.0f / 3) + ((r - g) / 6) / delta;
        }

        if (hue < 0)
            hue += 1;
        if (hue > 1)
            hue -= 1;

        h = (int)(hue * 360);
    }

    return std::make_tuple(h,s * 100,l * 100);
}

std::tuple<float, float, float, float> ColorConverter::getCMYK() const
{
    double dr = (double)m_Color.red() / 255;
    double dg = (double)m_Color.green() / 255;
    double db = (double)m_Color.blue()/ 255;
    double k = 1 - std::max(std::max(dr, dg), db);
    double c = (1 - dr - k) / (1 - k);
    double m = (1 - dg - k) / (1 - k);
    double y = (1 - db - k) / (1 - k);

    return std::make_tuple(c * 100 , m * 100, y * 100, k * 100);
}

void ColorConverter::setColor(const QColor &color)
{
    m_Color = color;
}

void ColorConverter::setRed(const uint8_t value)
{
    m_Color.setRed(value);
}

void ColorConverter::setGreen(const uint8_t value)
{
    m_Color.setGreen(value);
}

void ColorConverter::setBlue(const uint8_t value)
{
    m_Color.setBlue(value);
}

void ColorConverter::setHSV(float H, float S, float V)
{
        if (H>360 || H<0 || S>100 || S<0 || V>100 || V<0) {
            qDebug() << "The givem HSV values are not in valid range";
            return;
        }
        float s = S/100;
        float v = V/100;
        float C = s*v;
        float X = C*(1-abs(fmod(H/60.0, 2)-1));
        float m = v-C;
        float r,g,b;
        if(H >= 0 && H < 60){
            r = C,g = X,b = 0;
        }
        else if(H >= 60 && H < 120){
            r = X,g = C,b = 0;
        }
        else if(H >= 120 && H < 180){
            r = 0,g = C,b = X;
        }
        else if(H >= 180 && H < 240){
            r = 0,g = X,b = C;
        }
        else if(H >= 240 && H < 300){
            r = X,g = 0,b = C;
        }
        else{
            r = C,g = 0,b = X;
        }
        m_Color.setRed( (r+m)*255 );
        m_Color.setGreen( (g+m)*255 );
        m_Color.setBlue( (b+m)*255 );
}

void ColorConverter::setLAB(float l, float a, float b)
{
    float var_Y = ( l + 16. ) / 116.;
    float var_X = a / 500. + var_Y;
    float var_Z = var_Y - b / 200.;

    if ( pow(var_Y,3) > 0.008856 ) var_Y = pow(var_Y,3);
    else                      var_Y = ( var_Y - 16. / 116. ) / 7.787;
    if ( pow(var_X,3) > 0.008856 ) var_X = pow(var_X,3);
    else                      var_X = ( var_X - 16. / 116. ) / 7.787;
    if ( pow(var_Z,3) > 0.008856 ) var_Z = pow(var_Z,3);
    else                      var_Z = ( var_Z - 16. / 116. ) / 7.787;

    float X = 95.047 * var_X ;    //ref_X =  95.047     Observer= 2°, Illuminant= D65
    float Y = 100.000 * var_Y  ;   //ref_Y = 100.000
    float Z = 108.883 * var_Z ;    //ref_Z = 108.883


    var_X = X / 100. ;       //X from 0 to  95.047      (Observer = 2°, Illuminant = D65)
    var_Y = Y / 100. ;       //Y from 0 to 100.000
    var_Z = Z / 100. ;      //Z from 0 to 108.883

    float var_R = var_X *  3.2406 + var_Y * -1.5372 + var_Z * -0.4986;
    float var_G = var_X * -0.9689 + var_Y *  1.8758 + var_Z *  0.0415;
    float var_B = var_X *  0.0557 + var_Y * -0.2040 + var_Z *  1.0570;

    if ( var_R > 0.0031308 ) var_R = 1.055 * pow(var_R , ( 1 / 2.4 ))  - 0.055;
    else                     var_R = 12.92 * var_R;
    if ( var_G > 0.0031308 ) var_G = 1.055 * pow(var_G , ( 1 / 2.4 ) )  - 0.055;
    else                     var_G = 12.92 * var_G;
    if ( var_B > 0.0031308 ) var_B = 1.055 * pow( var_B , ( 1 / 2.4 ) ) - 0.055;
    else                     var_B = 12.92 * var_B;

    m_Color.setRed(var_R * 255.);
    m_Color.setGreen(var_G * 255.);
    m_Color.setBlue(var_B * 255.);
}

float HueToRGB(float v1, float v2, float vH) {
    if (vH < 0)
        vH += 1;

    if (vH > 1)
        vH -= 1;

    if ((6 * vH) < 1)
        return (v1 + (v2 - v1) * 6 * vH);

    if ((2 * vH) < 1)
        return v2;

    if ((3 * vH) < 2)
        return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

    return v1;
}

void ColorConverter::setHSL(float H, float S, float L)
{
    S /= 100;
    L /= 100;

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    if (S == 0)
    {
        r = g = b = (unsigned char)(L * 255);
    }
    else
    {
        float v1, v2;
        float hue = (float)H / 360;

        v2 = (L < 0.5) ? (L * (1 + S)) : ((L + S) - (L * S));
        v1 = 2 * L - v2;

        r = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
        g = (unsigned char)(255 * HueToRGB(v1, v2, hue));
        b = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
    }

    m_Color.setRed(r);
    m_Color.setGreen(g);
    m_Color.setBlue(b);
}

void ColorConverter::setCMYK(float c, float m, float y, float k)
{
    unsigned char r = (unsigned char)(255 * (1 - c/100) * (1 - k/100));
    unsigned char g = (unsigned char)(255 * (1 - m/100) * (1 - k/100));
    unsigned char b = (unsigned char)(255 * (1 - y/100) * (1 - k/100));

    m_Color.setRed(r);
    m_Color.setGreen(g);
    m_Color.setBlue(b);
}
