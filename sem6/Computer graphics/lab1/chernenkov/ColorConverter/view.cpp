#include "view.h"

#include <QDebug>

int View::getSliderRedValue() const
{
    return m_SliderRedValue;
}

int View::getSliderGreenValue() const
{
    return m_SliderGreenValue;
}

int View::getSliderBlueValue() const
{
    return m_SliderBlueValue;
}

int View::getTextFieldRedValue() const
{
    return m_TextFieldRedValue;
}

int View::getTextFieldGreenValue() const
{
    return m_TextFieldGreenValue;
}

int View::getTextFieldBlueValue() const
{
    return m_TextFieldBlueValue;
}

int View::getTextFieldHueValue() const
{
    return m_TextFieldHueValue;
}

int View::getTextFieldSaturationValue() const
{
    return m_TextFieldSaturationValue;
}

int View::getTextFieldLightnessValue() const
{
    return m_TextFieldLightnessValue;
}

int View::getTextFieldCValue() const
{
    return m_TextFieldCValue;
}

int View::getTextFieldMValue() const
{
    return m_TextFieldMValue;
}

int View::getTextFieldYValue() const
{
    return m_TextFieldYValue;
}

int View::getTextFieldKValue() const
{
    return m_TextFieldKValue;
}

QColor View::getRectangleColor() const
{
    return m_RectangleColor;
}

void View::setSliderRedValue(const int value)
{
    if (m_SliderRedValue == value) {
        return;
    }

    m_ColorConverter.setRed(value);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setSliderGreenValue(const int value)
{
    if (m_SliderGreenValue == value) {
        return;
    }

    m_ColorConverter.setGreen(value);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setSliderBlueValue(const int value)
{
    if (m_SliderBlueValue == value) {
        return;
    }

    m_ColorConverter.setBlue(value);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldRedValue(const int value)
{
    if (m_TextFieldRedValue == value) {
        return;
    }

    m_ColorConverter.setRed(value);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldGreenValue(const int value)
{
    if (m_TextFieldGreenValue == value) {
        return;
    }

    m_ColorConverter.setGreen(value);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldBlueValue(const int value)
{
    if (m_TextFieldBlueValue == value) {
        return;
    }

    m_ColorConverter.setBlue(value);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldHueValue(float h, float s, float v)
{
    if (m_TextFieldHueValue == h) {
        return;
    }

    m_ColorConverter.setHSV(h, s, v);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldSaturationValue(float h, float s, float v)
{
    if (m_TextFieldSaturationValue == s) {
        return;
    }

    m_ColorConverter.setHSV(h, s, v);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldLightnessValue(float h, float s, float v)
{
    if (m_TextFieldLightnessValue == v) {
        return;
    }

    m_ColorConverter.setHSV(h, s, v);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldHueValue(const int value)
{

}

void View::setTextFieldSaturationValue(const int value)
{

}

void View::setTextFieldLightnessValue(const int value)
{

}

void View::setTextFieldCValue(float l, float a, float b)
{
    if (m_TextFieldCValue == l) {
        return;
    }

    m_ColorConverter.setLAB(l, a, b);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldMValue(float l, float a, float b)
{
    if (m_TextFieldMValue == a) {
        return;
    }

    m_ColorConverter.setLAB(l, a, b);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldYValue(float l, float a, float b)
{
    if (m_TextFieldYValue == b) {
        return;
    }

    m_ColorConverter.setLAB(l, a, b);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldKValue(float l, float a, float b)
{

}

void View::setTextFieldCValue(const int value)
{

}

void View::setTextFieldMValue(const int value)
{

}

void View::setTextFieldYValue(const int value)
{

}

void View::setTextFieldKValue(const int value)
{

}

void View::setHSL(float h, float s, float l)
{
    if (m_TextFieldHueValue == h &&
        m_TextFieldSaturationValue == s &&
        m_TextFieldLightnessValue == l) {
        return;
    }

    m_ColorConverter.setHSL(h,s,l);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setCMYK(float c, float m, float y, float k)
{
    if (m_TextFieldCValue == c &&
        m_TextFieldMValue == m &&
        m_TextFieldYValue == y &&
        m_TextFieldKValue == k) {
        return;
    }

    m_ColorConverter.setCMYK(c,m,y,k);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setRectangleColor(const QColor &color)
{
    if (m_RectangleColor == color) {
        return;
    }

    m_ColorConverter.setColor(color);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::recalculateColorModelsParameters()
{
    m_SliderRedValue = m_ColorConverter.getRed();
    m_SliderGreenValue = m_ColorConverter.getGreen();
    m_SliderBlueValue = m_ColorConverter.getBlue();

    m_TextFieldRedValue = m_ColorConverter.getRed();
    m_TextFieldGreenValue = m_ColorConverter.getGreen();
    m_TextFieldBlueValue = m_ColorConverter.getBlue();

    auto hsl = m_ColorConverter.getHSL();

    m_TextFieldHueValue = std::get<0>(hsl);
    m_TextFieldSaturationValue = std::get<1>(hsl);
    m_TextFieldLightnessValue = std::get<2>(hsl);

    auto cmyk = m_ColorConverter.getCMYK();

    m_TextFieldCValue = std::get<0>(cmyk);
    m_TextFieldMValue = std::get<1>(cmyk);
    m_TextFieldYValue = std::get<2>(cmyk);
    m_TextFieldKValue = std::get<3>(cmyk);

    m_RectangleColor = m_ColorConverter.getColor();
}

void View::emitAllTheParameterSignals()
{
    emit sliderRedValueChanged();
    emit sliderGreenValueChanged();
    emit sliderBlueValueChanged();

    emit textFieldRedValueChanged();
    emit textFieldGreenValueChanged();
    emit textFieldBlueValueChanged();

    emit textFieldHueValueChanged();
    emit textFieldSaturationValueChanged();
    emit textFieldLightnessValueChanged();

    emit textFieldCValueChanged();
    emit textFieldMValueChanged();
    emit textFieldYValueChanged();
    emit textFieldKValueChanged();

    emit rectangleColorChanged();
}
