#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QColor>

#include "colorconverter.h"

class View : public QObject {

    Q_OBJECT
    Q_PROPERTY(int sliderRedValue READ getSliderRedValue WRITE setSliderRedValue NOTIFY sliderRedValueChanged)
    Q_PROPERTY(int sliderGreenValue READ getSliderGreenValue WRITE setSliderGreenValue NOTIFY sliderGreenValueChanged)
    Q_PROPERTY(int sliderBlueValue READ getSliderBlueValue WRITE setSliderBlueValue NOTIFY sliderBlueValueChanged)

    Q_PROPERTY(int textFieldRedValue READ getTextFieldRedValue WRITE setTextFieldRedValue NOTIFY textFieldRedValueChanged)
    Q_PROPERTY(int textFieldGreenValue READ getTextFieldGreenValue WRITE setTextFieldGreenValue NOTIFY textFieldGreenValueChanged)
    Q_PROPERTY(int textFieldBlueValue READ getTextFieldBlueValue WRITE setTextFieldBlueValue NOTIFY textFieldBlueValueChanged)

    Q_PROPERTY(int textFieldHueValue READ getTextFieldHueValue WRITE setTextFieldHueValue NOTIFY textFieldHueValueChanged)
    Q_PROPERTY(int textFieldSaturationValue READ getTextFieldSaturationValue WRITE setTextFieldSaturationValue NOTIFY textFieldSaturationValueChanged)
    Q_PROPERTY(int textFieldLightnessValue READ getTextFieldLightnessValue WRITE setTextFieldLightnessValue NOTIFY textFieldLightnessValueChanged)

    Q_PROPERTY(int textFieldCValue READ getTextFieldCValue WRITE setTextFieldCValue NOTIFY textFieldCValueChanged)
    Q_PROPERTY(int textFieldMValue READ getTextFieldMValue WRITE setTextFieldMValue NOTIFY textFieldMValueChanged)
    Q_PROPERTY(int textFieldYValue READ getTextFieldYValue WRITE setTextFieldYValue NOTIFY textFieldYValueChanged)
    Q_PROPERTY(int textFieldKValue READ getTextFieldKValue WRITE setTextFieldKValue NOTIFY textFieldKValueChanged)

    Q_PROPERTY(QColor rectangleColor READ getRectangleColor WRITE setRectangleColor NOTIFY rectangleColorChanged)

  signals:
    void sliderRedValueChanged();
    void sliderGreenValueChanged();
    void sliderBlueValueChanged();

    void textFieldRedValueChanged();
    void textFieldGreenValueChanged();
    void textFieldBlueValueChanged();

    void textFieldHueValueChanged();
    void textFieldSaturationValueChanged();
    void textFieldLightnessValueChanged();

    void textFieldCValueChanged();
    void textFieldMValueChanged();
    void textFieldYValueChanged();
    void textFieldKValueChanged();

    void rectangleColorChanged();

 public slots:
    void setSliderRedValue(const int value);
    void setSliderGreenValue(const int value);
    void setSliderBlueValue(const int value);

    void setTextFieldRedValue(const int value);
    void setTextFieldGreenValue(const int value);
    void setTextFieldBlueValue(const int value);

    void setTextFieldHueValue(float h, float s, float v);
    void setTextFieldSaturationValue(float h, float s, float v);
    void setTextFieldLightnessValue(float h, float s, float v);

    void setTextFieldHueValue(const int value);
    void setTextFieldSaturationValue(const int value);
    void setTextFieldLightnessValue(const int value);

    void setTextFieldCValue(float l, float a, float b);
    void setTextFieldMValue(float l, float a, float b);
    void setTextFieldYValue(float l, float a, float b);
    void setTextFieldKValue(float l, float a, float b);

    void setTextFieldCValue(const int value);
    void setTextFieldMValue(const int value);
    void setTextFieldYValue(const int value);
    void setTextFieldKValue(const int value);

    void setHSL(float h, float s, float l);
    void setCMYK(float c, float m, float y, float k);

    void setRectangleColor(const QColor& color);

  public:
    View() = default;
    ~View() = default;

    void recalculateColorModelsParameters();
    void emitAllTheParameterSignals();

    int getSliderRedValue() const;
    int getSliderGreenValue() const;
    int getSliderBlueValue() const;

    int getTextFieldRedValue() const;
    int getTextFieldGreenValue() const;
    int getTextFieldBlueValue() const;

    int getTextFieldHueValue() const;
    int getTextFieldSaturationValue() const;
    int getTextFieldLightnessValue() const;

    int getTextFieldCValue() const;
    int getTextFieldMValue() const;
    int getTextFieldYValue() const;
    int getTextFieldKValue() const;

    QColor getRectangleColor() const;

  private:
    int m_SliderRedValue{100};
    int m_SliderGreenValue{150};
    int m_SliderBlueValue{100};

    int m_TextFieldRedValue{};
    int m_TextFieldGreenValue{};
    int m_TextFieldBlueValue{};

    int m_TextFieldHueValue{};
    int m_TextFieldSaturationValue{};
    int m_TextFieldLightnessValue{};

    int m_TextFieldCValue{};
    int m_TextFieldMValue{};
    int m_TextFieldYValue{};
    int m_TextFieldKValue{};

    QColor m_RectangleColor{100, 150, 100};

    ColorConverter m_ColorConverter{};

};

#endif // VIEW_H
