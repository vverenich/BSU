package by.verenich.pmvs_lab_6_3_3_var_18;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;

import androidx.appcompat.app.AppCompatActivity;

import com.example.pmvs_lab_6_3_3_var_4.R;

import java.util.Arrays;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    Spinner spinner1;
    Spinner spinner2;

    EditText etInput1;
    EditText etInput2;

    String[] CurrencyList = {"Волока", "Прутик кв.", "Шнур кв.", "Прут кв.", "Морг", "Метр кв."};
    double[] CoefficientList = {1 / 213600.0, 1 / 0.24, 1 / 2370.0, 1 / 23.77, 1 / 7100.0,  1 / 1.0};

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        spinner1 = (Spinner) findViewById(R.id.spinner1);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, CurrencyList);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner1.setAdapter(adapter);

        spinner2 = (Spinner) findViewById(R.id.spinner2);
        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, CurrencyList);
        adapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner2.setAdapter(adapter);

        etInput1 = (EditText) findViewById(R.id.editText1);

        etInput2 = (EditText) findViewById(R.id.editText2);
    }

    public void handleClick(View v) {
        Button button = (Button) v;
        etInput1.setText(etInput1.getText().toString() + button.getText().toString());
    }

    public void Dot_onClick(View v) {
        etInput1.setText((etInput1.getText().toString() + "."));
    }

    public void Clear_onClick(View v) {
        etInput1.setText("");
    }

    public void Plus_onClick(View v) {
        etInput1.setText((etInput1.getText().toString() + " + "));
    }

    public void Minus_onClick(View v) {
        etInput1.setText((etInput1.getText().toString() + " - "));
    }

    public void Multiply_onClick(View v) {
        etInput1.setText((etInput1.getText().toString() + " * "));
    }

    public void Divide_onClick(View v) {
        etInput1.setText((etInput1.getText().toString() + " / "));
    }

    public void Calculate_onClick(View v) {
        String expr = etInput1.getText().toString();

        if (expr.equals("")) {
            etInput2.setText(R.string.error_nothing);
            return;
        }

        String current_currency_name1 = spinner1.getSelectedItem().toString();
        int index1 = Arrays.asList(CurrencyList).indexOf(current_currency_name1);
        double coefficient1 = CoefficientList[index1];

        String current_currency_name2 = spinner2.getSelectedItem().toString();
        int index2 = Arrays.asList(CurrencyList).indexOf(current_currency_name2);
        double coefficient2 = CoefficientList[index2];

        double result = (coefficient2 / coefficient1) * eval(expr);

        if (Double.isInfinite(result) || Double.isNaN(result)) {
            etInput2.setText(R.string.error_zero);
            return;
        }

        etInput2.setText(String.format(Locale.US, "%f", result));
    }

    // Позаимствовал данную функцию для подсчёта математических выражений в виде строк на Java вот из этого источника:
    // https://fooobar.com/questions/28238/evaluating-a-math-expression-given-in-string-form
    public static double eval(final String str) {
        return new Object() {
            int pos = -1, ch;

            void nextChar() {
                ch = (++pos < str.length()) ? str.charAt(pos) : -1;
            }

            boolean eat(int charToEat) {
                while (ch == ' ') nextChar();
                if (ch == charToEat) {
                    nextChar();
                    return true;
                }
                return false;
            }

            double parse() {
                nextChar();
                double x = parseExpression();
                if (pos < str.length()) throw new RuntimeException("Unexpected: " + (char) ch);
                return x;
            }

            // Grammar:
            // expression = term | expression `+` term | expression `-` term
            // term = factor | term `*` factor | term `/` factor
            // factor = `+` factor | `-` factor | `(` expression `)`
            //        | number | functionName factor | factor `^` factor

            double parseExpression() {
                double x = parseTerm();
                for (; ; ) {
                    if (eat('+')) x += parseTerm(); // addition
                    else if (eat('-')) x -= parseTerm(); // subtraction
                    else return x;
                }
            }

            double parseTerm() {
                double x = parseFactor();
                for (; ; ) {
                    if (eat('*')) x *= parseFactor(); // multiplication
                    else if (eat('/')) x /= parseFactor(); // division
                    else return x;
                }
            }

            double parseFactor() {
                if (eat('+')) return parseFactor(); // unary plus
                if (eat('-')) return -parseFactor(); // unary minus

                double x;
                int startPos = this.pos;
                if (eat('(')) { // parentheses
                    x = parseExpression();
                    eat(')');
                } else if ((ch >= '0' && ch <= '9') || ch == '.') { // numbers
                    while ((ch >= '0' && ch <= '9') || ch == '.') nextChar();
                    x = Double.parseDouble(str.substring(startPos, this.pos));
                } else if (ch >= 'a' && ch <= 'z') { // functions
                    while (ch >= 'a' && ch <= 'z') nextChar();
                    String func = str.substring(startPos, this.pos);
                    x = parseFactor();
                    if (func.equals("sqrt")) x = Math.sqrt(x);
                    else if (func.equals("sin")) x = Math.sin(Math.toRadians(x));
                    else if (func.equals("cos")) x = Math.cos(Math.toRadians(x));
                    else if (func.equals("tan")) x = Math.tan(Math.toRadians(x));
                    else throw new RuntimeException("Unknown function: " + func);
                } else {
                    throw new RuntimeException("Unexpected: " + (char) ch);
                }

                if (eat('^')) x = Math.pow(x, parseFactor()); // exponentiation

                return x;
            }
        }.parse();
    }
}