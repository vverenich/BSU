public class Converter {
    public boolean view = false;

    public double[] checkRgb(double[] rgb) {
        for (int i = 0; i < rgb.length; i++) {
            rgb[i] = Math.min(255, rgb[i]);
            rgb[i] = Math.max(0, rgb[i]);
        }
        return rgb;
    }

    public double[] checkCmyk(double[] cmyk) {
        for (int i = 0; i < cmyk.length; i++) {
            cmyk[i] = Math.min(100, cmyk[i]);
            cmyk[i] = Math.max(0, cmyk[i]);
        }
        return cmyk;
    }

    public double[] checkXyz(double[] xyz) {
        xyz[0] = Math.min(95, xyz[0]);
        xyz[0] = Math.max(0, xyz[0]);
        xyz[1] = Math.min(100, xyz[1]);
        xyz[1] = Math.max(0, xyz[1]);
        xyz[2] = Math.min(108, xyz[2]);
        xyz[2] = Math.max(0, xyz[2]);
        return xyz;
    }

    public double[] convertCmykToRgb(double c, double m, double y, double k) {
        double[] rgb = new double[3];
        rgb[0] = 255 * (1 - c) * (1 - k);
        rgb[1] = 255 * (1 - m) * (1 - k);
        rgb[2] = 255 * (1 - y) * (1 - k);
        return rgb;
    }

    public double[] convertRgbToCmyk(double r, double g, double b) {
        double[] cmyk = new double[4];
        cmyk[3] = Math.min(Math.min(1 - r / 255d, 1 - g / 255d), 1 - b / 255d);
        cmyk[0] = 100 * (1 - r / 255d - cmyk[3]) / (1 - cmyk[3]);
        cmyk[1] = 100 * (1 - g / 255d - cmyk[3]) / (1 - cmyk[3]);
        cmyk[2] = 100 * (1 - b / 255d - cmyk[3]) / (1 - cmyk[3]);
        cmyk[3] *= 100;
        return cmyk;
    }

    public double[] convertXyzToRgb(double x, double y, double z) {
        double[] rgb = new double[3];
        double Rn = 3.2406 * x / 100 - 1.5372 * y / 100 - 0.4986 * z / 100;
        double Gn = -0.9689 * x / 100 + 1.8758 * y / 100 + 0.0415 * z / 100;
        double Bn = 0.0557 * x / 100 - 0.2040 * y / 100 + 1.0570 * z / 100;
        rgb[0] = fXyzRgb(Rn) * 255;
        rgb[1] = fXyzRgb(Gn) * 255;
        rgb[2] = fXyzRgb(Bn) * 255;
        return rgb;
    }

    public double[] convertRgbToXyz(double r, double g, double b) {
        double[] xyz = new double[3];
        double Rn = fRgbXyz(r / 255) * 100;
        double Gn = fRgbXyz(g / 255) * 100;
        double Bn = fRgbXyz(b / 255) * 100;
        xyz[0] = 0.412453 * Rn + 0.357580 * Gn + 0.180423 * Bn;
        xyz[1] = 0.212671 * Rn + 0.715160 * Gn + 0.072169 * Bn;
        xyz[2] = 0.019334 * Rn + 0.119193 * Gn + 0.950227 * Bn;
        return xyz;
    }

    private double fXyzRgb(double x) {
        double ans;
        if (x >= 0.0031308) {
            ans = 1.055 * Math.pow(x, 1d / 2.4) - 0.055;
        } else {
            ans = 12.92 * x;
        }
        return ans;
    }

    private double fRgbXyz(double x) {
        double ans;
        if (x >= 0.04045) {
            ans = Math.pow((x + 0.055) / 1.055, 2.4);
        } else {
            ans = x / 12.92;
        }
        return ans;
    }
}
