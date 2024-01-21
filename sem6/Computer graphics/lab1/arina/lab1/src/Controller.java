import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import java.net.URL;
import java.util.*;

public class Controller {

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private TextField cmykCtext;

    @FXML
    private TextField cmykMtext;

    @FXML
    private TextField cmykYtext;

    @FXML
    private TextField cmykKtext;

    @FXML
    private TextField xyzXtext;

    @FXML
    private TextField xyzYtext;

    @FXML
    private TextField xyzZtext;

    @FXML
    private TextField rgbRtext;

    @FXML
    private TextField rgbGtext;

    @FXML
    private TextField rgbBtext;

    @FXML
    private ColorPicker bar;

    @FXML
    private Slider cmykCslider;

    @FXML
    private Slider cmykMslider;

    @FXML
    private Slider cmykYslider;

    @FXML
    private Slider cmykKslider;

    @FXML
    private Slider xyzXslider;

    @FXML
    private Slider xyzYslider;

    @FXML
    private Slider xyzZslider;

    @FXML
    private Slider rgbRslider;

    @FXML
    private Slider rgbGslider;

    @FXML
    private Slider rgbBslider;

    @FXML
    private Rectangle colorField;

    private Converter handler = new Converter();
    private boolean isBlocked = false;

    @FXML
    void initialize() {
        setSliders();
        setSliderValuesToText();
        setTexts();
        updateText();
    }

    @FXML
    void barAction(ActionEvent event) {
        if (!isBlocked) {
            isBlocked = true;
            double r = bar.getValue().getRed() * 255;
            double g = bar.getValue().getGreen() * 255;
            double b = bar.getValue().getBlue() * 255;
            if (r == 255 && g == 255 && b == 255) {
                handler.view = true;
            }
            double[] rgb = handler.checkRgb(new double[]{r, g, b});
            double[] xyz = handler.checkXyz(handler.convertRgbToXyz(rgb[0], rgb[1], rgb[2]));
            double[] cmyk = handler.checkCmyk(handler.convertRgbToCmyk(rgb[0], rgb[1], rgb[2]));

            rgbUpdate(rgb);
            xyzUpdate(xyz);
            cmykUpdate(cmyk);
            colorField.setFill(bar.getValue());
            isBlocked = false;
            handler.view = false;
        }
    }

    private void setSliders() {
        barAction(new ActionEvent());
        List<Slider> cmyk_sliders = Arrays.asList(cmykCslider, cmykMslider, cmykYslider, cmykKslider);
        List<Slider> xyz_sliders = Arrays.asList(xyzXslider, xyzYslider, xyzZslider);
        List<Slider> rgb_sliders = Arrays.asList(rgbRslider, rgbBslider, rgbGslider);

        for (Slider cmyk_slider : cmyk_sliders) {
            cmykSlider(cmyk_slider);
        }
        for (Slider xyz_slider : xyz_sliders) {
            xyzSlider(xyz_slider);
        }

        for (Slider rgb_slider : rgb_sliders) {
            rgbSlider(rgb_slider);
        }
    }

    private void setTexts() {
        List<TextField> cmyk_texts = Arrays.asList(cmykCtext, cmykMtext, cmykYtext, cmykKtext);
        List<TextField> xyz_texts = Arrays.asList(xyzXtext, xyzYtext, xyzZtext);
        List<TextField> rgb_texts =  Arrays.asList(rgbRtext, rgbGtext, rgbBtext);
        for (TextField xyz_text: xyz_texts) {
            xyzAction(xyz_text);
        }
        for (TextField cmyk_text: cmyk_texts) {
            cmykAction(cmyk_text);
        }
        for (TextField rgb_text: rgb_texts) {
            rgbAction(rgb_text);
        }
    }

    private void cmykUpdate(double[] cmyk) {
        cmykCtext.setText(Long.toString(Math.round(cmyk[0])));
        cmykMtext.setText(Long.toString(Math.round(cmyk[1])));
        cmykYtext.setText(Long.toString(Math.round(cmyk[2])));
        cmykKtext.setText(Long.toString(Math.round(cmyk[3])));
    }

    private void xyzUpdate(double[] xyz) {
        xyzXtext.setText(Long.toString(Math.round(xyz[0])));
        xyzYtext.setText(Long.toString(Math.round(xyz[1])));
        xyzZtext.setText(Long.toString(Math.round(xyz[2])));
    }

    private void rgbUpdate(double[] rgb) {
        rgbRtext.setText(Long.toString(Math.round(rgb[0])));
        rgbGtext.setText(Long.toString(Math.round(rgb[1])));
        rgbBtext.setText(Long.toString(Math.round(rgb[2])));
    }

    public void cmykAction(TextField textField) {
        textField.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!isBlocked && !textField.getText().isEmpty() && !textField.getText().equals("-")) {
                isBlocked = true;
                int c = Integer.parseInt(cmykCtext.getText());
                int m = Integer.parseInt(cmykMtext.getText());
                int y = Integer.parseInt(cmykYtext.getText());
                int k = Integer.parseInt(cmykKtext.getText());
                double[] cmyk = handler.checkCmyk(new double[]{c, m, y, k});
                double[] rgb = handler.checkRgb(handler.convertCmykToRgb(c / 100d, m / 100d, y / 100d, k / 100d));
                double[] xyz = handler.checkXyz(handler.convertRgbToXyz(rgb[0], rgb[1], rgb[2]));
                cmykUpdate(cmyk);
                xyzUpdate(xyz);
                rgbUpdate(rgb);
                updateColor(rgb);
                updateSliders();
                isBlocked = false;
            }
        });
    }

    public void xyzAction(TextField textField) {
        textField.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!isBlocked && !textField.getText().isEmpty() && !textField.getText().equals("-")) {
                isBlocked = true;
                int x = Integer.parseInt(xyzXtext.getText());
                int y = Integer.parseInt(xyzYtext.getText());
                int z = Integer.parseInt(xyzZtext.getText());
                double[] xyz = handler.checkXyz(new double[]{x, y, z});
                double[] rgb = handler.checkRgb(handler.convertXyzToRgb(xyz[0], xyz[1], xyz[2]));
                double[] cmyk = handler.checkCmyk(handler.convertRgbToCmyk(rgb[0], rgb[1], rgb[2]));
                cmykUpdate(cmyk);
                xyzUpdate(xyz);
                rgbUpdate(rgb);
                updateColor(rgb);
                updateSliders();
                isBlocked = false;
            }
        });
    }

    public void rgbAction(TextField textField) {
        textField.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!isBlocked && !textField.getText().isEmpty() && !textField.getText().equals("-")) {
                isBlocked = true;
                int r = Integer.parseInt(rgbRtext.getText());
                int g = Integer.parseInt(rgbGtext.getText());
                int b = Integer.parseInt(rgbBtext.getText());
                double[] rgb = handler.checkXyz(new double[]{r, g, b});
                double[] xyz = handler.checkXyz(handler.convertRgbToXyz(rgb[0], rgb[1], rgb[2]));
                double[] cmyk = handler.checkCmyk(handler.convertRgbToCmyk(rgb[0], rgb[1], rgb[2]));
                cmykUpdate(cmyk);
                xyzUpdate(xyz);
                updateColor(rgb);
                updateSliders();
                isBlocked = false;
            }
        });
    }

    public void sliderValueToText(Slider slider, TextField textField) {
        slider.valueProperty().addListener((observable, oldValue, newValue) -> {
            textField.setText(Integer.toString(Math.round(newValue.floatValue())));
        });
    }

    private void updateColor(double[] rgb) {
        bar.setValue(new Color(rgb[0] / 255d, rgb[1] / 255d, rgb[2] / 255d, 1));
        colorField.setFill(bar.getValue());
    }

    private void cmykSlider(Slider slider) {
        slider.setShowTickLabels(true);
        slider.setShowTickMarks(true);
    }

    private void xyzSlider(Slider slider) {
        if (slider.equals(xyzXslider)) {
            slider.setMin(0);
            slider.setMax(95);
        } else if (slider.equals(xyzYslider)) {
            slider.setMin(0);
            slider.setMax(100);
        } else {
            slider.setMin(0);
            slider.setMax(108);
        }
        slider.setShowTickLabels(true);
        slider.setShowTickMarks(true);
    }

    private void rgbSlider(Slider slider) {
        slider.setMin(0);
        slider.setMax(255);
        slider.setShowTickLabels(true);
        slider.setShowTickMarks(true);
    }

    private void updateSliders() {
        cmykCslider.setValue(Double.parseDouble(cmykCtext.getText()));
        cmykMslider.setValue(Double.parseDouble(cmykMtext.getText()));
        cmykYslider.setValue(Double.parseDouble(cmykYtext.getText()));
        cmykKslider.setValue(Double.parseDouble(cmykKtext.getText()));

        xyzXslider.setValue(Double.parseDouble(xyzXtext.getText()));
        xyzYslider.setValue(Double.parseDouble(xyzYtext.getText()));
        xyzZslider.setValue(Double.parseDouble(xyzZtext.getText()));

        rgbRslider.setValue(Double.parseDouble(rgbRtext.getText()));
        rgbGslider.setValue(Double.parseDouble(rgbGtext.getText()));
        rgbBslider.setValue(Double.parseDouble(rgbBtext.getText()));
    }
    private void changeText(TextField textField) {
        textField.setTextFormatter(new TextFormatter<>(
                change -> (change.getControlNewText().matches("[0-9]*")) ? change : null));
    }

    private void updateText() {
        List<TextField> list = Arrays.asList(cmykCtext, cmykMtext, cmykYtext, cmykKtext, xyzXtext, xyzYtext, xyzZtext,
                rgbRtext, rgbGtext, rgbBtext);
        for (TextField textField : list) {
            changeText(textField);
        }
    }

    private void setSliderValuesToText() {
        sliderValueToText(cmykCslider, cmykCtext);
        sliderValueToText(cmykMslider, cmykMtext);
        sliderValueToText(cmykYslider, cmykYtext);
        sliderValueToText(cmykKslider, cmykKtext);

        sliderValueToText(xyzXslider, xyzXtext);
        sliderValueToText(xyzYslider, xyzYtext);
        sliderValueToText(xyzZslider, xyzZtext);

        sliderValueToText(rgbRslider, rgbRtext);
        sliderValueToText(rgbGslider, rgbGtext);
        sliderValueToText(rgbBslider, rgbBtext);
    }
}
