#ifndef COLORCONVERTER_H
#define COLORCONVERTER_H

#include <QColor>

class ColorConverter {
  public:
    ColorConverter() = default;

    QColor getColor() const;
    uint8_t getRed() const;
    uint8_t getGreen() const;
    uint8_t getBlue() const;
    std::tuple<float, float, float> getHSV() const;
    std::tuple<float, float, float> getLAB() const;

    void setColor(const QColor& color);
    void setRed(const uint8_t value);
    void setGreen(const uint8_t value);
    void setBlue(const uint8_t value);
    void setHSV(float H, float S, float V);
    void setLAB(float l, float a, float b);

  private:
    QColor m_Color{};
};

#endif // COLORCONVERTER_H
