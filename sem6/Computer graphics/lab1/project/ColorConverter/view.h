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
    Q_PROPERTY(int textFieldValueValue READ getTextFieldValueValue WRITE setTextFieldValueValue NOTIFY textFieldValueValueChanged)
    Q_PROPERTY(int textFieldLValue READ getTextFieldLValue WRITE setTextFieldLValue NOTIFY textFieldLValueChanged)
    Q_PROPERTY(int textFieldAValue READ getTextFieldAValue WRITE setTextFieldAValue NOTIFY textFieldAValueChanged)
    Q_PROPERTY(int textFieldBValue READ getTextFieldBValue WRITE setTextFieldBValue NOTIFY textFieldBValueChanged)
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
    void textFieldValueValueChanged();

    void textFieldLValueChanged();
    void textFieldAValueChanged();
    void textFieldBValueChanged();

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
    void setTextFieldValueValue(float h, float s, float v);

    void setTextFieldHueValue(const int value);
    void setTextFieldSaturationValue(const int value);
    void setTextFieldValueValue(const int value);

    void setTextFieldLValue(float l, float a, float b);
    void setTextFieldAValue(float l, float a, float b);
    void setTextFieldBValue(float l, float a, float b);

    void setTextFieldLValue(const int value);
    void setTextFieldAValue(const int value);
    void setTextFieldBValue(const int value);

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
    int getTextFieldValueValue() const;

    int getTextFieldLValue() const;
    int getTextFieldAValue() const;
    int getTextFieldBValue() const;

    QColor getRectangleColor() const;

  private:
    int m_SliderRedValue{};
    int m_SliderGreenValue{};
    int m_SliderBlueValue{};

    int m_TextFieldRedValue{};
    int m_TextFieldGreenValue{};
    int m_TextFieldBlueValue{};

    int m_TextFieldHueValue{};
    int m_TextFieldSaturationValue{};
    int m_TextFieldValueValue{};

    int m_TextFieldLValue{};
    int m_TextFieldAValue{};
    int m_TextFieldBValue{};

    QColor m_RectangleColor{};

    ColorConverter m_ColorConverter{};

};

#endif // VIEW_H
