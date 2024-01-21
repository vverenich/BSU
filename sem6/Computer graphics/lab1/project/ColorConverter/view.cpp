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

int View::getTextFieldValueValue() const
{
    return m_TextFieldValueValue;
}

int View::getTextFieldLValue() const
{
    return m_TextFieldLValue;
}

int View::getTextFieldAValue() const
{
    return m_TextFieldAValue;
}

int View::getTextFieldBValue() const
{
    return m_TextFieldBValue;
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

void View::setTextFieldValueValue(float h, float s, float v)
{
    if (m_TextFieldValueValue == v) {
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

void View::setTextFieldValueValue(const int value)
{

}

void View::setTextFieldLValue(float l, float a, float b)
{
    if (m_TextFieldLValue == l) {
        return;
    }

    m_ColorConverter.setLAB(l, a, b);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldAValue(float l, float a, float b)
{
    if (m_TextFieldAValue == a) {
        return;
    }

    m_ColorConverter.setLAB(l, a, b);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldBValue(float l, float a, float b)
{
    if (m_TextFieldBValue == b) {
        return;
    }

    m_ColorConverter.setLAB(l, a, b);
    recalculateColorModelsParameters();
    emitAllTheParameterSignals();
}

void View::setTextFieldLValue(const int value)
{

}

void View::setTextFieldAValue(const int value)
{

}

void View::setTextFieldBValue(const int value)
{

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

    auto hsv = m_ColorConverter.getHSV();

    m_TextFieldHueValue = std::get<0>(hsv);
    m_TextFieldSaturationValue = std::get<1>(hsv);
    m_TextFieldValueValue = std::get<2>(hsv);

    auto lab = m_ColorConverter.getLAB();

    m_TextFieldLValue = std::get<0>(lab);
    m_TextFieldAValue = std::get<1>(lab);
    m_TextFieldBValue = std::get<2>(lab);

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
    emit textFieldValueValueChanged();

    emit textFieldLValueChanged();
    emit textFieldAValueChanged();
    emit textFieldBValueChanged();

    emit rectangleColorChanged();
}
